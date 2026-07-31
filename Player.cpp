#include "headers/Player.h"

#include <cstdio>
#include <cstdlib>

void initPlayer(Player *player) {
    player->points = 0;
    player->cash = INITIAL_CASH;
    player->active = true;
    for (int i = 0; i < DECK_SIZE; i++) {
        player->hand[i] = NULL;
    }
}

void initDealer(Player *player) {
    player->points = 0;
    player->cash = 0;
    player->active = false;
    for (int i = 0; i < DECK_SIZE; i++) {
        player->hand[i] = NULL;
    }
}

bool contains(Player *player, int id) {
    int index = hashFunction(id);

    Node *current = player->hand[index];
    while (current != NULL) {
        if (current->id == id) {
            return true;
        }
        current = current->nextCard;
    }
    return false;
}

bool addToHand(Player *player, Card *card) {
    if (contains(player, card->id)) {
        return false;
    }

    int index = hashFunction(card->id);

    Node *newCard = (Node *)malloc(sizeof(Node));
    if (newCard == NULL) {
        printf("Memory allocation error!\n");
        return false;
    }

    newCard->id = card->id;
    newCard->kind = card->kind;
    newCard->value = card->value;
    newCard->number = card->number;

    newCard->nextCard = player->hand[index];
    player->hand[index] = newCard;

    return true;
}

void buyCard(Player *player, Deck *deck) {
    Card *drawnCard = NULL;
    int randomId = 0;

    while (drawnCard == NULL) {
        int randomKind = rand() % 4 + 1;
        int randomNum = rand() % 13 + 1;
        randomId = randomKind * 100 + randomNum;

        drawnCard = getCard(deck, randomId);
    }

    addToHand(player, drawnCard);
    removeElement(deck, randomId);
}

void calculatePlayerPoints(Player *player) {
    player->points = 0;
    int aceCount = 0;

    for (int i = 0; i < DECK_SIZE; i++) {
        Node *current = player->hand[i];

        while (current != NULL) {
            if (current->number == 1) {
                aceCount++;
            }

            player->points += current->value;
            current = current->nextCard;
        }
    }

    while (player->points > 21 && aceCount > 0) {
        player->points -= 10;
        aceCount--;
    }
}