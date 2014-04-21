/* COULD HAVE USED STRTOK FOR ALL THE EXTRACTION FUNCTIONS!!!!!! */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *deleteChar(char *line)
{
        int lineCount;
        char *temp;
        temp = &line[0];
        while(*temp != '\n')
        {
                temp++;
                lineCount++;
        }

        int removeCount;
        temp = &line[0];
        while(*temp != '|')
        {
                temp++;
                removeCount++;
        }

        char holder[strlen(line)];
        strncpy(holder,line,lineCount-removeCount);
        strcpy(line,holder);

        return line;
}


int getMaxLineCount(FILE *filePtr)
{
        char c;
        int lineCount;
        int maxCount;
        lineCount = 0;
        maxCount = 0;
        while(c != EOF)
        {
                c = fgetc(filePtr);
                lineCount++;
                if((c == '\n') && (lineCount > maxCount))
                {
                        maxCount = lineCount;
                        lineCount = 0;
                }
        }

        rewind(filePtr);
        return maxCount;
}

int getNumLines(FILE *filePtr)
{
        char c;
/*        int lineCount;
      int maxCount;
        lineCount = 0;
        maxCount = 0;
*/
        int peopleCount;
        peopleCount = 0;
        while(c != EOF)
        {
                c = fgetc(filePtr);
                if(c == '\n')
                        peopleCount++;
        }

        rewind(filePtr);
        return peopleCount;
}


char *extractName(char *line, char *name)
{
	char *extractor;
	extractor = line;
	int counter;
	counter = 1;
	extractor++;

	while(*extractor != '\"')
	{
		extractor++;
		counter++;
	}

	char *temp;	
	temp = &line[1];
	strncpy(name,temp,counter-1);
	name[counter-1] = '\0';

	
//	printf("\n\n(Inside) The name is: %s. Extractor is: %c. The char after extractor is: %c\n",name,*extractor,*extractor++);

	return name;
}

int extractID(char *line)
{
	char *extractor;
	extractor = line;
	int counter;
	counter = 1;
	char *temp;
	extractor++;
	temp = extractor;
	char id[strlen(line)];


	while(*extractor != '|')
	{
		extractor++;
		counter++;
	}

	strncpy(id,temp,counter-1);
	id[counter-1] = '\0';

//	printf("ID is now: %s\n",id);		
//	printf("\n\n(Inside) The name is: %s. Extractor is: %c. The char after extractor is: %c\n",name,*extractor,*extractor++);
	int returnValue;
	returnValue = atoi(id);
	return returnValue;
}

double extractCredit(char *line)
{
	char *extractor;
	extractor = line;
	int counter;
	counter = 1;
	char *temp;
	extractor++;
	temp = extractor;
	char credit[strlen(line)];
	
	while(*extractor != '|')
	{
		extractor++;
		counter++;
	}

	strncpy(credit,temp,counter-1);
	credit[counter-1] = '\0';

//	printf("ID is now: %s\n",credit);		
//	printf("\n\n(Inside) The name is: %s. Extractor is: %c. The char after extractor is: %c\n",name,*extractor,*extractor++);
	double hello;
	hello = atof(credit);
	return atof(credit);
}

char *extractAddress(char *line, char *address)
{
	char *extractor;
	extractor = line;
	int counter;
	counter = 1;
	char *temp;
	extractor++;
	extractor++;
	temp = extractor;	
	

	while(*extractor != '\"')
	{
		extractor++;
		counter++;
//		printf("%c\n",*extractor);
	}

	strncpy(address,temp,counter-1);
	address[counter-1] = '\0';

	return address;
}

char *extractState(char *line, char *state)
{

	char *extractor;
	extractor = line;
	int counter;
	counter = 1;
	char *temp;
	extractor++;
	temp = extractor;	
	
	while(*extractor != '|')
	{
		extractor++;
		counter++;
	}
	strncpy(state,temp,counter-1);
	state[counter-1] = '\0';

	return state;
}

char *extractZip(char *line, char *zip)
{
	char *extractor;
	extractor = line;
	int counter;
	counter = 1;
	char *temp;
	extractor++;
	temp = extractor;	
	

	while(*extractor != '|')
	{
		extractor++;
		counter++;
	}

	strncpy(zip,temp,counter-1);
	zip[counter-1] = '\0';

	return zip;
}

char *extractCategory(char *line, char *category)
{
	char *extractor;
	extractor = line;
	int counter;
	counter = 1;
	char *temp;
	extractor++;
	temp = extractor;	
	

	while(*extractor != '|')
	{
		extractor++;
		counter++;
	}

	strncpy(category,temp,counter-1);
	category[counter-1] = '\0';

	return category;
}

char *moveToNextPipe(char *line)
{
	char *extractor;
	char *temp;
	temp = line;
	extractor = line;
	extractor++;
	while(*extractor != '|')
	{
//		printf("Extractor is: %c\n",*extractor);
		extractor++;
	}

	while(*extractor != '\0')
	{
		*temp = *extractor;
		extractor++;
		temp++;
	}

	*temp = '\0';
	return line;
}
	

char *extractTitle(char *line, char *title)
{
	char *extractor;
	extractor = line;
	int counter;
	counter = 1;
	extractor++;

	while(*extractor != '\"')
	{
		extractor++;
		counter++;
	}

	char *temp;	
	temp = &line[1];
	strncpy(title,temp,counter-1);
	title[counter-1] = '\0';

	
//	printf("\n\n(Inside) The title is: %s. Extractor is: %c. The char after extractor is: %c\n",title,*extractor,*extractor++);

	return title;
}

double extractPrice(char *line)
{
	char *extractor;
	extractor = line;
	int counter;
	counter = 1;
	char *temp;
	extractor++;
	temp = extractor;
	char price[strlen(line)];
	
	while(*extractor != '|')
	{
		extractor++;
		counter++;
	}

	strncpy(price,temp,counter-1);
	price[counter-1] = '\0';

//	printf("ID is now: %s\n",price);		
//	printf("\n\n(Inside) The name is: %s. Extractor is: %c. The char after extractor is: %c\n",name,*extractor,*extractor++);

	return atof(price);
}
