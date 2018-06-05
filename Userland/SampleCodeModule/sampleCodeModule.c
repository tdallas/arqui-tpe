#include <stdio.h>
#include <constantPrints.h>
#include <stdlib.h>
#include <blobsFront.h>

void managingCases(char *);
void help();
void exceptions();
void displayTime();
void blobwars();
void printingMenu();
void clearScreen();

int main()
{
    char *choice = malloc(150);
    printingMenu();
    while (1)
    {
        printf("$> ");
        scanf("%n", choice);
        if (strcmp(choice, "exit") == 0){
            break;
        }
        managingCases(choice);
    }
    return 0;
}

void managingCases(char *option)
{
    if (strcmp(option, "help") == 0)
    {
        help();
    }
    else if (strcmp(option, "displayTime") == 0)
    {
        displayTime();
    }
    else if (strcmp(option, "blobWars") == 0)
    {
        blobwars();
    }
    else if (strcmp(option, "exceptions") == 0)
    {
        exceptions();
    }
    else if (strcmp(option, "b") == 0) {
        printingMenu();
    }
    else
    {
        printf("Invalid input!\n");
    }
}

void printingMenu()
{
    clearScreen();
    printf("                            \n");
    printf("                           Welcome to Titanium Kernel!\n");
    printf("                            \n");
    printf("                                For Help, write help\n");
    printf("                  If you want to display time, write displayTime\n");
    printf("               If you want to play Blobwars (you should), write blobWars\n");
    printf("                                 Exceptions?, write exceptions\n");
    printf("                           If you want to exit, write exit\n");
    printf("                            \n");
    printf("                            \n");
    printf("                            \n");
    printf("                            \n");
    printf("                            \n");
}

void clearScreen()
{
    clearWorkSpace();
}

void help()
{
    //fixme ascii art somewhere
    clearScreen();
    printf("        This is a rudimentary kernell, created by 2 ITBA students, passionate for what they do\n");
    printf("                                            and what they study. \n");
    printf("        In this kernell, you will be able to do: \n ");
    printf("               - See what time is it. \n");
    printf("                - Play a game call BlobWars -> It is a strategy game where you can play \n");
    printf("                     against a IA or against a friend, where you got a squared matrix\n");
    printf("                     and the mission is to \"convert\" as much pieces of the enemy you can.\n");
    printf("                - You can get informed on how we managed exceptions\n");
    printf("                - Eventually, you can inform us of any bug you'll find and we'll be \n");
    printf("                      happy to solve them (hope they're few). You can send an email to : \n");
    printf("                              tdorado@itba.edu.ar or tdallas@itba.edu.ar\n");
    printf("\n\n                                  THANKS FOR USING OUR KERNELL! :) \n\n");
    printf("Press b to return \n\n");
}

void displayTime()
{
    printf("Epoch Time: %d.\n", time(NULL));
    printTime();
    printDate();
    printTimeUTC();
}

void exceptions()
{
    printf("YOU WANT TO SEE EXCEPTIONS\n");
}

void blobwars()
{
    iniciarBlobWars();
    printingMenu();
}