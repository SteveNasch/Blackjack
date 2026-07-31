#pragma once

typedef struct Node {
    int value, id, number;
    int kind;
    Node *nextCard;
} Card;

Card* initCard(Card *card, int number, int kind);