#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Donor
{
    int id;
    char name[50];
    char bloodType[2];
    char Number[15];
    char gender;
    int age;
};

void printMenu();
void add_donor(struct Donor donor[], int *count);
void search_donor(struct Donor donor[], int count);
void view_donor(struct Donor donor[], int count);
void delete_donor();
void update_donor();
void viewBloodStock();
void SavetoFile(struct Donor donor[], int count);
int LoadToFile(struct Donor donor[]);

int main()
{
    struct Donor donors[1000];
    int donorCount = LoadToFile(donors);
    int choice;
    do
    {
        printMenu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            add_donor(donors, &donorCount);
            SavetoFile(donors, donorCount);
            break;
        case 2:
            search_donor(donors, donorCount);
            break;
        case 3:
            update_donor();
            SavetoFile(donors, donorCount);
            break;
        case 4:
            view_donor(donors, donorCount);
            break;
        case 5:
            viewBloodStock();
            break;
        case 6:
            delete_donor();
            break;
        case 7:
            SavetoFile(donors, donorCount);
            printf("Exiting the program. Goodbye!\n");
            return 0;
        default:
            printf("Invalid Input Or Choice");
        }
    } while (choice != 7);
    return 0;
}

// PRINT MENU FUNCTION

void printMenu()
{
    printf("\n================== Welcome to Blood Management System =========================\n");
    printf("\t Enter The choice(1-7): \n");
    printf("\t 1) Add Donor\n");
    printf("\t 2) Search Donor\n");
    printf("\t 3) Update Donor\n");
    printf("\t 4) View Donor\n");
    printf("\t 5) Delete Donor\n");
    printf("\t 6) View Blood Stock\n");
    printf("\t 7) Exit\n");
}

// ADD DONOR FUNCTION

void add_donor(struct Donor donor[], int *count)
{
    if (*count >= 1000)
    {
        printf("Cannot Add More Donor \n");
        return;
    }
    struct Donor newDonor;
    int idExist = 0;
    printf("Add Donor\n");
    printf("Enter ID Donor");
    scanf("%d", &newDonor.id);

    for (int i = 0; i < *count; i++)
    {
        if (donor[i].id == newDonor.id)
        {
            printf("Donor ID already exist! \n");
            idExist = 1;
            break;
        }
    }
    if (idExist)
    {
        return;
    }

    printf("Enter the Name : ");
    scanf("%s", newDonor.name);
    printf("Enter the Age :");
    scanf("%d", &newDonor.age);
    printf("Enter the Phone Number : ");
    scanf("%s", &newDonor.Number);
    printf("Enter the Gender (M/F) : ");
    scanf(" %c", &newDonor.gender);
    printf("Enter the BloodType :");
    scanf("%s", newDonor.bloodType);

    donor[*count] = newDonor;
    (*count)++;

    printf("New Donor Added Succesfully");
}

//! SEARCH DONOR FUNCTION

void search_donor(struct Donor donor[], int count)
{
    if (count == 0)
    {
        printf("No Donor Found\n");
        return;
    }
    int id;
    printf("Enter the ID of the donor to search: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++)
    {
        if (donor[i].id == id)
        {
            printf("Donor Found:\n");
            printf("ID: %d\n", donor[i].id);
            printf("Name: %s\n", donor[i].name);
            printf("Age: %d\n", donor[i].age);
            printf("Phone Number: %s\n", donor[i].Number);
            printf("Gender: %c\n", donor[i].gender);
            printf("Blood Type: %s\n", donor[i].bloodType);
            return;
        }
    }
    printf("Donor with ID %d not found.\n", id);
}

//? DELETE DONOR FUNCTION

void delete_donor()
{
    printf("...");
}
void update_donor()
{
    printf("...");
}
void viewBloodStock()
{
    printf("...");
}

//? VIEW DONOR FUNCTION

void view_donor(struct Donor donor[], int count)

{
    if (count == 0)
    {
        printf("No Donor Found\n");
        return;
    }
    printf("List of Donors:\n");
    for (int i = 0; i < count; i++)
    {
        printf("ID: %d\nName: %s\nAge: %d \nPhone Number: %s\nGender: %c\nBlood Type: %s\n", donor[i].id, donor[i].name, donor[i].age, donor[i].Number, donor[i].gender, donor[i].bloodType);
    }
}

//? SAVE TO FILE FUNCTION

void SavetoFile(struct Donor donor[], int count)
{
    FILE *file = fopen("donors.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d,%s,%d,%s,%c,%s\n", donor[i].id, donor[i].name, donor[i].age, donor[i].Number, donor[i].gender, donor[i].bloodType);
    }
    fclose(file);
    printf("\nData saved successfully to donors.txt\n");
}

//? LOAD TO FILE FUNCTION

int LoadToFile(struct Donor donor[])
{
    FILE *file = fopen("donors.txt", "r");
    if (file == NULL)
    {
        printf("No existing data found . \n");
        return 0;
    }
    int count = 0;
    while (fscanf(file, "%d %s %d %s %c %s", &donor[count].id, donor[count].name, &donor[count].age, &donor[count].Number, &donor[count].gender, donor[count].bloodType) == 6)
    {
        count++;
    }
    fclose(file);
    printf("\nData loaded successfully (%d donors).\n", count);
    return count;
}
