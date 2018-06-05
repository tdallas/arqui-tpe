#include <shell.h>

static char choice[BUFFER_SIZE];

#define DEFAULT 0
#define RED 1
#define ORANGE 2
#define YELLOW 3
#define GREEN 4
#define BLUE 5

void shell(int showMenu)
{
    int flag = 0;
    while (!flag)
    {
        printf("$> ");
        scanf("%n", choice);
        flag = managingCases(choice);
    }
}

int managingCases(char *option)
{
    if (strcmp(option, "help") == 0)
    {
        help();
    }
    else if (strncmp(option, "setTimeZone ", 11) == 0)
    {
        int newTimeZone;
        int count = sscanf(option, "setTimeZone %d", &newTimeZone);
        if (count == 1)
        {
            setTimeUTC(newTimeZone);
            printTimeUTC();
        }
        else
        {
            printf("Invalid input! For help write help.\n");
        }
    }
    else if (strncmp(option, "changeTextColor ", 15) == 0)
    {
        int correct = changeTextColor(option + 16);
        if (correct == 1)
        {
            printf("Color changed!\n");
        }
        else
        {
            printf("Invalid input! For help write help.\n");
        }
    }
    else if (strncmp(option, "changeBackGroundColor ", 21) == 0)
    {
        int correct = changeBackGroundColor(option + 22);
        if (correct == 1)
        {
            clearWorkSpace();
            printf("Color changed!\n");
        }
        else
        {
            printf("Invalid input! For help write help.\n");
        }
    }
    else if (strcmp(option, "info") == 0)
    {
        info();
    }
    else if (strcmp(option, "displayTime -digital") == 0)
    {
        startDigitalTime();
    }
    else if (strcmp(option, "displayTime -console") == 0)
    {
        displayTime();
    }
    else if (strcmp(option, "blobWars") == 0)
    {
        iniciarBlobWars();
    }
    else if (strcmp(option, "exceptionZero") == 0)
    {
        zeroDiv();
    }
    else if (strcmp(option, "exceptionOpCode") == 0)
    {
        opCode();
    }
    else if (strcmp(option, "clear") == 0)
    {
        clearWorkSpace();
    }
    else if (strcmp(option, "exit") == 0)
    {
        return 1;
    }
    else if (strcmp(option, "") != 0)
    {
        printf("Invalid input! For help write help.\n");
    }
    *option = 0;
    return 0;
}

void help()
{
    printf("                            \n");
    printf("                           Welcome to Titanium OS!\n");
    printf("                            \n");
    printf("                                For more information, write info\n");
    printf("                                To clean the console, write clear\n");
    printf("             If you want to display time on console, write displayTime -console\n");
    printf("            If you want to display the digital time, write displayTime -digital\n");
    printf("              If you want to change the timezone, write setTimeZone NUMBER\n");
    printf("               If you want to play Blobwars (you should), write blobWars\n");
    printf("              Write exceptionZero for trying our divZero exception catch\n");
    printf("              Write exceptionOpCode for trying our opCode exception catch\n");
    printf("                           If you want to exit, write exit\n");
    printf("                            \n");
}

void info()
{
    printf("        This is a rudimentary OS, created by 2 ITBA students, passionate for what they do\n");
    printf("                                            and what they study. \n");
    printf("        In this OS, you will be able to do: \n ");
    printf("                - See what time is it. \n");
    printf("                - See what time is it on a digital watch. \n");
    printf("                - Play a game call BlobWars -> It is a strategy game where you can play \n");
    printf("                     against a IA or against a friend, where you got a squared matrix\n");
    printf("                     and the mission is to \"convert\" as much pieces of the enemy you can.\n");
    printf("                - You can test the exceptions\n");
    printf("                - Eventually, you can inform us of any bug you'll find and we'll be \n");
    printf("                      happy to solve them (hope they're few). You can send an email to : \n");
    printf("                              tdorado@itba.edu.ar or tdallas@itba.edu.ar\n");
    printf("\n                                   THANKS FOR USING OUR OS! :) \n\n");
}

void displayTime()
{
    printf("Epoch Time: %d.\n", time(NULL));
    printTime();
    printDate();
    printTimeUTC();
}

int changeTextColor(char *color)
{
    int number = wichColor(color);
    switch (number)
    {
    case DEFAULT:
        setCharColor(255, 255, 255);
        break;
    case RED:
        setCharColor(255, 0, 0);
        break;
    case ORANGE:
        setCharColor(255, 128, 0);
        break;
    case YELLOW:
        setCharColor(255, 255, 0);
        break;
    case GREEN:
        setCharColor(0, 255, 0);
        break;
    case BLUE:
        setCharColor(0, 0, 255);
        break;
    }
    return number > 0;
}

int changeBackGroundColor(char *color)
{
    int number = wichColor(color);
    switch (number)
    {
    case DEFAULT:
        setBackGroundColor(0, 0, 0);
        break;
    case RED:
        setBackGroundColor(255, 0, 0);
        break;
    case ORANGE:
        setBackGroundColor(255, 128, 0);
        break;
    case YELLOW:
        setBackGroundColor(255, 255, 0);
        break;
    case GREEN:
        setBackGroundColor(0, 255, 0);
        break;
    case BLUE:
        setBackGroundColor(0, 0, 255);
        break;
    }
    return number > 0;
}

int wichColor(char *color)
{
    if (strcmp(color, "default") == 0)
    {
        return DEFAULT;
    }
    else if (strcmp(color, "red") == 0)
    {
        return RED;
    }
    else if (strcmp(color, "orange") == 0)
    {
        return ORANGE;
    }
    else if (strcmp(color, "yellow") == 0)
    {
        return YELLOW;
    }
    else if (strcmp(color, "green") == 0)
    {
        return GREEN;
    }
    else if (strcmp(color, "blue") == 0)
    {
        return BLUE;
    }
    return -1;
}