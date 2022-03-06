/**********************************  Moghared Wahid  ************************************/
/******************************  mogharedwahid@gmail.com  *******************************/
/*****************************  Clinic Management System  *******************************/
/****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct patient{
	char name[20];
	char gender;
	int age,id,slot;
}patients[20];

int p_counter=0;

int slotsCheck[5]={0,0,0,0,0};

char slots[][20]={"from 2pm to 2:30pm","from 2:30pm to 3pm",\
				  "from 3pm to 3:30pm","from 4pm to 4:30pm",\
				  "from 4:30pm to 5pm"};


int choose_mode();
int check_password(); // boolean
int check_add_id();    // -1 if already in list or the id to be added
int check_id();		  // -1 if not found or index of ID if in list
int admin_choices();
void add_patient(int id);
void edit_patient_record(int index);
void reserve_slot(int index);
void cancel_reservation(int index);
int user_choices();
void view_patient_record(int index);
void view_todays_reservation(int index);


int main()
{
	int mode=0;
	while(1)
    {
		mode=choose_mode();
        if(mode==1) // Admin mode
		{
			system("cls");
			printf("\n*** Admin mode ***\n");
			int password=check_password();
			if(password==1)
			{
				int choice=admin_choices();
				if(choice==1) //Add Patient
				{
					system("cls");
					int check=check_add_id();
					if(check==-1)
					{
						printf("\nID already on the system !\n");
					}
					else
					{
						add_patient(check);
					}
				}
				else if(choice==2) //Edit patient record
				{
					system("cls");
					int check=check_id();
					if(check==-1)
					{
						printf("\nIncorrect ID !\n");
					}
					else
					{
						edit_patient_record(check);
					}
				}
				else if(choice==3) // Reserve a slot
				{
					system("cls");
					int check=check_id();
					if(check==-1)
					{
						printf("\nNot found on the system !\n");
					}
					else
					{
						reserve_slot(check);
					}
				}
				else if(choice==4) // Cancel reservation
				{
					system("cls");
					int check=check_id();
					if(check==-1)
					{
						printf("\nNot found on the system !\n");
					}
					else
					{
						cancel_reservation(check);
					}
				}
			}
			else
			{
				printf("\n*** System Locked ***\n");
			}
		}
		else if(mode==2) // User mode
		{
			system("cls");
			printf("\n*** User mode ***\n");
			int choice=user_choices();
			if(choice==1) // View Patient Record 
			{
				system("cls");
				int check=check_id();
				if(check==-1)
				{
					printf("\nNot found on the system !\n");
				}
				else
				{
					view_patient_record(check);
				}
			}
			else if(choice==2) // View today's reservation
			{
				system("cls");
				int check=check_id();
				if(check==-1)
				{
					printf("\nNot found on the system!\n");
				}
				else
				{
					view_todays_reservation(check);
				}
			}
		}
		else   //wrong input
		{
			printf("\n*** Wrong input ***\n");
		}
    }
}


int choose_mode()
{
	int mode;
	printf("\n|***********************|\n");
	printf("|  1. Admin mode        |\n");
	printf("|  2. User mode         |\n");
	printf("|***********************|\n");
	printf("Enter your mode: ");
	scanf("%d",&mode);
	return mode;
}

int check_password()
{
	int password=0;
    int attempts = 0;
    while ( password != 1234 && attempts < 3 )
    {
        printf("\nEnter password: ");
		scanf("%d",&password);
        attempts++;
    }
    if (password == 1234 && attempts <= 3 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_add_id()
{
	int id;
	printf("Enter your ID no. : ");
    scanf("%d",&id);
    for(int i=0; i<=p_counter; i++)
    {
        if(id==patients[i].id)
		{
			id=-1;
			return id;
		}
    }
	return id;
}

int check_id()
{
	int id,check=-1;
	printf("Enter your ID no. : ");
    scanf("%d",&id);
    for(int i=0; i<=p_counter; i++)
    {
        if(id==patients[i].id)
		{
			check=i;
			return check;
		}
    }
	return check;
}

int admin_choices()
{
	int choice;
	printf("\n|*******************************************|\n");
	printf("|  1. Add a new patient                     |\n");
	printf("|  2. Edit a patient record enter           |\n");
	printf("|  3. Reserve a slot with the doctor enter  |\n");
	printf("|  4. Cancel the reservation enter          |\n");
	printf("|*******************************************|\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);
	return choice;
}

void add_patient(int id)
{
	patients[p_counter].id=id;
    fflush(stdin);
    printf("Enter patient's Name : ");
    gets(patients[p_counter].name);
    printf("Enter age : ");
    scanf("%d",&patients[p_counter].age);
    printf("Enter gender(m=male / f=female) : ");
    scanf(" %c",&patients[p_counter].gender);
	patients[p_counter].slot=-1;
    p_counter++;
}

void edit_patient_record(int index)
{
	fflush(stdin);
    printf("Enter patient's Name : ");
    gets(patients[index].name);
    printf("Enter age : ");
    scanf("%d",&patients[index].age);
    printf("Enter gender(m=male / f=female) : ");
    scanf(" %c",&patients[index].gender);
}

void reserve_slot(int index)
{
	if(patients[index].slot==-1)
	{
		int choice;
		for(int i=0;i<5;i++)
		{
			if(slotsCheck[i]==1)
			{
				continue;
			}
			printf("%d. %s\n",i+1,slots[i]);
		}
		printf("Enter your slot: ");
		scanf("%d",&choice);
		if(slotsCheck[choice-1]==1)
		{
			printf("\nSlot already reserved !\n");
			return;
		}
		else
		{
			slotsCheck[choice-1]=1;
			patients[index].slot=choice;
			return;
		}
	}
	else
	{
		printf("%s,",patients[index].name);
		printf(" you already have a reservation");
		printf(" %s\n",slots[patients[index].slot-1]);
		return;
	}
	int choice;
	for(int i=0;i<5;i++)
	{
		if(slotsCheck[i]==1)
		{
			continue;
		}
		printf("%d. %s\n",i+1,slots[i]);
	}
	printf("Enter your slot: ");
	scanf("%d",&choice);
	if(slotsCheck[choice-1]==1)
	{
		printf("\nSlot already reserved !\n");
	}
	else
	{
		slotsCheck[choice-1]=1;
		patients[index].slot=choice;
	}
}

void cancel_reservation(int index)
{
	int s=patients[index].slot;
	patients[index].slot=-1;
	slotsCheck[s-1]=0;
	printf("\nReservarion cancelled !\n");
}

int user_choices()
{
	int choice;
	printf("\n|*******************************************|\n");
	printf("|  1. View patient record                   |\n");
	printf("|  2. View todays reservations              |\n");
	printf("|*******************************************|\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);
	return choice;
}

void view_patient_record(int index)
{
	printf("ID: %d\n",patients[index].id);
	printf("Name: %s\n",patients[index].name);
	printf("Age: %d\n",patients[index].age);
	printf("Gender: %c\n",patients[index].gender);
}

void view_todays_reservation(int index)
{
	int s=patients[index].slot;
	if(s==-1)
	{
		printf("%s,",patients[index].name);
		printf(" you have no reservations !");
	}
	else
	{
		printf("%s,",patients[index].name);
		printf(" your reservation is");
		printf(" %s\n",slots[s-1]);
	}
}