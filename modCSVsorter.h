/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

//Suggestion: define a struct that mirrors a record (row) of the data set


//Suggestion: prototype a mergesort function


typedef struct {
  char *headerName;
  //char int dataType;
  
  /*represents data we are sorting on: 
	 *	0 for string
	 *	1 for int
	 *	2 for double
	 *	3 for float
	 */
   
  //void prtData; //cast depending on datatype
  
  char *charValue;
  int intValue;
  float floatValue;
  char *rowLine;
  struct node * next;
  } node;
 
//New tokenizer function to handle comas and quotes
char *strtok_new(char *c, char *delim) 
{
	static char *current = NULL;
	char *pointer;
	int numOfPreDelimChars;

	if(c != NULL)
	{
		current = c;
	}
	if(current == NULL || *current == '\0')
	{
		return(NULL);
	}


	if (*current != '\"')//34 is " in ascii
	{
		
		numOfPreDelimChars = strcspn(current,delim);  //number of chars before the delim
		pointer = current; 					
		current += numOfPreDelimChars;					

		if(*current != '\0')
		{
			*current++ = '\0';
		}

		current--;

		if(*current=='\n')
		{
			*current='\0';
		}
		current++;

		//return (pointer);
	}
	else
	{
		//printf("(\") case: ");
		//current = c;
		current++;//current is now one ahead of the "
		pointer=current;

		while(current!=NULL && *current!='\"' && *current!='\0')
		{
			current++;
		}


		if(*current=='\"')
		{
			//printf("matching (\") found: ");
			*current='\0';
		}


		current+=2;//increment cause there has to be a "," or "\n" after a quote
		//printf("val@current: %s\n", current);
		//*current='\0';
		//current++;
	}
  
  //printf("Calling trimSpace with: %s\n", pointer);
  
  //TRIMMING WHITE SPACES
  //Leading space
  while(isspace(*pointer)) 
  {
    pointer++;
  }
  
  //Ending space
  char* back = pointer + strlen(pointer);
  while(isspace(*--back));
  {
    *(back+1) = '\0';
  }
  
  //printf("Trimmed string: %s\n", pointer);  
	return (pointer);
}

//Get the data under the column
const char* getfield(char* line, int colNum)
{
	//THIS CODE WORKS
	char* tok;
	int i=1;
 
  tok = strtok_new(line, ",");
	while (tok !=NULL && i<=colNum)
	{
		if(i==colNum){
			return tok;
		}
		
   tok = strtok_new(NULL, ",");
	 i++;
	}
}

//Get the column number
int getHeaderNum(char* headerLine, char* colName){

	char* tok;
	int i=1;
 
  
  int strLength = strlen(colName);
  //printf("%d\n", strLength );
  tok = strtok_new(headerLine, ",");
  //printf("TOKEN1: %s\n", tok);
  
	while (tok != NULL)
	{

		if((strcmp(tok, colName) == 0))
    {
      
			return i;
		}

    tok = strtok_new(NULL, ",");
		i++;
	}
   return -1;
}

void MergeSortInt(node ** headRef/*, int dataType*/);
node* SortedMergeInt(node* a, node* b/*, int dataType*/);
void mergeSortChar(node ** headRef/*, int dataType*/);
node* SortedMergeChar(node* a, node* b/*, int dataType*/);
void splitIntoSublists(node* sourcePtr, node** frontPtrPtr, node** backPtrPtr);