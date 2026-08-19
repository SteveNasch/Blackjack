#pragma once

typedef struct Node {
    int value, id, number;
    int kind;
    int sequence;
    Node *nextCard;
} Card;

Card* initCard(Card *card, int number, int kind);
