#ifndef LIST_H
#define LIST_H
#include "order.h"

struct OrderList {
	Order *head;
};

typedef struct OrderList OrderList;
typedef struct OrderList* OrderListPtr;

void initOrderList(OrderListPtr newList);
void insertOrder(OrderListPtr myList, Order *newOrder);
Order *retrieveOrder(OrderListPtr myList, int custID, Order *toRetrieve);
void removeOrder(OrderListPtr myList, int custID);


#endif
