#pragma once

typedef struct Node {
    int value, id;
    char kind;
    struct Node *nextCard;
} Card;

Card* initCard(Card *card, int value, int kind);