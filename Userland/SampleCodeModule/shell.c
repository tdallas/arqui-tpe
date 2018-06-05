#include <shell.h>

static char choice[BUFFER_SIZE];

void shell()
{
    int flag = 0;
    printingMenu();
    while (!flag)
    {
        printf("$> ");
        scanf("%n", choice);
        if (strcmp(choice, "exit") == 0){
            flag = 1;
        }
        managingCases(choice);
    }
}

void managingCases(char *option)
{
    if (strcmp(option, "help") == 0)
    {
        help();
    }
    else if(strcmp(option, "displayDigitalTime") == 0){
        startDigitalTime();
    }
    else if (strcmp(option, "displayTime") == 0)
    {
        displayTime();
    }
    else if (strcmp(option, "blobWars") == 0)
    {
        blobwars();
    }
    else if (strcmp(option, "exceptionsZero") == 0)
    {
        exceptions(0);
    }
    else if (strcmp(option, "exceptionsOpCode") == 0)
    {
        exceptions(6);
    }
    else if (strcmp(option, "b") == 0) {
        printingMenu();
    }
    else if(strcmp(option, "") != 0)
    {
        printf("Invalid input!\n");
    }
    *option = 0;
}

void printingMenu()
{
    printf("                            \n");
    printf("                           Welcome to Titanium Kernel!\n");
    printf("                            \n");
    printf("                                For Help, write help\n");
    printf("                  If you want to display time, write displayTime\n");
    printf("           If you want to display the digital time, write displayDigitalTime\n");
    printf("               If you want to play Blobwars (you should), write blobWars\n");
    printf("              Write exceptionsZero for trying our divZero exception catch\n");
    printf("              Write exceptionsOpCode for trying our opCode exception catch\n");
    printf("                           If you want to exit, write exit\n");
    printf("                            \n");
    printf("                            \n");
    printf("                            \n");
    printf("                            \n");
    printf("                            \n");
}

void help()
{
    //fixme ascii art somewhere
    clearWorkSpace();
    printf("        This is a rudimentary kernell, created by 2 ITBA students, passionate for what they do\n");
    printf("                                            and what they study. \n");
    printf("        In this kernell, you will be able to do: \n ");
    printf("                - See what time is it. \n");
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

void exceptions(int code)
{
    if (code == 6)
        opCode();
    else
        zeroDiv();
}

void blobwars()
{
    iniciarBlobWars();
    printingMenu();
}