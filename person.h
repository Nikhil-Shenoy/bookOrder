#ifndef PERSON_H
#define PERSON_H
#include <stdlib.h>
#include "orderList.h"

struct Person {
	char *name;
	int id;
	double credit;
	char *address;
	char *state;
	char *zip;

	struct Person *next;

	struct Person *accept;
	struct OrderList *reject;
};

typedef struct Person Person;
typedef struct Person* PersonPtr;

void printPerson(PersonPtr person);
void initPerson(PersonPtr newPerson, char *name, int id, double credit, char *address, char *state, char *zip);

#endif
