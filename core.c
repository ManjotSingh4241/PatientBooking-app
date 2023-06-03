/*
*****************************************************************************
                        Assignment 1 - Milestone 2
Full Name  : Manjot Singh
Student ID#: 171797210
Email      : msingh753@myseneca.ca
Section    : ZBB
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


void clearInputBuffer(void)
{
   
    while (getchar() != '\n')
    {
        ; 
    }
}


void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


void displayFormattedPhone(const char number[])
{
    int i = 0,
        count = 0,
        num = 0;

    if (number != NULL)
    {
        for (i = 0; number[i] != '\0'; i++)
        {
            count++;                             

            if (number[i] < 58 && number[i]> 47)
            {
                num++;                             
            }
        }
    }

    if ((count == 10) && (num == 10))
    {
        printf("(%.3s)%.3s-%s", number, &number[3], &number[6]);
    }
    else
    {
        printf("(___)___-____");
    }

}



int inputInt()
{
    int value = 0;
    char n = 'x';

    while (!(value))
    {
        scanf(" %d%c", &value, &n);

        if (!(n == '\n'))
        {
            clearInputBuffer();
        }

        if (!(value))                          
        {
            printf("Error! Input a whole number: ");
        }
    }

    return value;
}


int inputIntPositive()
{
    int x = -1;

    while (!(x >= 0))
    {
        scanf(" %d", &x);

        if (!(x >= 0))
        {
            printf("ERROR! Value must be > 0: ");
        }

    }

    return x;
}


int inputIntRange(int low, int high)
{
    int x = 0,
        h = high,
        l = low;
    char y;

    x = h + 10;                                     

    while (!(x <= h && x >= l))
    {
        scanf(" %d%c", &x, &y);

        if (!(y == '\n'))
        {
            clearInputBuffer();
        }

        if (x == h + 10)                       
       {
            printf("Error! Input a whole number: ");
        }
        else
        {
            if (!(x <= h && x >= l))
            {
                printf("ERROR! Value must be between %d and %d inclusive: ", l, h);
            }
        }
    }

    return x;
}

 
char inputCharOption(const char name[])
{
    int i = 0,
        z = 0,
        l = 0,
        y = 0;
    char x = '\0';

    for (i = 0; name[i] != '\0'; i++)
    {
        l++;
    }

    while (!(y == 1))
    {
        y = 0;
        z = 0;

        scanf(" %c", &x);

        if (!(x == '\0'))
        {
            clearInputBuffer();
        }

        for (i = 0; i < l; i++)
        {
            if (x == name[i])
            {
                y = 1;
            }
            z = 1;
        }

        if (y == 0 && z == 1)
        {
            printf("ERROR: Character must be one of [%s]: ", name);
        }
    }

    return x;
}
void inputCString(char string[], int min, int max)
{
    int i = 0,
        count = 0,
        y = 0,
        h = 0,
        l = 0;

    while (!(y == 1))
    {
        count = 0;
        h = max;
        l = min;

        scanf("%[^\n]s", string);

        clearInputBuffer();

        if (string)
        {
            for (i = 0; string[i] != '\0'; i++)
            {
                count++;
            }
        }

        if ((count <= max) && (count >= min))
        {
            y = 1;
        }

        else
        {
            if (h == l)
            {
                printf("ERROR: String length must be exactly %d chars: ", max);
            }

            else if (h == l + 1)
            {
                printf("ERROR: String length must be between %d and %d chars: ", min, max);
            }

            else
            {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }

        }
    }

}
