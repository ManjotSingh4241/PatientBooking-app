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
#include<string.h>

#include "core.h"

#include "clinic.h"



void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}


void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
      
        selection = inputIntRange(0, 2);
        
        putchar('\n');
        
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}


void menuPatient(struct Patient patient[], int max)

{
    int selection;

    do {

        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");

        selection = inputIntRange(0, 5);

        putchar('\n');

        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}


void menuPatientEdit(struct Patient* patient)

{

    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"

            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");

        selection = inputIntRange(0, 2);

        putchar('\n');

        if (selection == 1)
        {

            printf("Name  : ");

            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;


    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }

    for (i = 0; i < max && patient[i].patientNumber != '\0'; i++)
    {

        printf("%4.5d %-16s", patient[i].patientNumber, patient[i].name);
        displayFormattedPhone(patient[i].phone.number);
        printf(" (%s)", patient[i].phone.description);


        printf("\n");

    }

    printf("\n");

}

void searchPatientData(const struct Patient patient[], int max)

{

    int selection = 3;

    while (selection != 0)

    {

        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n");


        printf("Selection: ");

        selection = inputIntRange(0, 2);


        printf("\n");

        if (selection == 1)
        {

            searchPatientByPatientNumber(patient, max);

        }

        else if (selection == 2)

        {

            searchPatientByPhoneNumber(patient, max);
        }

    }
}

void addPatient(struct Patient patient[], int max)

{

    int i,
        count = 0,
        num = 0;


    for (i = 0; i < max && patient[i].patientNumber != '\0'; i++)
    {
        count++;
    }

    if (count >= max)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }

    else
    {
        num = nextPatientNumber(patient, max);

        if (count < max)
        {
            patient[count].patientNumber = num;
        }

        inputPatient(&patient[count]);

        if (count != max)
        {
            patient[max].patientNumber = '\0';
        }

        printf("*** New patient record added ***\n");
        printf("\n");
        clearInputBuffer();
    }
}


void editPatient(struct Patient patient[], int max)

{

    int i = 0,
        patientNumber = 0;

    printf("Enter the patient number: ");
    scanf("%d", &patientNumber);

    i = findPatientIndexByPatientNum(patientNumber, patient, max);
    printf("\n");

    if (i == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        menuPatientEdit(&patient[i]);
    }
}


void removePatient(struct Patient patient[], int max)

{

    int i = 0,
        j = 0,
        patientNumber = 0,
        selection = 0;


    printf("Enter the patient number: ");
    scanf("%d", &patientNumber);
    printf("\n");

    i = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (i == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }

    else
    {
        displayPatientData(&patient[i], 1);
        printf("\n");

        printf("Are you sure you want to remove this patient record? (y/n): ");
        selection = inputCharOption("yn") == 'y';

        if (selection)
        {
            for (j = i; j < max; j++)
            {
                patient[j] = patient[j + 1];                                 

            }


            printf("Patient record has been removed!\n\n");

        }

        else

        {
            printf("Operation aborted.\n\n");

        }
    }
}


void searchPatientByPatientNumber(const struct Patient patient[], int max)

{

    int patientNum = 0,
        i = 0,
        match = 0;

    printf("Search by patient number: ");
    scanf("%d", &patientNum);

    printf("\n");

    for (i = 0; i < max; i++)

    {

        if (patient[i].patientNumber == patientNum)

        {

            displayPatientData(&patient[i], 1);

            printf("\n");


            match = 1;
        }
    }

    if (match == 0)
    {
        printf("*** No records found ***\n");
        printf("\n");
    }

    clearInputBuffer();
    suspend();
}


void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phoneNum[11] = { '\0' };
    int i = 0,
        match = 0;


    printf("Search by phone number: ");
    
    scanf("%s", phoneNum);


    
    printf("\n");
    
    displayPatientTableHeader();


    
    for (i = 0; i < max; i++)
    
    {
    
        if (strcmp(patient[i].phone.number, phoneNum) == 0)
        
        {
        
            printf("%4.5d %-16s", patient[i].patientNumber, patient[i].name);
            
            displayFormattedPhone(patient[i].phone.number);
            
            printf(" (%s)", patient[i].phone.description);
            
            printf("\n");

            
            match = 1;
        }







    }



    
    if (match == 0)
    
    {
    
        printf("\n");
        printf("*** No records found ***");
        
        printf("\n");
    }


    
    printf("\n");


    
    clearInputBuffer();
    
    suspend();
}




int nextPatientNumber(const struct Patient patient[], int max)

{

    int i = 0,

        num = 0,

        count = 0;


    
    for (i = 0; i < max && patient[i].patientNumber != '\0'; i++)
    
    {
    
        count++;
    }

    
    num = (patient[count - 1].patientNumber + 1);


    
    return num;





}

int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    

    int num = 0,


        
        found = 0,
        i = 0;


    for (i = 0; i < max; i++)
    
    {
    
        if (patient[i].patientNumber == patientNumber)
        
        {
        
            found = 1;
            
            num = i;
        }

    }

    
    if (found != 1)
    {
        num = -1;
    
    }


    
    return num;
}






void inputPatient(struct Patient* patient)

{

    printf("Patient Data Input\n"

        "------------------\n");


    printf("Number: %.5d\n", patient->patientNumber);
    
    printf("Name  : ");
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    scanf("%[^\n]", patient->name);

    
    printf("\n");
    inputPhoneData(&patient->phone);
}



void inputPhoneData(struct Phone* phone)

{

    int selection = 0;
    char s1[] = { "CELL" };
    char s2[] = { "HOME" };

    char s3[] = { "WORK" };

    char s4[] = { "TBD" };


    
    printf("Phone Information\n"
    
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        
        "1. Cell\n"
        
        "2. Home\n"
        
        "3. Work\n"
        
        "4. TBD\n"
        
        "Selection: ");
    scanf("%d", &selection);

    if (selection == 1)
    {
        strcpy(phone->description, s1);
    }
    else if (selection == 2)

    {
        strcpy(phone->description, s2);

    }

    else if (selection == 3)
    {

        strcpy(phone->description, s3);

    }
    else if (selection == 4)
    {
        strcpy(phone->description, s4);


    }


    if (selection != 4)

    {

        printf("\n");

        printf("Contact: %s\n", phone->description);

        printf("Number : ");

        scanf("%s", phone->number);

    }


    
    printf("\n");

}

