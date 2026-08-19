#pragma once
#include "Card.h"
#include "Deck.h"

#define INITIAL_CASH 50.00
#define BET 5.00

typedef struct {
    int points;
    double cash;
    Card *hand[DECK_SIZE];
    bool active;
    int sequenceCounter;
} Player;

void initPlayer(Player *player, bool isDealer);

bool contains(Player *player, int id);

bool addToHand(Player *player, Card *card);

Card* buyCard(Player *player, Deck *deck);

void calculatePlayerPoints(Player *player);

void placeBet(Player *player);

void payOut(Player *player);

bool isBlackjack(Player *player);
