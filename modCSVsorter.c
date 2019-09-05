#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
//#include "customTokenizer.c"
//#include "customTokenizer.h"
#include "modCSVsorter.h"
#include "mergesort.c"

/*
char *strtok_new(char *c, char *delim);
const char* getfield(char* line, int colNum);
int getHeaderNum(char* headerLine, char* colName);


void MergeSortChar(node ** headRef);
void MergeSortInt(node ** headRef);
node* SortedMergeChar(node* a, node* b);
node* SortedMergeInt(node* a, node* b);
void splitIntoSublists(node* sourcePtr, node** frontPtrPtr, node** backPtrPtr);
*/

void sorting(char *headerName, char *fileName, char *filePath, char *outputDir, char *outputFileName) //Returns 1 on success and 0 on failure
{
  
  FILE *file = fopen(filePath, "r");
  if(file == NULL)
  {
    fprintf(stderr, "Could not open file for reading \n");
  }
  
  char headerArr[5000];
  
  fgets(headerArr, 5000, file);
  char *headerLine = &headerArr;
  
  if(*headerLine == NULL)
  {
    fprintf(stderr, "No lines in CSV file. \n");
    return 0;
  }
  
  char *headerLineDuplicate = strdup(headerLine);
  //Last 2 values of the line are new line characters, so replace that with null terminating characters
  size_t len = strlen(headerLine);
  headerLine[len-1] = '\0';
  headerLine[len-2] = '\0';
  
  //getHeaderNum is used to see which column number the data is under
  int headerNum = getHeaderNum(headerLine, headerName);
  
  //printf("header num in sorting function %d \n", headerNum);
  
  int dataType; //0 for char, 1 for integer, 2 for float
  //Check header
  if (strcmp (headerName, "num_critic_for_reviews") ==0 ||
    strcmp (headerName, "duration") ==0 ||
    strcmp (headerName, "director_facebook_likes") ==0 ||
    strcmp (headerName, "actor_3_facebook_likes") ==0 ||
    strcmp (headerName, "actor_1_facebook_likes") ==0 ||
    strcmp (headerName, "gross") ==0 ||
    strcmp (headerName, "num_voted_users") ==0 ||
    strcmp (headerName, "cast_total_facebook_likes") ==0 ||
    strcmp (headerName, "facenumber_in_poster") ==0 ||
    strcmp (headerName, "num_user_for_reviews") ==0 ||
    strcmp (headerName, "budget") ==0 ||
    strcmp (headerName, "title_year") ==0 ||
    strcmp (headerName, "actor_2_facebook_likes") ==0 ||
    strcmp (headerName, "imdb_score") ==0 ||
    strcmp (headerName, "aspect_ratio") ==0 ||
    strcmp (headerName, "movie_facebook_likes") ==0)
  { 
    if (strcmp (headerName, "imdb_score") ==0 || strcmp (headerName, "aspect_ratio") == 0) //Check for float
    {
       dataType = 2; //Float
    }
    else //Else means it's an integer
    {
       dataType = 1; //Integer
   } 
  }
  else if ((strcmp (headerName, "num_critic_for_reviews") !=0 && //check if string
    strcmp (headerName, "duration") !=0 &&
    strcmp (headerName, "director_facebook_likes") !=0 &&
    strcmp (headerName, "actor_3_facebook_likes") !=0 &&
    strcmp (headerName, "actor_1_facebook_likes") !=0 &&
    strcmp (headerName, "gross") !=0 &&
    strcmp (headerName, "num_voted_users") !=0 &&
    strcmp (headerName, "cast_total_facebook_likes") !=0 &&
    strcmp (headerName, "facenumber_in_poster") !=0 &&
    strcmp (headerName, "num_user_for_reviews") !=0 &&
    strcmp (headerName, "budget") !=0 &&
    strcmp (headerName, "title_year") !=0 &&
    strcmp (headerName, "actor_2_facebook_likes") !=0 &&
    strcmp (headerName, "imdb_score") !=0 &&
    strcmp (headerName, "aspect_ratio") !=0 &&
    strcmp (headerName, "movie_facebook_likes") !=0))
    {
      dataType = 0; //Char
    }
  else
  {
    fprintf(stderr, "No header found \n");
    dataType = -1;
    return 0;
  }

  node * head;
  head = malloc(sizeof(node)); //Initially allocate space for the head node
  
  //Pointer nodes for linking multiple nodes
  node *prev;
  node *curr;
  
  int nodeCounter = 0;
  
  char eachLine[5000];
  while((fgets(eachLine, 5000, file)) != NULL) //Reading each line
  {
    char *buffer = eachLine; //Pointer to point to the array of text
    char *tempLine = strdup(buffer);
    char *eachTerm = getfield(tempLine, headerNum); //Gets the data under the specified column
    
    //Create head node if this is the first iteration
    if(nodeCounter == 0)
    {
      head->rowLine = strdup(buffer);
      head->headerName = headerName;
      
      //Check data type and assign to intValue or charValue accordingly
      if(dataType == 0)
      {
        head->charValue = eachTerm;
        head->intValue = 0;
        head->floatValue = 0;
      }
      else if (dataType == 1)
      {
        head->intValue = atoi(eachTerm);
        head->charValue = NULL;
        head->floatValue = 0;
      }
      else if (dataType == 2)
      {
        head->floatValue = atof(eachTerm);
        head->charValue = NULL;
        head->intValue = 0;
      }
      
      head->next = NULL;
      
      //printf("%s\n", buffer);
      //printf("%s\n", head->rowLine);
      
      prev = head;
      curr = head;
    }
    else //Create new nodes and link them
    {
      node * tempNode; 
      tempNode = malloc(sizeof(node)); //Allocate more space for each node created
    
      tempNode->rowLine = strdup(buffer);
      tempNode->headerName = headerName;
      
      if(dataType == 0)
      {
        tempNode->charValue = eachTerm;
        tempNode->intValue = 0;
        tempNode->floatValue = 0;
      }
      else if (dataType == 1)
      {
        tempNode->intValue = atoi(eachTerm);
        tempNode->charValue = NULL;
        tempNode->floatValue = 0;
      }
      else if (dataType == 2)
      {
        tempNode->floatValue = atof(eachTerm);
        tempNode->charValue = NULL;
        tempNode->intValue = 0;
      }
      
      //tempNode->charValue = eachTerm;
      tempNode->next = NULL;
      
      //printf("%s\n", tempNode->rowLine);
      //printf("%s\n", buffer);
      
      curr = tempNode;
      prev->next = curr;
      prev = tempNode; 
   }

    nodeCounter++;
  }
 
  //Call appropriate merge sort function based on if it is sorting on an int or a char
  if(dataType == 0)
  {
    MergeSortChar(&head);
  }
  else if(dataType == 1)
  {
    MergeSortInt(&head);
  }
  else if(dataType == 2)
  {
    MergeSortFloat(&head);
  }
  
  node * finalPtr = head;
  
  fclose(file);
  
  printSortedListToFile(finalPtr, headerLineDuplicate, dataType, outputDir, outputFileName); //Print out each row
  
  return;
} 

void printSortedListToFile(node *node, char *headerLine, int dataType, char *outputDir, char *outputFileName) 
{ 
  //Make path for file if output directory is specified
  char outputFilePath[5000];
  strcpy(outputFilePath, outputDir);
  strcat(outputFilePath, "/");
  strcat(outputFilePath, outputFileName);
  
  //printf("output directory path %s \n", outputFilePath);
  
  FILE *eachFile = (fopen(outputFilePath, "w"));
  if(eachFile == NULL)
  {
    printf("Could not open file to write data \n");
  }
  
  fprintf(eachFile, "%s", headerLine); //Need a new line character because we delete both in sorting function
  
  while(node != NULL) 
  { 
    fprintf(eachFile, "%s", node->rowLine); 
    node = node->next; 
  }
  
  fclose(eachFile); 
  
}