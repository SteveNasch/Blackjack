#pragma once

typedef struct Node {
    int value, id;
    char kind;
    struct Node *nextCard;
} Card;

void initCard(Card *card, int value, char kind);