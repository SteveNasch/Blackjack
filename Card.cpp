#include "headers/Card.h"

Card* initCard(Card *card, int number, int kind) {
    int value = number;

    card->id = kind * 100 + number;

    if (value > 10) value = 10;
    if (value == 1) value = 11;

    card->number = number;
    card->value = value;
    card->kind = kind;

    return card;
}
