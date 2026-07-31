#pragma once
#include "Card.h"
#include "Deck.h"

#define INITIAL_CASH 50.00

typedef struct {
    int points;
    double cash;
    Card *hand[DECK_SIZE];
    bool active;
} Player;

void initPlayer(Player *player);

void initDealer(Player *player);

bool contains(Player *player, int id);

bool addToHand(Player *player, Card *card);

void buyCard(Player *player, Deck *deck);

void calculatePlayerPoints(Player *player);
