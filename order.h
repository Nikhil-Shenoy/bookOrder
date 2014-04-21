#ifndef ORDER_H
#define ORDER_H
#include <stdlib.h>
struct Order {
	char *title;
	double price;
	int custID;
	char *category;

	struct Order *next;
};

typedef struct Order Order;
//typedef Order* OrderPtr;

void initOrder(Order *newOrder, char *title, double price, int custID, char *category);
void printOrder(Order *node);

#endif
