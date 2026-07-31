#include "headers/Deck.h"

#include <complex>
#include <bits/locale_facets_nonio.h>

int hashFunction(int value) {
    return std::abs(value) % DECK_SIZE;
}

void initDeck(Deck *deck) {
    for (int i = 0; i < DECK_SIZE; i++) {
        deck->card[i] = NULL;
    }

    for (int kind = 1; kind <= 4; kind++) {
        for (int value = 1; value <= 13; value++) {
            Card card;
            add(deck, initCard(&card, value, kind));
        }
    }
}

bool contains(Deck *deck, int value) {
    int index = hashFunction(value);

    Node *current = deck->card[index];
    while (current != NULL) {
        if (current->id == value) {
            return true;
        }
        current = current->nextCard;
    }
    return false;
}

bool add(Deck *deck, Card *card) {
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

    newCard->nextCard = deck->card[index];
    deck->card[index] = newCard;

    return true;
}

void removeElement(Deck *deck, int value) {
    int index = hashFunction(value);
    Node *current = deck->card[index];
    Node *prev = NULL;

    while (current != NULL) {
        if (current->id == value) {
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

void printDeck(Deck *deck) {
    printf("{ ");
    for (int i = 0; i < DECK_SIZE; i++) {
        Node *current = deck->card[i];
        while (current != NULL) {
            printf("%d ", current->id);
            current = current->nextCard;
        }
    }
    printf("}\n\n");
    for (int i = 0; i < DECK_SIZE; i++) {
        Node *current = deck->card[i];
        while (current != NULL) {
            printf("%c %d / ", current->kind, current->value);
            current = current->nextCard;
        }
    }
}