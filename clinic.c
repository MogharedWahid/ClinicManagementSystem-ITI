/**********************************  Moghared Wahid  ************************************/
/******************************  mogharedwahid@gmail.com  *******************************/
/*****************************  Clinic Management System  *******************************/
/****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 20
#define PASSWORD 1234
#define MAX_ATTEMPTS 3

typedef struct {
    char name[20];
    char gender;
    int age, id, slot;
} Patient;

Patient patients[MAX_PATIENTS];
int p_counter = 0;
int slotsCheck[5] = {0, 0, 0, 0, 0};
const char *slots[] = {
    "from 2pm to 2:30pm",
    "from 2:30pm to 3pm",
    "from 3pm to 3:30pm",
    "from 4pm to 4:30pm",
    "from 4:30pm to 5pm"
};

typedef enum {
    ADMIN_MODE = 1,
    USER_MODE
} Mode;

typedef enum {
    ADD_PATIENT = 1,
    EDIT_PATIENT,
    RESERVE_SLOT,
    CANCEL_RESERVATION
} AdminChoice;

typedef enum {
    VIEW_PATIENT_RECORD = 1,
    VIEW_TODAYS_RESERVATION
} UserChoice;

int choose_mode();
int check_password();
int check_add_id();
int check_id();
int admin_choices();
void add_patient(int id);
void edit_patient_record(int index);
void reserve_slot(int index);
void cancel_reservation(int index);
int user_choices();
void view_patient_record(int index);
void view_todays_reservation(int index);

int main() {
    int mode = 0;
    while (1) {
        mode = choose_mode();
        if (mode == ADMIN_MODE) {
            system("cls");
            printf("\n*** Admin mode ***\n");
            if (check_password()) {
                int choice = admin_choices();
                switch (choice) {
                    case ADD_PATIENT:
                        system("cls");
                        int id = check_add_id();
                        if (id == -1) {
                            printf("\nID already on the system!\n");
                        } else {
                            add_patient(id);
                        }
                        break;
                    case EDIT_PATIENT:
                        system("cls");
                        int index = check_id();
                        if (index == -1) {
                            printf("\nIncorrect ID!\n");
                        } else {
                            edit_patient_record(index);
                        }
                        break;
                    case RESERVE_SLOT:
                        system("cls");
                        index = check_id();
                        if (index == -1) {
                            printf("\nNot found on the system!\n");
                        } else {
                            reserve_slot(index);
                        }
                        break;
                    case CANCEL_RESERVATION:
                        system("cls");
                        index = check_id();
                        if (index == -1) {
                            printf("\nNot found on the system!\n");
                        } else {
                            cancel_reservation(index);
                        }
                        break;
                    default:
                        printf("\nInvalid choice!\n");
                        break;
                }
            } else {
                printf("\n*** System Locked ***\n");
            }
        } else if (mode == USER_MODE) {
            system("cls");
            printf("\n*** User mode ***\n");
            int choice = user_choices();
            switch (choice) {
                case VIEW_PATIENT_RECORD:
                    system("cls");
                    int index = check_id();
                    if (index == -1) {
                        printf("\nNot found on the system!\n");
                    } else {
                        view_patient_record(index);
                    }
                    break;
                case VIEW_TODAYS_RESERVATION:
                    system("cls");
                    index = check_id();
                    if (index == -1) {
                        printf("\nNot found on the system!\n");
                    } else {
                        view_todays_reservation(index);
                    }
                    break;
                default:
                    printf("\nInvalid choice!\n");
                    break;
            }
        } else {
            printf("\n*** Wrong input ***\n");
        }
    }
}

int choose_mode() {
    int mode;
    printf("\n|***********************|\n");
    printf("|  1. Admin mode        |\n");
    printf("|  2. User mode         |\n");
    printf("|***********************|\n");
    printf("Enter your mode: ");
    scanf("%d", &mode);
    return mode;
}

int check_password() {
    int password = 0;
    int attempts = 0;
    while (password != PASSWORD && attempts < MAX_ATTEMPTS) {
        printf("\nEnter password: ");
        scanf("%d", &password);
        attempts++;
    }
    return (password == PASSWORD);
}

int check_add_id() {
    int id;
    printf("Enter your ID no.: ");
    scanf("%d", &id);
    for (int i = 0; i < p_counter; i++) {
        if (id == patients[i].id) {
            return -1;
        }
    }
    return id;
}

int check_id() {
    int id;
    printf("Enter your ID no.: ");
    scanf("%d", &id);
    for (int i = 0; i < p_counter; i++) {
        if (id == patients[i].id) {
            return i;
        }
    }
    return -1;
}

int admin_choices() {
    int choice;
    printf("\n|*******************************************|\n");
    printf("|  1. Add a new patient                     |\n");
    printf("|  2. Edit a patient record                 |\n");
    printf("|  3. Reserve a slot with the doctor        |\n");
    printf("|  4. Cancel the reservation                |\n");
    printf("|*******************************************|\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void add_patient(int id) {
    if (p_counter >= MAX_PATIENTS) {
        printf("Patient list is full!\n");
        return;
    }
    patients[p_counter].id = id;
    fflush(stdin);
    printf("Enter patient's Name: ");
    fgets(patients[p_counter].name, sizeof(patients[p_counter].name), stdin);
    strtok(patients[p_counter].name, "\n"); // Remove newline character
    printf("Enter age: ");
    scanf("%d", &patients[p_counter].age);
    printf("Enter gender (m=male / f=female): ");
    scanf(" %c", &patients[p_counter].gender);
    patients[p_counter].slot = -1;
    p_counter++;
}

void edit_patient_record(int index) {
    fflush(stdin);
    printf("Enter patient's Name: ");
    fgets(patients[index].name, sizeof(patients[index].name), stdin);
    strtok(patients[index].name, "\n"); // Remove newline character
    printf("Enter age: ");
    scanf("%d", &patients[index].age);
    printf("Enter gender (m=male / f=female): ");
    scanf(" %c", &patients[index].gender);
}

void reserve_slot(int index) {
    if (patients[index].slot != -1) {
        printf("%s, you already have a reservation %s\n", patients[index].name, slots[patients[index].slot - 1]);
        return;
    }
    int choice;
    for (int i = 0; i < 5; i++) {
        if (slotsCheck[i] == 0) {
            printf("%d. %s\n", i + 1, slots[i]);
        }
    }
    printf("Enter your slot: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > 5 || slotsCheck[choice - 1] == 1) {
        printf("\nInvalid or already reserved slot!\n");
    } else {
        slotsCheck[choice - 1] = 1;
        patients[index].slot = choice;
    }
}

void cancel_reservation(int index) {
    int s = patients[index].slot;
    if (s == -1) {
        printf("No reservation to cancel!\n");
        return;
    }
    patients[index].slot = -1;
    slotsCheck[s - 1] = 0;
    printf("\nReservation cancelled!\n");
}

int user_choices() {
    int choice;
    printf("\n|*******************************************|\n");
    printf("|  1. View patient record                   |\n");
    printf("|  2. View today's reservations             |\n");
    printf("|*******************************************|\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void view_patient_record(int index) {
    printf("ID: %d\n", patients[index].id);
    printf("Name: %s\n", patients[index].name);
    printf("Age: %d\n", patients[index].age);
    printf("Gender: %c\n", patients[index].gender);
}

void view_todays_reservation(int index) {
    int s = patients[index].slot;
    if (s == -1) {
        printf("%s, you have no reservations!\n", patients[index].name);
    } else {
        printf("%s, your reservation is %s\n", patients[index].name, slots[s - 1]);
    }
}
