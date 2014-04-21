#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dbList.h"
#include "order.h"
#include "orderList.h"
#include "person.h"

//typedef struct Person* PersonPtr;
void insertPerson(dbListPtr myList, PersonPtr newPerson)
{
        PersonPtr temp = myList->head;

        if(temp == NULL)
        {
                myList->head = newPerson;
                myList->head->next = NULL;
		newPerson = NULL;
		return;
        }
        else
        {
		
                while(temp->next != NULL)
                        temp = temp->next;
		
                temp->next = newPerson;
                newPerson->next = NULL;
        }

        printf("New Person inserted\n");
}

void initPersonList(dbListPtr newList)
{
        newList->head = NULL;
        printf("New PersonList initialized\n");
}

PersonPtr retrievePerson(dbListPtr myList, int ID, PersonPtr toRetrieve)
{
        toRetrieve = myList->head;

        while((toRetrieve->id != ID) && (toRetrieve != NULL))
                toRetrieve = toRetrieve->next;

        if(toRetrieve == NULL)
                return NULL;
        else
                return toRetrieve;
}

void removePerson(dbListPtr myList, int ID)
{
        PersonPtr toDelete = myList->head;

        PersonPtr trail = NULL;

        if((toDelete->id == ID) && (toDelete != NULL))
        {
                myList->head = toDelete->next;
                toDelete->next = NULL;
                free(toDelete);
                return;
        }

        while((toDelete->id != ID) && (toDelete != NULL))
        {
                trail = toDelete;
                toDelete = toDelete->next;
        }

        if(toDelete == NULL)
        {
                printf("Person not found\n");
                return;
        }
        else
        {
                trail->next = toDelete->next;
                toDelete->next = NULL;
                free(toDelete);
        }
}

void printList(dbListPtr myList)
{
	PersonPtr temp;
	temp = myList->head;

	while(temp != NULL)
	{
		printPerson(temp);
		printf("\n\n");
		temp = temp->next;
	}

}



	
