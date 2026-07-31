#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include "headers/Deck.h"
#include "headers/Player.h"
#include "headers/UserInterface.h"

int input;

void verifyTotoints(Player &player) {

}

int main() {
    srand(time(nullptr));

    Deck deck;
    Player player;
    Player dealer;

    //Instantiate the players and deck
    initPlayer(&player);
    initDealer(&dealer);
    initDeck(&deck);

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
                while (dealer.points < 21) {
                    buyCard(&dealer, &deck);
                    printPlayerCardsHorizontally(&dealer);
                    printPlayerCardsHorizontally(&player);
                    calculatePlayerPoints(&dealer);
                    if (dealer.points < 21) std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                if (dealer.points > 21) {
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
                break;
            case 3:
                printPlayerCardsHorizontally(&dealer);
                buyCard(&player, &deck);
                printPlayerCardsHorizontally(&player);
                calculatePlayerPoints(&player);
                if (player.points > 21) {continue;}
                while (dealer.points < 21) {
                    buyCard(&dealer, &deck);
                    printPlayerCardsHorizontally(&dealer);
                    printPlayerCardsHorizontally(&player);
                    calculatePlayerPoints(&dealer);
                    if (dealer.points < 21) std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
                player.active = false;
                break;
        }
    }

    return 0;

}
