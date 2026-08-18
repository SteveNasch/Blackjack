#pragma once
#include "Player.h"

void getCardValueString(int number, char *str);

void printCardRow(int row, int number, int suit);

void printPlayerCardsHorizontally(Player *player);

void printDealerCardsHidden(Player *dealer);

void welcomeText();

void printCash(Player *player);

void printButtons(Player *player);

void winText(Player *player);

void loseText();

void pushText();
