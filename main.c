#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
void listRecords();
void addRecords();
void searchRecords();
void modifyExistingRecords();
void payment();

struct customer
{
    char phonenumber[20];
    char name[50];
    float amount;
} s;
char get;
int main()
{
    int phonenumber;
    int choice;
    printf("\n\n\n\n\t\t**************************************************************");
    printf("\n\t\t-------WELCOME-------");
    printf("\n\t\t****************************************************************");
    while (choice != 6)
    {
        printf("\n Enter\n 1 : for adding new records.\n 2 : for list of records");
        printf("\n 3 : for modifying records.\n 4 : for payment");
        printf("\n 5 : for searching records.");
        printf("\n 6 : for exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addRecords();
            break;
        case 2:
            listRecords();
            break;
        case 3:
            modifyExistingRecords();
            break;
        case 4:
            payment();
            break;
        case 5:
            searchRecords();
            break;
        case 6:
            printf("\n\n\t\t\t-------THANK YOU FOR USING OUR SERVICE--------");
            exit(0);
            break;
        default:
            printf("Wrong Input");
            printf("\nAny key to continue");
            break;
        }
    }
}

void addRecords()
{
    FILE *file;
    int check = 1;
    file = fopen("file.txt", "ab+");
    if (file == 0)
    {
        file = fopen("file.txt", "wb+");
        printf("/nPress any key to continue");
    }
    while (check != 27)
    {
        printf("\n Enter phone number:");
        scanf("%s", s.phonenumber);
        printf("\n Enter name:");
        scanf("%s[^\n]", s.name);
        printf("\n Enter amount:");
        scanf("%f", &s.amount);
        fwrite(&s, sizeof(s), 1, file);
        printf("1 record added successfully");
        printf("\n Press 27 to exit, press any other key to add other record:");
        scanf("%d", &check);
        if (check == 27)
            break;
    }
    fclose(file);
}

void listRecords()
{
    FILE *file;
    int i;
    if ((file = fopen("file.txt", "rb")) == NULL)
        exit(0);
    system("cls");
    printf("Phone Number\t\tUser Name\t\t\tAmount\n");
    for (i = 0; i < 79; i++)
        printf("-");
    while (fread(&s, sizeof(s), 1, file) == 1)
    {
        printf("\n%-10s\t\t%-20s\t\tRs. %.2f /-", s.phonenumber, s.name, s.amount);
    }
    printf("\n");
    for (i = 0; i < 79; i++)
        printf("-");
    fclose(file);
}

void searchRecords()
{
    FILE *file;
    char phonenumber[20];
    int checkFlag = 1;
    file = fopen("file.txt", "rb+");
    if (file == 0)
        exit(0);
    fflush(stdin);
    printf("Enter Phone Number to search in our database");
    scanf("%s", phonenumber);
    while (fread(&s, sizeof(s), 1, file) == 1)
    {
        if (strcmp(s.phonenumber, phonenumber) == 0)
        {
            printf(" Record Found ");
            printf("\n\nPhonenumber: %s\nName: %s\nAmount: Rs.%0.2f\n", s.phonenumber, s.name, s.amount);
            checkFlag = 0;
            break;
        }
        else if (checkFlag == 1)
        {
            printf("Requested Phone Number Not found in our database");
        }
    }
    fclose(file);
}

void modifyExistingRecords()
{
    FILE *file;
    char phonenumber[20];
    long int size = sizeof(s);
    if ((file = fopen("file.txt", "rb+")) == NULL)
        exit(0);
    printf("Enter phone number of the customer to modify:");
    scanf("%s[^\n]", phonenumber);
    fflush(stdin);
    while (fread(&s, sizeof(s), 1, file) == 1)
    {
        if (strcmp(s.phonenumber, phonenumber) == 0)
        {
            printf("\n Enter phone number:");
            scanf("%s", s.phonenumber);
            printf("\n Enter name: ");
            fflush(stdin);
            scanf("%s[^\n]", s.name);
            printf("\n Enter amount: ");
            scanf("%f", &s.amount);
            fseek(file, -size, SEEK_CUR);
            fwrite(&s, sizeof(s), 1, file);
            break;
        }
    }
    fclose(file);
}

void payment()
{
    FILE *file;
    char phonenumber[20];
    long int size = sizeof(s);
    float amt;
    int i;
    if ((file = fopen("file.txt", "rb+")) == NULL)
        exit(0);
    printf("Enter phone number of the subscriber for payment");
    scanf("%s[^\n]", phonenumber);
    fflush(stdin);
    while (fread(&s, sizeof(s), 1, file) == 1)
    {
        if (strcmp(s.phonenumber, phonenumber) == 0)
        {
            printf("\n Phone No.: %s", s.phonenumber);
            printf("\n Name: %s", s.name);
            printf("\n Current amount: %f", s.amount);
            printf("\n");
            for (i = 0; i < 79; i++)
                printf("-");
            printf("\n\nEnter amount of payment :");
            fflush(stdin);
            scanf(" %f", &amt);
            s.amount = s.amount - amt;
            fseek(file, -size, SEEK_CUR);
            fwrite(&s, sizeof(s), 1, file);
            break;
        }
    }
    printf("THANK YOU %s FOR YOUR TIMELY PAYMENTS", s.name);
    fclose(file);
}
