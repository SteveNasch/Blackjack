#include <cstdio>
#include <ctime>
#include <thread>
#include <chrono>
#include "headers/Deck.h"
#include "headers/Player.h"
#include "headers/UserInterface.h"

int main() {
    srand(time(nullptr));

    bool playing = true;

    while (playing) {
        Deck deck;
        Player player;
        Player dealer;

        initPlayer(&player, false);
        initPlayer(&dealer, true);
        initDeck(&deck);

        welcomeText();
        printCash(&player);

        if (player.cash < BET) {
            printf("Sem saldo para apostar!\n");
            break;
        }
        placeBet(&player);

        // Deal initial cards
        buyCard(&dealer, &deck);
        buyCard(&player, &deck);
        buyCard(&player, &deck);

        calculatePlayerPoints(&dealer);
        calculatePlayerPoints(&player);

        // Show dealer with hidden hole card
        printDealerCardsHidden(&dealer);
        printPlayerCardsHorizontally(&player);

        // Check for blackjack
        if (isBlackjack(&player)) {
            if (isBlackjack(&dealer)) {
                pushText();
                player.cash += BET;
            } else {
                winText(&player);
            }
            printCash(&player);
            player.active = false;
        }

        // Player turn
        while (player.active) {
            if (player.points > 21) {
                loseText();
                player.active = false;
                break;
            }

            printButtons(&player);
            int input = 0;
            if (scanf("%d", &input) != 1) {
                while (getchar() != '\n');
                printf("Opcao invalida! Tente novamente.\n");
                continue;
            }

            switch (input) {
                case 1: // Stand
                    // Reveal dealer's hole card
                    printf("\nDealer revela as cartas:\n");
                    printPlayerCardsHorizontally(&dealer);

                    // Dealer draws
                    while (dealer.points < 17) {
                        buyCard(&dealer, &deck);
                        printPlayerCardsHorizontally(&dealer);
                        printPlayerCardsHorizontally(&player);
                        calculatePlayerPoints(&dealer);
                        if (dealer.points < 17) {
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        }
                    }

                    // Determine winner
                    if (dealer.points > 21) {
                        payOut(&player);
                        winText(&player);
                    } else if (dealer.points > player.points) {
                        loseText();
                    } else if (dealer.points < player.points) {
                        payOut(&player);
                        winText(&player);
                    } else {
                        pushText();
                        player.cash += BET;
                    }
                    player.active = false;
                    break;

                case 2: // Hit
                    buyCard(&player, &deck);
                    printPlayerCardsHorizontally(&player);
                    calculatePlayerPoints(&player);
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    break;

                case 3: // Double
                    if (player.cash < BET) {
                        printf("Saldo insuficiente para dobrar!\n");
                        break;
                    }
                    placeBet(&player);
                    buyCard(&player, &deck);
                    printPlayerCardsHorizontally(&player);
                    calculatePlayerPoints(&player);
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));

                    if (player.points > 21) {
                        loseText();
                        player.active = false;
                        break;
                    }

                    // Reveal dealer's hole card
                    printf("\nDealer revela as cartas:\n");
                    printPlayerCardsHorizontally(&dealer);

                    // Dealer draws
                    while (dealer.points < 17) {
                        buyCard(&dealer, &deck);
                        printPlayerCardsHorizontally(&dealer);
                        printPlayerCardsHorizontally(&player);
                        calculatePlayerPoints(&dealer);
                        if (dealer.points < 17) {
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        }
                    }

                    // Determine winner
                    if (dealer.points > 21) {
                        payOut(&player);
                        winText(&player);
                    } else if (dealer.points > player.points) {
                        loseText();
                    } else if (dealer.points < player.points) {
                        payOut(&player);
                        winText(&player);
                    } else {
                        pushText();
                        player.cash += BET * 2;
                    }
                    player.active = false;
                    break;

                default:
                    printf("Opcao invalida! Use 1, 2 ou 3.\n");
                    break;
            }
        }

        printCash(&player);

        // Ask to play again
        if (player.cash > 0) {
            printf("Jogar novamente? (1 - Sim, 0 - Nao): ");
            int choice = 0;
            if (scanf("%d", &choice) != 1 || choice != 1) {
                playing = false;
            }
            printf("\n");
        } else {
            printf("Sem saldo! Fim de jogo.\n");
            playing = false;
        }
    }

    printf("Obrigado por jogar!\n");
    return 0;
}
