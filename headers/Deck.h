#pragma once
#include "Card.h"

#define DECK_SIZE 52

typedef struct {
    Card *card[DECK_SIZE];
} Deck;

int HashFunction(int value);

void initDeck(Deck *deck);

bool contains(Deck *deck, int value);

bool add(Deck *deck, Card *card);

void removeElement(Deck *deck, int value);

void printDeck(Deck *deck);