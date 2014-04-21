#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "orderList.h"
#include "person.h"

void printPerson(PersonPtr person)
{
	printf("Name is: %s\n",person->name);
	printf("Credit is: $%f\n",person->credit);
	printf("Address is: %s\n",person->address);
	printf("State is: %s\n",person->state);
	printf("ZIP is: %s\n",person->zip);
}

void initPerson(PersonPtr newPerson, char *name, int id, double credit, char *address, char *state, char *zip)
{

	newPerson->name = name;
	newPerson->id = id;
	newPerson->address = address;
	newPerson->state = state;
	newPerson->zip = zip;
	newPerson->next = NULL;
	
	newPerson->accept = NULL;
	newPerson->reject = NULL;


}	
