#include <cstdio>
#include <cstring>

#include "headers/Player.h"


void getCardValueString(int number, char *str) {
    if (number == 1) strcpy(str, "A");
    else if (number == 10) strcpy(str, "X");
    else if (number == 11) strcpy(str, "J");
    else if (number == 12) strcpy(str, "Q");
    else if (number == 13) strcpy(str, "K");
    else sprintf(str, "%d", number);
}

void printCardRow(int row, int number, int suit) {
    char valStr[3];
    getCardValueString(number, valStr);

    switch(row) {
        case 0:
            printf(" _____  ");
            break;
        case 1:
            if (suit == 1) printf("|%s .  | ", valStr);      // Espadas
            else if (suit == 2) printf("|%s ^  | ", valStr); // Ouros
            else if (suit == 3) printf("|%s _  | ", valStr); // Copas
            else if (suit == 4) printf("|%s_ _ | ", valStr); // Paus
            break;
        case 2:
            if (suit == 1) printf("| /.\\ | ");
            else if (suit == 2) printf("| / \\ | ");
            else if (suit == 3) printf("| ( ) | ");
            else if (suit == 4) printf("|( v )| ");
            break;
        case 3:
            if (suit == 1) printf("|(_._)| ");
            else if (suit == 2) printf("| \\ / | ");
            else if (suit == 3) printf("|(_'_)| ");
            else if (suit == 4) printf("| \\ / | ");
            break;
        case 4:
            if (suit == 1) printf("|  |  | ");
            else if (suit == 2) printf("|  .  | ");
            else if (suit == 3) printf("|  |  | ");
            else if (suit == 4) printf("|  .  | ");
            break;
        case 5:
            if (number == 10) printf("|___10| ");
            else printf("|____%c| ", valStr[0]);
            break;
    }
}

static void printHiddenCardRow(int row) {
    switch(row) {
        case 0: printf(" _____  "); break;
        case 1: printf("|? .  | "); break;
        case 2: printf("| /.\\ | "); break;
        case 3: printf("|(_._)| "); break;
        case 4: printf("|  |  | "); break;
        case 5: printf("|____?| "); break;
    }
}

void printPlayerCardsHorizontally(Player *player) {
    Node* activeCards[21];
    int count = 0;

    for (int i = 0; i < DECK_SIZE; i++) {
        Node* current = player->hand[i];
        while (current != NULL) {
            activeCards[count] = current;
            count++;
            current = current->nextCard;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (activeCards[j]->sequence < activeCards[i]->sequence) {
                Node *tmp = activeCards[i];
                activeCards[i] = activeCards[j];
                activeCards[j] = tmp;
            }
        }
    }

    for (int row = 0; row < 6; row++) {
        for (int c = 0; c < count; c++) {
            printCardRow(row, activeCards[c]->number, activeCards[c]->kind);
        }
        printf("\n");
    }

    printf("\n");
}

void printDealerCardsHidden(Player *dealer) {
    Node* activeCards[21];
    int count = 0;

    for (int i = 0; i < DECK_SIZE; i++) {
        Node* current = dealer->hand[i];
        while (current != NULL) {
            activeCards[count] = current;
            count++;
            current = current->nextCard;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (activeCards[j]->sequence < activeCards[i]->sequence) {
                Node *tmp = activeCards[i];
                activeCards[i] = activeCards[j];
                activeCards[j] = tmp;
            }
        }
    }

    for (int row = 0; row < 6; row++) {
        for (int c = 0; c < count; c++) {
            if (c == 1) {
                printHiddenCardRow(row);
            } else {
                printCardRow(row, activeCards[c]->number, activeCards[c]->kind);
            }
        }
        printf("\n");
    }

    printf("\n");
}

void welcomeText(){
    printf(
    " /$$$$$$   /$$                                    /$$   /$$                               /$$      /$$               /$$$$$$$  /$$                    /$$                               /$$     \n"
          "/$$__  $$ | $$                                   | $$$ | $$                              | $$     | $/             | $$__  $$| $$                    | $$                              | $$     \n"
          "| $$  \\__//$$$$$$    /$$$$$$  /$$    /$$ /$$$$$$ | $$$$| $$  /$$$$$$   /$$$$$$$  /$$$$$$$| $$$$$$$|_//$$$$$$$      | $$  \\ $$| $$  /$$$$$$   /$$$$$$$| $$   /$$ /$$  /$$$$$$   /$$$$$$$| $$   /$$\n"
          "|  $$$$$$|_  $$_/   /$$__  $$|  $$  /$$//$$__  $$| $$ $$ $$ |____  $$ /$$_____/ /$$_____/| $$__  $$ /$$_____/      | $$$$$$$ | $$ |____  $$ /$$_____/| $$  /$$/|__/ |____  $$ /$$_____/| $$  /$$/\n"
          " \\____  $$ | $$    | $$$$$$$$ \\  $$/$$/| $$$$$$$$| $$  $$$$  /$$$$$$$|  $$$$$$ | $$      | $$  \\ $$|  $$$$$$       | $$__  $$| $$  /$$$$$$$| $$      | $$$$$$/  /$$  /$$$$$$$| $$      | $$$$$$/ \n"
          " /$$  \\ $$ | $$ /$$| $$_____/  \\  $$$/ | $$_____/| $$\\  $$$ /$$__  $$ \\____  $$| $$      | $$  | $$ \\____  $$      | $$  \\ $$| $$ /$$__  $$| $$      | $$_  $$ | $$ /$$__  $$| $$      | $$_  $$ \n"
          "|  $$$$$$/ |  $$$$/|  $$$$$$$   \\  $/  |  $$$$$$$| $$ \\  $$|  $$$$$$$ /$$$$$$$/|  $$$$$$$| $$  | $$ /$$$$$$$/      | $$$$$$$/| $$|  $$$$$$$|  $$$$$$$| $$ \\  $$| $$|  $$$$$$$|  $$$$$$$| $$ \\  $$\n"
          " \\______/   \\___/   \\_______/    \\_/    \\_______/|__/  \\__/ \\_______/|_______/  \\_______/|__/  |__/|_______/       |_______/ |__/ \\_______/ \\_______/|__/  \\__/| $$ \\_______/ \\_______/|__/  \\__/\n"
          "                                                                                                                                                          /$$  | $$                       \n"
          "                                                                                                                                                         |  $$$$$$/                       \n"
          "                                                                                                                                                          \\______/                        \n"
);
}

void printCash(Player *player) {
    printf("┌────────────────────┐\n"
           "| Cash: R$%07.2f   |\n"
           "└────────────────────┘\n\n",
           player->cash);
}

void printButtons(Player *player) {
    printf("┌────────────────────┐    ┌───────────┐ ┌───────────┐ ┌────────────┐\n"
                 "| You have %02d points |    | 1 - Stand | |  2 - Hit  | | 3 - Double |\n"
                 "└────────────────────┘    └───────────┘ └───────────┘ └────────────┘\n",
                 player->points);
}

void winText(Player *player) {
    printf("┌──────────────┐    ┌──────────────┐\n"
                 "| YOU WON!!!!! |    |  +R$%06.2f   |\n"
                 "└──────────────┘    └──────────────┘\n",
                 BET);
}

void loseText() {
    printf("┌──────────────┐\n"
                 "| YOU LOSE!!!! |\n"
                 "└──────────────┘\n");
}

void pushText() {
    printf("┌──────────────┐\n"
                 "|    PUSH!     |\n"
                 "└──────────────┘\n");
}
