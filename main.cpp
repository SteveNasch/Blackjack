#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include "headers/Deck.h"
#include "headers/Player.h"
#include "headers/UserInterface.h"

int input;

int main() {
    srand(time(nullptr));

    Deck deck;
    Player player;
    Player dealer;

    welcomeText();

    //Instantiate the players and deck
    initPlayer(&player);
    initDealer(&dealer);
    initDeck(&deck);

    if (player.cash < BET) {
        printf("Sem saldo para apostar!\n");
        return 0;
    }
    placeBet(&player);

    //Dealer startup
    buyCard(&dealer, &deck);
    printPlayerCardsHorizontally(&dealer);
    calculatePlayerPoints(&dealer);

    //Player statup
    buyCard(&player, &deck);
    buyCard(&player, &deck);

    printPlayerCardsHorizontally(&player);
    calculatePlayerPoints(&player);

    while (player.active) {

        if (player.points < 21) {
            printButtons(&player);
            scanf("%d", &input);
        } else if (player.points == 21) {
            payOut(&player);
            winText(&player);
            player.active = false;
            return 0;
        } else {
            loseText();
            player.active = false;
            return 0;
        }

        switch (input) {
            case 1:
                while (dealer.points < 21 && dealer.points < player.points) {
                    buyCard(&dealer, &deck);
                    printPlayerCardsHorizontally(&dealer);
                    printPlayerCardsHorizontally(&player);
                    calculatePlayerPoints(&dealer);
                    if (dealer.points < 21) std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                if (dealer.points > 21) {
                    payOut(&player);
                    winText(&player);
                } else {
                    loseText();
                }
                player.active = false;
                break;
            case 2:
                printPlayerCardsHorizontally(&dealer);
                buyCard(&player, &deck);
                printPlayerCardsHorizontally(&player);
                calculatePlayerPoints(&player);
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                break;
            case 3:
                printPlayerCardsHorizontally(&dealer);
                buyCard(&player, &deck);
                printPlayerCardsHorizontally(&player);
                calculatePlayerPoints(&player);
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                if (player.points > 21) {
                    loseText();
                    player.active = false;
                    break;
                }
                while (dealer.points < 21 && dealer.points < player.points) {
                    buyCard(&dealer, &deck);
                    printPlayerCardsHorizontally(&dealer);
                    printPlayerCardsHorizontally(&player);
                    calculatePlayerPoints(&dealer);
                    if (dealer.points < 21) std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                if (dealer.points > 21) {
                    payOut(&player);
                    winText(&player);
                } else {
                    loseText();
                }
                player.active = false;
                break;
        }
    }

    return 0;

}
