/****************************************************************************/
/* Author      : Mohamed Maged                                              */
/* Version     : V01                                                        */
/* Date        : 19 October 2023                                            */
/* Description : school.c                                                   */
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

ErrorState_t List_init(List_t* pl)
{
    if (pl != NULL)
    {
        pl->pHead = NULL;
        pl->pTail = NULL;
        pl->ListSize = 0;
        return SUCCESS;
    }
    return NULL_PTR;
}
/****************************************************************************/

ErrorState_t List_insertStudent(List_t* pl, const ListEntry_t* pe)
{
    if (pl != NULL && pe != NULL)
    {
        ListNode_t* newNode = (ListNode_t*)malloc(sizeof(ListNode_t));
        if (newNode != NULL)
		{
            newNode->entry = *pe;
            newNode->pNext = NULL;
            newNode->pPrev = NULL;

            if (pl->pHead == NULL)
			{
                // The list is empty, insert at the head
                pl->pHead = newNode;
                pl->pTail = newNode;
                pl->ListSize++;
                return SUCCESS;
            }
            else
            {
                // Insert the new node in alphabetical order
                ListNode_t* currentNode = pl->pHead;
                ListNode_t* previousNode = NULL;

                while (currentNode != NULL && strcmp(pe->Name, currentNode->entry.Name) > 0)
                {
                    previousNode = currentNode;
                    currentNode = currentNode->pNext;
                }

                if (previousNode == NULL)
                {
                    // Insert at the head
                    newNode->pNext = pl->pHead;
                    pl->pHead->pPrev = newNode;
                    pl->pHead = newNode;
                }
                else if (currentNode == NULL)
                {
                    // Insert at the tail
                    previousNode->pNext = newNode;
                    newNode->pPrev = previousNode;
                    pl->pTail = newNode;
                }
                else
                {
                    // Insert in the middle
                    previousNode->pNext = newNode;
                    newNode->pPrev = previousNode;
                    newNode->pNext = currentNode;
                    currentNode->pPrev = newNode;
                }

                pl->ListSize++;
                return SUCCESS;
            }
        }
        else
        {
            return NULL_PTR;
        }
    }
    return NULL_PTR;
}
/****************************************************************************/
ErrorState_t List_searchStudent(const List_t* pl, u8 copy_u8ID, ListNode_t** pFoundStudent)
{
    if (pl != NULL && pFoundStudent != NULL)
    {
        ListNode_t* currentNode = pl->pHead;
        while (currentNode != NULL)
        {
            if (currentNode->entry.ID == copy_u8ID)
            {
                *pFoundStudent = currentNode;
                return SUCCESS;
            }
            currentNode = currentNode->pNext;
        }
        return OUT_OF_RANGE_ERR;
    }
    return NULL_PTR;
}
/****************************************************************************/
ErrorState_t List_deleteStudent(List_t* pl, u8 copy_u8ID)
{
    if (pl != NULL)
	{
        ListNode_t* foundStudent;
        ErrorState_t result = List_searchStudent(pl, copy_u8ID, &foundStudent);
        if (result == SUCCESS)
		{
            // Remove the found student from the list
            if (foundStudent->pPrev != NULL)
			{
                foundStudent->pPrev->pNext = foundStudent->pNext;
            }
			else
			{
                // The found student is at the head
                pl->pHead = foundStudent->pNext;
            }

            if (foundStudent->pNext != NULL)
			{
                foundStudent->pNext->pPrev = foundStudent->pPrev;
            }
			else
			{
                // The found student is at the tail
                pl->pTail = foundStudent->pPrev;
            }

            free(foundStudent);
            pl->ListSize--;
            return SUCCESS;
        }
		else
		{
            return result;
        }
    }
    return NULL_PTR;
}
/****************************************************************************/
ErrorState_t List_editStudent(const List_t* pl, u8 copy_u8ID)
{
	u8 Localu8ChosenNumber = 0;
    if (pl != NULL)
	{
        ListNode_t* foundStudent;
        ErrorState_t result = List_searchStudent(pl, copy_u8ID, &foundStudent);
        if (result == SUCCESS)
		{
			/* EDIT */
			printf("1) Student ID: %d \n",foundStudent->entry.ID);
			printf("2) Student Name: %s \n",foundStudent->entry.Name);
			printf("3) Student Age: %d \n",foundStudent->entry.age);
			printf("4) Student Phone: %lu \n",foundStudent->entry.data.phone);
			printf("5) Student Address: %s \n",foundStudent->entry.data.address);
			printf("Choose the number to edit [1-5]: ");
			scanf("%d",&Localu8ChosenNumber);
			switch (Localu8ChosenNumber)
			{
			      case 1:
			          printf("[NEW] Student ID: ");
			          scanf("%d", &foundStudent->entry.ID);
			          break;
			      case 2:
			          printf("[NEW] Student Name: ");
			          scanf("%s", foundStudent->entry.Name);
			          break;
			      case 3:
			          printf("[NEW] Student Age: ");
			          scanf("%d", &foundStudent->entry.age);
			          break;
			      case 4:
			          printf("[NEW] Student Phone: ");
			          scanf("%lu", &foundStudent->entry.data.phone);
			          break;
			      case 5:
			          printf("[NEW] Student Address: ");
			          scanf("%s", foundStudent->entry.data.address);
			          break;
			      default:
			          printf("Invalid choice.\n");
			          break;
			    }

            return SUCCESS;
        }
		else
		{
            return result;
        }
    }
    return NULL_PTR;
}
/****************************************************************************/
ErrorState_t List_updateScore(const List_t* pl, u8 copy_u8ID)
{
	u8 Localu8ChosenNumber = 0;
    if (pl != NULL)
	{
        ListNode_t* foundStudent;
        ErrorState_t result = List_searchStudent(pl, copy_u8ID, &foundStudent);
        if (result == SUCCESS)
		{
			/* Update */
			printf("1) Student Math deg: %d \n",foundStudent->entry.degress.math_deg);
			printf("2) Student English deg: %d \n",foundStudent->entry.degress.english_deg);
			printf("3) Student Arabic deg: %d \n",foundStudent->entry.degress.arabic_deg);
			printf("Choose the number to Update [1-3]: ");

	         u8 Hold_math = foundStudent->entry.degress.math_deg;
	         u8 Hold_eng  = foundStudent->entry.degress.english_deg;
	         u8 Hold_ara  = foundStudent->entry.degress.arabic_deg;

			scanf("%d",&Localu8ChosenNumber);
			switch (Localu8ChosenNumber)
			{
			      case 1:
			          printf("[NEW] Student Math deg: ");
			          scanf("%d", &foundStudent->entry.degress.math_deg);
			          foundStudent->entry.degress.english_deg = Hold_eng;
			          foundStudent->entry.degress.arabic_deg  = Hold_ara;

			          break;
			      case 2:
			          printf("[NEW] Student English deg: ");
		              scanf("%d", &foundStudent->entry.degress.english_deg);
			          foundStudent->entry.degress.math_deg    = Hold_math;
			          foundStudent->entry.degress.arabic_deg  = Hold_ara;
			          break;
			      case 3:
			          printf("[NEW] Student Arabic deg: ");
			          scanf("%d", &foundStudent->entry.degress.arabic_deg);
			          foundStudent->entry.degress.math_deg    = Hold_math;
			          foundStudent->entry.degress.english_deg = Hold_eng;

			          break;
			      default:
			          printf("Invalid choice.\n");
			          break;
			    }

            return SUCCESS;
        }
		else
		{
            return result;
        }
    }
    return NULL_PTR;
}
/****************************************************************************/

ErrorState_t List_printList(const List_t* pl) {
    u8 Localu8NodeNumber = 0;
    if (pl != NULL && pl->pHead != NULL)
    {
    	// Check if the list is not NULL and not empty
        struct Node * currentNode = pl->pHead;
        while (currentNode != NULL)
        {
            printf("======================================================================\n");
            printf("========================== NODE NUMBER (%d) ==========================\n", ++Localu8NodeNumber);
            printf("======================================================================\n");
            printf("1) Student ID: %d \n", currentNode->entry.ID);
            printf("2) Student Name: %s \n", currentNode->entry.Name);
            printf("3) Student Age: %d \n", currentNode->entry.age);
            printf("4) Student Phone: (+20)%lu \n", currentNode->entry.data.phone);
            printf("5) Student Address: %s \n", currentNode->entry.data.address);
            printf("6) Student Math deg: %d \n", currentNode->entry.degress.math_deg);
            printf("7) Student English deg: %d \n", currentNode->entry.degress.english_deg);
            printf("8) Student Arabic deg: %d \n", currentNode->entry.degress.arabic_deg);
            printf("======================================================================\n\n");
            currentNode = currentNode->pNext;
        }
        return SUCCESS;
    }
    return NULL_PTR;
}

/****************************************************************************/
ErrorState_t List_listSize(const List_t* pl, u32* pSize)
{
    if (pl != NULL && pSize != NULL)
	{
        *pSize = pl->ListSize;
        return SUCCESS;
    }
    return NULL_PTR;
}
/****************************************************************************/
ErrorState_t List_freeList(List_t* pl)
{
    if (pl != NULL)
	{
        ListNode_t* currentNode = pl->pHead;
        while (currentNode != NULL)
		{
            ListNode_t* nextNode = currentNode->pNext;
            free(currentNode);
            currentNode = nextNode;
        }
        pl->pHead = NULL;
        pl->pTail = NULL;
        pl->ListSize = 0;
        return SUCCESS;
    }
    return NULL_PTR;
}

/****************************************************************************/

