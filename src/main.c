/****************************************************************************/
/* Author      : Mohamed Maged                                              */
/* Version     : V01                                                        */
/* Date        : 19 October 2023                                            */
/* Description : main.c                                                     */
/****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/****************************************************************************/
#include "../inc/STD_TYPES.h"
#include "../inc/ErrorState.h"
#include "../inc/Config.h"
#include "../inc/school.h"
/****************************************************************************/

int main()
{
	List_t* studentList = (List_t*)malloc(sizeof(List_t));
    ErrorState_t result = List_init(studentList);

    if (result != SUCCESS)
    {
        printf("Error initializing the list.\n");
        return 1; // Exit with an error code
    }
    while (1)
    {
        printf("\n==========================================");
        printf("\n----- School Management System Menu ------");
        printf("\n==========================================\n");
        printf("1. Insert a new student\n");
        printf("2. Delete a student\n");
        printf("3. Edit a student\n");
        printf("4. Update a student's scores\n");
        printf("5. Print the list of students\n");
        printf("6. Print the size of the list\n");
        printf("7. Exit\n");
        printf("==========================================\n");
        printf("Enter your choice: ");

        u8 choice;
        scanf("%d", &choice);
        printf("==========================================\n");

        getchar(); // Consume the newline character

        switch (choice) {
            case 1: // Add Student
                printf("Enter Student details:\n");
                ListEntry_t newStudent;
                printf("Enter student ID: ");
                scanf("%d", &newStudent.ID);
                getchar(); // Consume the newline character
                printf("Enter student name: ");
                fgets(newStudent.Name, sizeof(newStudent.Name), stdin);
                newStudent.Name[strcspn(newStudent.Name, "\n")] = 0; // Remove the newline character
                printf("Enter student age: ");
                scanf("%d", &newStudent.age);
                getchar(); // Consume the newline character
                printf("Enter student phone: (+20)");
                scanf("%lu", &newStudent.data.phone);
                getchar(); // Consume the newline character
                printf("Enter student address: ");
                fgets(newStudent.data.address, sizeof(newStudent.data.address), stdin);
                newStudent.data.address[strcspn(newStudent.data.address, "\n")] = 0; // Remove the newline character
                printf("Enter Math Degree: ");
                scanf("%d", &newStudent.degress.math_deg);
                getchar(); // Consume the newline character
                printf("Enter English Degree: ");
                scanf("%d", &newStudent.degress.english_deg);
                getchar(); // Consume the newline character
                printf("Enter Arabic Degree: ");
                scanf("%d", &newStudent.degress.arabic_deg);
                getchar(); // Consume the newline character

                List_insertStudent(studentList, &newStudent);
                printf("Student inserted successfully.\n");
                break;

            case 2: // Delete Student
            {
                u8 deleteID;
                printf("Enter the ID of the student to delete: ");
                scanf("%d", &deleteID);
                getchar(); // Consume the newline character
                if (List_deleteStudent(studentList, deleteID) == SUCCESS)
                {
                    printf("Student with ID %d deleted successfully.\n", deleteID);
                }
                else
                {
                    printf("Student with ID %d not found.\n", deleteID);
                }
                break;
            }
            case 3: // Edit Student
            {
                u8 editID;
                printf("Enter the ID of the student to edit: ");
                scanf("%d", &editID);
                getchar(); // Consume the newline character
                if (List_editStudent(studentList, editID) == SUCCESS) {
                    printf("Student with ID %d edited successfully.\n", editID);
                } else {
                    printf("Student with ID %d not found.\n", editID);
                }
                break;
            }
            case 4: // Update Student's Scores
            {
                u8 updateID;
                printf("Enter the ID of the student to update scores: ");
                scanf("%d", &updateID);
                getchar(); // Consume the newline character
                if (List_updateScore(studentList, updateID) == SUCCESS) {
                    printf("Student with ID %d scores updated successfully.\n", updateID);
                } else {
                    printf("Student with ID %d not found.\n", updateID);
                }
                break;
            }
            case 5: // Print List of Students
            {
                if (List_printList(studentList) == NULL_PTR) {
                    printf("The list is empty.\n");
                }
                break;
            }
            case 6: // List Size
            {
                u32 listSize;
                if (List_listSize(studentList, &listSize) == SUCCESS) {
                    printf("Number of Students in the list: %lu\n", listSize);
                } else {
                    printf("Error getting list size.\n");
                }
                break;
            }
            case 7: // Quit
                List_freeList(studentList);
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}



