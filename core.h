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


#ifndef CORE_H
#define CORE_H
 


void clearInputBuffer(void);

void suspend(void);

void displayFormattedPhone(const char number[]);



int inputInt();

int inputIntPositive();


int inputIntRange(int high, int low);

char inputCharOption(const char name[]);


void inputCString(char string[], int min, int max);

#endif // !CORE_H