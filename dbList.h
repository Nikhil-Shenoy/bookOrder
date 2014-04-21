#ifndef LIST_H
#define LIST_H
#include "person.h"

struct dbList {
        Person *head;
};

typedef struct dbList dbList;
typedef dbList* dbListPtr;
void initPersonList(dbListPtr newList);
void insertPerson(dbListPtr myList, PersonPtr newPerson);
PersonPtr retrievePerson(dbListPtr myList, int id, PersonPtr toRetrieve);
void removePerson(dbListPtr myList, int id);


#endif
           
