#include "headers/Card.h"

Card* initCard(Card *card, int value, int kind) {
    card->id = (kind * 100) + value;

    //Sets the correct value of face cards
    if (value > 10) value = 10;

    card->value = value;
    card->kind = 'A' + kind;

    return card;
}