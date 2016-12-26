#include "PayCalc.h"

int menu(void) {
    
    int choice;

    printf("\n\n");
    printf("'||''|.                                   '||          \n");
    printf(" ||   ||  ....   .... ...   ....   ....    ||    ....  \n");
    printf(" ||...|' '' .||   '|.  |  .|   '' '' .||   ||  .|   '' \n");
    printf(" ||      .|' ||    '|.|   ||      .|' ||   ||  ||      \n");
    printf(".||.     '|..'|'    '|     '|...' '|..'|' .||.  '|...' \n");
    printf("                  .. |                                 \n");
    printf("                  ''                                   \n");
    printf("\n\n");
    printf("Please select input mode:\n1= file input mode\n2= manual input mode\n3=Quit\n");
    fflush(stdin);
    scanf("%d",&choice);
    if (choice==3) exit(0);
    else return(choice);
    }

void manual(Employee *head) {

    Employee *current;
    current=head;
    int more_data=1;
    char answer[8];     /* to see if the user wants to add more employees */

    while (more_data) {
        
        printf ("\nEnter employee first name: ");
        scanf ("%s", &current->firstName);
        
        printf ("\nEnter employee last name: ");
        scanf ("%s", &current->lastName);
        
        /* Read in Employee ID and Hourly Wage */
        printf("\nEnter employee ID: ");
        scanf("%li", &current->clockNumber);
        
        printf("\nEnter employee hourly wage: ");
        scanf("%f", &current->wage);
        
        printf("\nWould you like to add another employee? (y/n): ");
        scanf("%s", answer);
        
        /* Ask user if they want to add another employee */
        if (toupper(answer[0]) != 'Y') {
            current->next = (struct employee *) NULL;
            more_data = 0;
            getHours(head);
        }
        else {
            /* set the next pointer of the current node to point to the new node */
            current->next=(Employee *)malloc(sizeof(Employee));
            /* move the current node pointer to the new node */
            current = current->next;
        }
    }
    otCalc(head);
    grossCalc(head);
    printList(head);
    totalAvg(head);
}

void file(Employee *head, char *filename) {

    Employee *current;  /*pointer to current node*/
    current=head;
    FILE *fp;

    if (!(fp=fopen(filename,"r"))){
		printf("cannot open %s for reading\n",filename); //Open filename
        //perror(void);
	}
		
	while (fscanf(fp,"%li %s %s %f %f",
                &current->clockNumber,
                &current->firstName,
                &current->lastName,
                &current->wage,
                &current->hours) 
             	&& !feof(fp))
	{
		current->next=(struct Employee *)malloc(sizeof(Employee));
        current=current->next;
    }
    	current->next=(struct Employee *)NULL;
        fclose(fp);

        otCalc(head);
        grossCalc(head);
        printList(head);
        totalAvg(head);
}

void getHours (Employee *empl)
{
    Employee *tmp;   /* tmp pointer value to current node */
    
    for(tmp = empl; tmp ; tmp = tmp->next)
    {
        printf ("\nEnter hours for employee %06li:  ", tmp -> clockNumber);
        scanf ("%f", &tmp -> hours);
    }
}

void grossCalc (Employee * empl)
{
    Employee *tmp;
    
    for(tmp = empl; tmp ; tmp = tmp->next) {
        if (tmp -> hours >= STD_HOURS)
            
            tmp -> gross =
            ((tmp -> wage) * STD_HOURS) + (OT_RATE * (tmp -> wage)) * (tmp -> overtime);
        else
            (tmp -> gross) = (tmp -> hours) * (tmp -> wage);
    }
}

void otCalc (Employee *empl)
{
    
    Employee *tmp;
    
    for(tmp = empl; tmp ; tmp = tmp->next)
    {
        if (tmp -> hours >= STD_HOURS)
            
            tmp -> overtime = (tmp -> hours - STD_HOURS);
        
        else
            tmp -> overtime = 0;
    }
}

void totalAvg (Employee *empl)
{
    int size=0;
    Employee *tmp;
    Statistics stats;
    
    for(tmp = empl; tmp ; tmp = tmp->next) {
        stats.totalHours += tmp->hours;
        stats.totalOvertime += tmp->overtime;
        stats.totalGross += tmp->gross;
        ++size;
    }
    
    stats.avgHours = stats.totalHours / size;
    stats.avgOvertime = stats.totalOvertime / size;
    stats.avgGross = stats.totalGross / size;

    printf ("----------------------------------------------------------------\n");
    printf ("                               Total:   %06.02f   %06.02f  %7.02f\n",
            stats.totalHours, stats.totalOvertime, stats.totalGross);
    printf ("                             Average:   %06.02f   %06.02f  %6.02f\n",
            stats.avgHours, stats.avgOvertime, stats.avgGross);
}

void printList(Employee *empl)
{
    Employee *tmp;   /* tmp pointer value to current node */
    
    printf ("\n-----------------------------------------------------------------\n");
    printf ("Name                  Clock#    Wage    Hours    OT      Gross\n");
    printf ("-----------------------------------------------------------------\n");
    /* Start a beginning of list and print out each value               */
    /* loop until tmp points to null (remember null is 0 or false)      */
    for(tmp = empl; tmp ; tmp = tmp->next)
    {
        printf ("%-10s %-10s %06li    %05.2f   %06.2f   %05.2f   %6.2f\n",
                tmp -> firstName,
                tmp -> lastName,
                tmp -> clockNumber,
                tmp -> wage,
                tmp -> hours,
                tmp -> overtime,
                tmp -> gross);  
    }   
}

int main (int argc, char** argv)
{
    Employee *head;     /*always points to first node*/
    char filename[80];

    /* Set up storage for first node */
    head=(Employee *)malloc(sizeof(Employee));
    
    /*Exit if there are wrong number arguments*/
    if (argc == 2 || argc > 3) {
        printf ("Usage: Paycalc -f [filename]\nor\nPaycalc");
        exit(2);
    }
    /*Check for valid command line flags*/
    if (argc == 3 && argv[1][0]=='-' && argv[1][1]=='f') {
        strcpy(filename,argv[2]);
        file(head,filename);
        exit(0);
    }
    else
        printf ("Usage: Paycalc -f [filename]\nor\nPaycalc\n");
    
    for (;;) {
        switch(menu()) {
            case 1:
              printf ("Enter file name:\n");
              scanf ("%s", &filename[0]);
              file(head,filename);
              break;
            case 2:
              manual(head);
              break;
            default:
              printf ("Invalid usage.\n");
              break;
          }
      }
}
