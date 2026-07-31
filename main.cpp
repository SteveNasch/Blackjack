#include <iostream>
#include "headers/Deck.h"

int main() {

    Deck deck;
    initDeck(&deck);

    printDeck(&deck);
    return 0;

}