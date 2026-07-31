#include "headers/Deck.h"

#include <complex>
#include <bits/locale_facets_nonio.h>

int hashFunction(int id) {
    return std::abs(id) % DECK_SIZE;
}

void initDeck(Deck *deck) {
    for (int i = 0; i < DECK_SIZE; i++) {
        deck->card[i] = NULL;
    }

    for (int kind = 1; kind <= 4; kind++) {
        for (int number = 1; number <= 13; number++) {
            Card card;
            addToDeck(deck, initCard(&card, number, kind));
        }
    }
}

bool contains(Deck *deck, int id) {
    int index = hashFunction(id);

    Node *current = deck->card[index];
    while (current != NULL) {
        if (current->id == id) {
            return true;
        }
        current = current->nextCard;
    }
    return false;
}

bool addToDeck(Deck *deck, Card *card) {
    if (contains(deck, card->id)) {
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

    newCard->nextCard = deck->card[index];
    deck->card[index] = newCard;

    return true;
}

void removeElement(Deck *deck, int id) {
    int index = hashFunction(id);
    Node *current = deck->card[index];
    Node *prev = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (prev == NULL) {
                deck->card[index] = current->nextCard;
            } else {
                prev->nextCard = current->nextCard;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->nextCard;
    }
}

Card* getCard(Deck *deck, int id) {
    int index = hashFunction(id);
    Node *current = deck->card[index];

    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->nextCard;
    }

    return NULL;
}
