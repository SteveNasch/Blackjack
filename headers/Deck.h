#pragma once
#include "Card.h"

#define DECK_SIZE 52

typedef struct {
    Card *card[DECK_SIZE];
} Deck;

int hashFunction(int id);

void initDeck(Deck *deck);

bool contains(Deck *deck, int id);

bool addToDeck(Deck *deck, Card *card);

void removeElement(Deck *deck, int id);

Card* getCard(Deck *deck, int id);
