#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define STD_HOURS 40
#define OT_RATE 1.5

typedef struct
{
    char firstName[20];
    char lastName[20];
    long int clockNumber;
    float wage;
    float hours;
    float overtime;
    float gross;
    struct Employee *next;
} Employee;

typedef struct
{
    float totalHours;
    float totalOvertime;
    double totalGross;
    float avgHours;
    float avgOvertime;
    float avgGross;
} Statistics;

/*Funtion Prototypes*/
void file(Employee *head, char *filename);
void getHours(Employee *head);
void otCalc(Employee *head);
void grossCalc(Employee *head);
void printList(Employee *head);
void totalAvg (Employee *head);
void manual(Employee *head);
int menu(void);
