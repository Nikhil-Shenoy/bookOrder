/* USE PRINT STATEMENTS TO SHOW THAT THE PROGRAM IS DOING PROPER INTERLEAVING */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "dbList.h"
#include "order.h"
#include "person.h"

#define MAX 10
int count = 0;
Order *sample[MAX];
int done = 0;
int ordersLeft = 0;

Person **database;

pthread_mutex_t mutex;
pthread_mutex_t orderLock;
pthread_mutex_t dummy;
pthread_cond_t dataAvailable;
pthread_cond_t spaceAvailable;

pthread_cond_t exitVar;

struct package {
	pthread_t *consumers;
	char *orderFile;
};

int isSampleNull()
{
	// 1 means it is empty, 0 means it is not empty
	int answer;
	answer = 1;
	int i;
	for(i = 0; i < MAX; i++)
	{
		if(sample[i] != NULL)
			answer = 0;
	}

	return answer;
}	
		

/*
Consumer operations:
	1) Acquire mutex;
	2) Block on the condition variable until work is available
	3) Remove work from queue, possibly signal condition variable
	4) Release mutex
	5) Process the work
	6) Go to step 1

	Notice that the mutex is held only until the thread retrieves an element from the shared buffer
	After the element is retrieved, then only is the processing done

*/

void consumer(void *arg)
{
	char *myCategory;
	myCategory = (char *)arg; // the category used to identify which orders should be taken out of the buffer
	int allRetrieved; // flag indicates that this consumer has removed all entries of its category
	allRetrieved = 0; // 0 means the all orders have not been retrieved, 1 means that they have.	

	Order *toProcess[MAX];
	int i;
	for(i = 0; i < MAX; i++) // initializes the local array of orders to be processed.
		toProcess[i] = NULL;


	int processCount; // indexes the toProcess array
	processCount = 0;
	while(ordersLeft != 0)
	{
		printf("Acquiring the mutex...\n");	
		pthread_mutex_lock(&mutex);
		int check;
		check = 0;
	
		while((count == 0) || (allRetrieved == 1))
		{
		
			/*
			if(done == 1)
			{
				printf("About to exit the consumer with category %s\n",myCategory);
				pthread_exit(0);
			}
			*/
			if(ordersLeft == 0)
			{
				pthread_mutex_lock(&dummy);
				printf("Waiting on the dummy\n",myCategory);
				pthread_cond_wait(&exitVar,&dummy);
				printf("Exiting the %s thread...\n",myCategory);
				pthread_exit(0);
			}


			printf("%s thread about to wait...\n",myCategory);
			pthread_cond_signal(&spaceAvailable);
			pthread_cond_wait(&dataAvailable,&mutex);
			allRetrieved = 0;

		}

		printf("\nConsumer: Retrieving orders\n");

		Order *myOrder;

		int x;
		for(x = 0; (x < MAX) && (isSampleNull() == 0); x++)
		{
			if(sample[x] != NULL)
			{	
				check = strcmp(sample[x]->category,myCategory);
	
				if(check == 0)
				{
	
					myOrder = sample[x];
					toProcess[processCount] = sample[x];
				
					sample[x] = NULL;
					processCount++;
					--count;
				}
			}	
		}
		allRetrieved = 1;
		printf("Giving up the mutex...\n");
		pthread_mutex_unlock(&mutex);
		printf("Let's see what we have in the consumer...\n");
		for(x = 0; x < MAX; x++)
		{
			if(toProcess[x] != NULL)
			{
				printOrder(toProcess[x]);
				printf("\n");
				toProcess[x] = NULL;
			}
		}

	//sleep(3);	


	}

	printf("Consumer exiting...\n");
//	pthread_exit(0);
}

/*
Producer Operations:
	
	1) Get the information we need to write
	2) Acquire the mutex.
	3 ) Block on the condition variable until there is space on the queue.
	4) Place information in the queue, possibly signal condition variable
	5) Release the mutex
	6) Go to step 1

	The producer only holds on the mutex long enough to place information into the queue, nothing more.

*/


void producer(void *arg)
{
	struct package *myPackage;
	myPackage = (struct package *)arg;

	pthread_t *consumers = myPackage->consumers;

	char *myFile;
	myFile = myPackage->orderFile;
	printf("myFile is %s\n",myFile);
	FILE *orders = fopen(myFile,"r");
	
	char c;
	int peopleCount;
	peopleCount = 0;
	while(c != EOF)
	{
		c = fgetc(orders);
		if(c == '\n')
			peopleCount++;
	}
	rewind(orders);

	int numOrders;
	numOrders = peopleCount;

	int orderLineSize = getMaxLineCount(orders);
 	rewind(orders);	
	char Line[orderLineSize];

	/* 
		Create an local array to hold all the orders. 
		Producer is responsible for populating the shared buffer.
		The reason for this is to keep track of all the mallocs performed and to free everything properly.
	*/


	char *title;
	char *priceTemp;
	char *idTemp;
	char *category;
	double price;
	int id;

	Order *localOrders[numOrders];

	int k;
	for(k = 0; k < numOrders; k++)
	{
		// Initialize the orders and place them into the array
		fgets(Line,orderLineSize,orders);
		Order *newOrder = malloc(sizeof(Order));

		title = strdup(strtok(Line,"|"));
		priceTemp = strdup(strtok(NULL,"|"));
		idTemp = strdup(strtok(NULL,"|"));
		category = strdup(strtok(NULL,"|"));
		
		price = atof(priceTemp);
		id = atoi(idTemp);
		
		initOrder(newOrder,title,price,id,category);

		localOrders[k] = newOrder;

		
	}



/*
	int orderCount;
	orderCount = 0;
*/
	while(ordersLeft != 0)
	{
		
		pthread_mutex_lock(&mutex);

		while(count == MAX)
		{
			printf("Producer about to sleep...\n");
			pthread_cond_signal(&dataAvailable);
			pthread_cond_wait(&spaceAvailable,&mutex);
		}

		printf("Producer: Inserting elements...\n");
	
		if(ordersLeft != 0)
		{	
			int i;
			for(i = 0; (i < MAX) && (ordersLeft != 0); i++)
			{
				if(sample[i] == NULL)
				{
					sample[i] = localOrders[ordersLeft-1];
					count++;
					pthread_mutex_lock(&orderLock);
					--ordersLeft;
					pthread_mutex_unlock(&orderLock);
				}
			}	


//			sleep(5);
		}
/*
		if(orderCount == 15)
		{
			done = 1;
			pthread_join(consumers[0],NULL);
		}
*/
		pthread_mutex_unlock(&mutex);


	}
	printf("Special exit of the producer...\n");
	pthread_mutex_lock(&mutex);
	done = 1;
	pthread_mutex_unlock(&mutex);

	printf("Attempting to wait on the consumers from the producer...\n");
//	pthread_join(consumers[0],NULL);
	printf("Successful join and exit\n");
	
/*
	int y;
	for(y = 0; y < 3; y++)
	{
		pthread_join(consumers[y],NULL);
	}
*/
	pthread_exit(0);
}





int main(int argc, char *argv[])
{
	//initPersonList(database);
	int i;
	for(i = 0; i < MAX; i++) // initialize the shared buffer to null
		sample[i] = NULL;

	char *dbFile;
	char *orderFile;
	char *categoryFile;

	dbFile = argv[1];
	orderFile = argv[2];
	categoryFile = argv[3];	
	

	FILE *catFile = fopen(categoryFile,"r");
	if(catFile == NULL)
		printf("Error opening the file\n");
	int catNumber;
	catNumber = getNumLines(catFile);
	printf("catNumber is: %d\n",catNumber);
	int maxCatSize;
	maxCatSize = getMaxLineCount(catFile);
//	printf("maxCatSize: %d\n",maxCatSize);
	char *categoryList[catNumber];

	for(i = 0; i < catNumber; i++)
	{
		categoryList[i] = (char *)malloc(catNumber*sizeof(char));
		fgets(categoryList[i],maxCatSize,catFile);
		printf("Temp is: %s\n",categoryList[i]);	
	}

	strcat(categoryList[catNumber-1],"\n");
	printf("categoryList[catNumber-1]: %s\n",categoryList[catNumber-1]);
	
	fclose(catFile);	


	/* NEED TO FIGURE OUT WHY THE CREDIT ISN'T GETTING RETURNED!!!!!*/

	char *name;
	char *IDTemp;
	char *creditTemp;
	char *address;
	char *state;
	char *zip;

	double credit;
	int ID;

	int peopleCount; 
	int maxLineSize;
	FILE *db = fopen(dbFile,"r");
//	peopleCount = getNumLines(db);

	char d;
	while(d != EOF)
	{
		d = fgetc(db);
		if(d == '\n')
			peopleCount++;
	}
	rewind(db);


	d = 'a';
	FILE *myOrders = fopen(orderFile,"r");
	while(d != EOF)
	{
		d = fgetc(myOrders);
		if(d == '\n')
			ordersLeft++;
	}
	rewind(db);


	maxLineSize = getMaxLineCount(db);
	char line[maxLineSize];
	database = (Person *)realloc(database,peopleCount*sizeof(Person));


	int x;
	for(x = 0; x < peopleCount; x++)	
	{
		fgets(line,maxLineSize,db);
		PersonPtr newPerson = (PersonPtr)malloc(sizeof(Person));
		

		name = strdup(strtok(line,"|"));
		IDTemp = strdup(strtok(NULL,"|"));
		creditTemp = strdup(strtok(NULL,"|"));
		address = strdup(strtok(NULL,"|"));
		state = strdup(strtok(NULL,"|"));
		zip = strdup(strtok(NULL,"|"));		
		
		credit = atof(creditTemp);
		ID = atoi(IDTemp);


		initPerson(newPerson,name,ID,credit,address,state,zip);
		database[x] = newPerson;		
		
//		insertPerson(database,newPerson);
	}
	
	for(x = 0; x < peopleCount; x++)
	{
		//printPerson(database[x]);
		printf("\n");
	}



	printf("%s\n",categoryList[2]);
	
	pthread_t thread;
//	pthread_t consumers[catNumber];
	pthread_t *consumers = malloc(catNumber*sizeof(pthread_t));
	
	struct package args;
	struct package *argPtr = &args;
	argPtr->consumers = consumers;
	argPtr->orderFile = orderFile;
	

	pthread_create(&thread,0,producer,(void *)argPtr);
	pthread_create(&consumers[0],0,consumer,categoryList[0]);
	pthread_create(&consumers[1],0,consumer,categoryList[1]);
	pthread_create(&consumers[2],0,consumer,categoryList[2]);

	printf("About to join the producer...\n");
	pthread_join(thread,NULL);

	printf("We're going to join the two threads now\n");
//	pthread_join(thread,NULL);

	pthread_cond_signal(&exitVar);
//	pthread_cond_signal(&dataAvailable);
//	pthread_cond_signal(&dataAvailable);



/*	pthread_join(consumers[0],NULL);
	pthread_join(consumers[1],NULL);
	pthread_join(consumers[2],NULL);
*/
	printf("And we're back!\n");
	sleep(10);
	pthread_exit(0);

	return 0;
}

