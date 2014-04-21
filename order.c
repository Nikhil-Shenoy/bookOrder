#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "order.h"

void initOrder(Order *newOrder, char *title, double price, int custID, char *category)
{
	newOrder->title = title;
	newOrder->price = price;
	newOrder->custID = custID;
	newOrder->category = category;
	newOrder->next = NULL;

}

void printOrder(Order *node)
{
        printf("Title is: %s\n",node->title);
        printf("Price is: $%f\n",node->price);
        printf("ID is: %d\n",node->custID);
        printf("Category is: %s\n",node->category);
}

