#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    char surname[50];
    char group[10];
    int course;
    int id;
};



// Function to remove a student from the database
void removeStudent(FILE *file, int id) {
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temp file");
        return;
    }

    struct Student student;
    int found = 0;

    while (fscanf(file, "%s %s %s %d %d\n", student.name, student.surname, student.group, &student.course, &student.id) != EOF) {
        if (student.id == id) {
            found = 1;
            continue; // Skip this student
        }
        fprintf(tempFile, "%s %s %s %d %d\n", student.name, student.surname, student.group, student.course, student.id);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("database.txt");
        rename("temp.txt", "database.txt");
        printf("Student with ID %d removed successfully!\n", id);
    } else {
        remove("temp.txt");
        printf("Student with ID %d not found in the database.\n", id);
    }
}

// Function to edit a student's information
void editStudent(FILE *file, int id) {
    struct Student student;
    int found = 0;

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temp file");
        return;
    }

    while (fscanf(file, "%s %s %s %d %d\n", student.name, student.surname, student.group, &student.course, &student.id) != EOF) {
        if (student.id == id) {
            found = 1;
            printf("Enter new student details:\n");
            printf("Name: ");
            scanf("%s", student.name);
            printf("Surname: ");
            scanf("%s", student.surname);
            printf("Group: ");
            scanf("%s", student.group);
            printf("Course: ");
            scanf("%d", &student.course);
            printf("ID: ");
            scanf("%d", &student.id);
        }
        fprintf(tempFile, "%s %s %s %d %d\n", student.name, student.surname, student.group, student.course, student.id);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("database.txt");
        rename("temp.txt", "database.txt");
        printf("Student with ID %d edited successfully!\n", id);
    } else {
        remove("temp.txt");
        printf("Student with ID %d not found in the database.\n", id);
    }
}

// Function to search for a student by ID
void searchStudent(FILE *file, int id) {
    struct Student student;
    int found = 0;

    while (fscanf(file, "%s %s %s %d %d\n", student.name, student.surname, student.group, &student.course, &student.id) != EOF) {
        if (student.id == id) {
            found = 1;
            printf("Student found:\n");
            printf("Name: %s\n", student.name);
            printf("Surname: %s\n", student.surname);
            printf("Group: %s\n", student.group);
            printf("Course: %d\n", student.course);
            printf("ID: %d\n", student.id);
            break; // Stop searching after finding the student
        }
    }

    if (!found) {
        printf("Student with ID %d not found in the database.\n", id);
    }
}

void showAllStudents(FILE *file) {
    rewind(file); // Move the file pointer to the beginning

    struct Student student;

    printf("List of all students:\n");
    while (fscanf(file, "%s %s %s %d %d\n", student.name, student.surname, student.group, &student.course, &student.id) != EOF) {
        printf("Name: %s\n", student.name);
        printf("Surname: %s\n", student.surname);
        printf("Group: %s\n", student.group);
        printf("Course: %d\n", student.course);
        printf("ID: %d\n", student.id);
        printf("--------------------\n");
    }
}

int main() {
    FILE *file = fopen("database.txt", "a+");

    if (file == NULL) {
        perror("Error opening database file");
        return 1;
    }

    int choice;
    int id;

    while (1) {
        printf("\nStudent Database Menu:\n");
        printf("1. Add Student\n");
        printf("2. Remove Student\n");
        printf("3. Edit Student\n");
        printf("4. Search Student\n");
        printf("5. Show All Students\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(file);
                break;
            case 2:
                printf("Enter the ID of the student to remove: ");
                scanf("%d", &id);
                removeStudent(file, id);
                break;
            case 3:
                printf("Enter the ID of the student to edit: ");
                scanf("%d", &id);
                editStudent(file, id);
                break;
            case 4:
                printf("Enter the ID of the student to search: ");
                scanf("%d", &id);
                searchStudent(file, id);
                break;
            case 5:
                showAllStudents(file);
                break;
            case 6:
                fclose(file);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
