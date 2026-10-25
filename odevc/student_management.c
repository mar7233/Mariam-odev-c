#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int numara;
    char ad[50];
    char soyad[50];
    char bolum[100];
    int sinif;
} Student;

#define FILE_NAME "students.txt" 


void addStudent();
void findStudent();
void deleteStudent();
void editStudent();
void listStudents();

int main() {
    int choice;

    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Find Student\n");
        printf("3. Delete Student\n");
        printf("4. Edit Student\n");
        printf("5. List Students\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            findStudent();
            break;
        case 3:
            deleteStudent();
            break;
        case 4:
            editStudent();
            break;
        case 5:
            listStudents();
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}

void addStudent() {
    FILE* file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Student student;
    printf("Enter student number: ");
    scanf_s("%d", &student.numara);
    getchar(); 

    printf("Enter first name: ");
    fgets(student.ad, sizeof(student.ad), stdin);
    student.ad[strcspn(student.ad, "\n")] = 0; 

    printf("Enter last name: ");
    fgets(student.soyad, sizeof(student.soyad), stdin);
    student.soyad[strcspn(student.soyad, "\n")] = 0; 

    printf("Enter department: ");
    fgets(student.bolum, sizeof(student.bolum), stdin);
    student.bolum[strcspn(student.bolum, "\n")] = 0; 

    printf("Enter class: ");
    scanf_s("%d", &student.sinif);

    fprintf(file, "%d\n%s\n%s\n%s\n%d\n", student.numara, student.ad, student.soyad, student.bolum, student.sinif);
    fclose(file);
    printf("Student added successfully!\n");
}

void findStudent() {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int numara;
    printf("Enter student number to search: ");
    scanf_s("%d", &numara);

    Student student;
    int found = 0;
    while (fscanf_s(file, "%d\n", &student.numara) != EOF) {
        fgets(student.ad, sizeof(student.ad), file);
        student.ad[strcspn(student.ad, "\n")] = 0;

        fgets(student.soyad, sizeof(student.soyad), file);
        student.soyad[strcspn(student.soyad, "\n")] = 0;

        fgets(student.bolum, sizeof(student.bolum), file);
        student.bolum[strcspn(student.bolum, "\n")] = 0;

        fscanf_s(file, "%d\n", &student.sinif);

        if (student.numara == numara) {
            printf("\nStudent found:\n");
            printf("Number: %d\nName: %s %s\nDepartment: %s\nClass: %d\n",
                student.numara, student.ad, student.soyad, student.bolum, student.sinif);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found!\n");
    }

    fclose(file);
}

void deleteStudent() {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(file);
        return;
    }

    int numara;
    printf("Enter student number to delete: ");
    scanf_s("%d", &numara);

    Student student;
    int found = 0;
    while (fscanf_s(file, "%d\n", &student.numara) != EOF) {
        fgets(student.ad, sizeof(student.ad), file);
        student.ad[strcspn(student.ad, "\n")] = 0;

        fgets(student.soyad, sizeof(student.soyad), file);
        student.soyad[strcspn(student.soyad, "\n")] = 0;

        fgets(student.bolum, sizeof(student.bolum), file);
        student.bolum[strcspn(student.bolum, "\n")] = 0;

        fscanf_s(file, "%d\n", &student.sinif);

        if (student.numara != numara) {
            fprintf(tempFile, "%d\n%s\n%s\n%s\n%d\n", student.numara, student.ad, student.soyad, student.bolum, student.sinif);
        }
        else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("Student deleted successfully!\n");
    }
    else {
        printf("Student not found!\n");
    }
}

void editStudent() {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(file);
        return;
    }

    int numara;
    printf("Enter student number to edit: ");
    scanf_s("%d", &numara);
    getchar(); 

    Student student;
    int found = 0;
    while (fscanf_s(file, "%d\n", &student.numara) != EOF) {
        fgets(student.ad, sizeof(student.ad), file);
        student.ad[strcspn(student.ad, "\n")] = 0;

        fgets(student.soyad, sizeof(student.soyad), file);
        student.soyad[strcspn(student.soyad, "\n")] = 0;

        fgets(student.bolum, sizeof(student.bolum), file);
        student.bolum[strcspn(student.bolum, "\n")] = 0;

        fscanf_s(file, "%d\n", &student.sinif);

        if (student.numara == numara) {
            found = 1;

            printf("Enter new first name: ");
            fgets(student.ad, sizeof(student.ad), stdin);
            student.ad[strcspn(student.ad, "\n")] = 0;

            printf("Enter new last name: ");
            fgets(student.soyad, sizeof(student.soyad), stdin);
            student.soyad[strcspn(student.soyad, "\n")] = 0;

            printf("Enter new department: ");
            fgets(student.bolum, sizeof(student.bolum), stdin);
            student.bolum[strcspn(student.bolum, "\n")] = 0;

            printf("Enter new class: ");
            scanf_s("%d", &student.sinif);
        }

        fprintf(tempFile, "%d\n%s\n%s\n%s\n%d\n", student.numara, student.ad, student.soyad, student.bolum, student.sinif);
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("Student updated successfully!\n");
    }
    else {
        printf("Student not found!\n");
    }
}

void listStudents() {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nList of students:\n");
    Student student;
    while (fscanf_s(file, "%d\n", &student.numara) != EOF) {
        fgets(student.ad, sizeof(student.ad), file);
        student.ad[strcspn(student.ad, "\n")] = 0;

        fgets(student.soyad, sizeof(student.soyad), file);
        student.soyad[strcspn(student.soyad, "\n")] = 0;

        fgets(student.bolum, sizeof(student.bolum), file);
        student.bolum[strcspn(student.bolum, "\n")] = 0;

        fscanf_s(file, "%d\n", &student.sinif);

        printf("Number: %d\nName: %s %s\nDepartment: %s\nClass: %d\n\n",
            student.numara, student.ad, student.soyad, student.bolum, student.sinif);
    }

    fclose(file);
}
