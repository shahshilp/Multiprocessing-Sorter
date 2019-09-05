#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include "modCSVsorter.c"


//GLOBAL VARIABLES:
int pipefd [2];
int depth = 0;

int isValidCSV(char *pathToFile) //Return 1 if it is a valid csv
{
  FILE * file = fopen(pathToFile, "r");
  
  if(file == NULL)
  {
    fprintf(stderr, "Could not open file  %s  to check if it is a valid csv \n", pathToFile);
  }
  
  char *firstLine;
  firstLine = (char *) malloc(sizeof(char)*5000);
  
  char *tokenLine;
  char *token;
  int tokenCounter = 0;
  char *eachLine;
  char *eachLineToken;
  
  fgets(firstLine, 5000, file);
  tokenLine = strdup(firstLine);
  token = strtok_new(tokenLine, ",");
  
  
  while(token != NULL) //Count number of tokens in headerLine
  {
    tokenCounter++;
    token = strtok_new(NULL, ",");
  }
  
  //Get next lines and count tokens again
  while(fgets(tokenLine,5000,file) != NULL)
  {
    int tempTokens = 0;
    eachLine = strdup(tokenLine);
    eachLineToken = strtok_new(eachLine, ",");
    
    while(eachLineToken != NULL)
    {
      tempTokens++;
      eachLineToken = strtok_new(NULL, ",");
    }
    
    if (tempTokens != tokenCounter)
    {
      fclose(file);
      return 0;
    }
  }
  
  fclose(file);
  return 1; //Valid CSV file
}


void traverseDirectory(char *columnName, char* startDir, char *outputDir)
{
	DIR* dir;
	struct dirent *entry;
  
  if (depth==0)
	{
		printf("Parent PID: %d\n", getpid());
	}
 
	if((dir = opendir(startDir))==NULL)
	{
		fprintf(stderr, "Error could not open directory to read files\n");
		return;
	}

	while ((entry = readdir(dir)) != NULL)
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)//skip current and pervious directories
		{
			continue;
		}
		else if(entry->d_type == DT_DIR)//check if entry is a sub-directoru
		{
			char path[1024];
			int pid = fork();

			if(pid == 0)//child will go through the sub-directory
			{
        pid_t childpid = getpid();
				write(pipefd[1], &childpid, sizeof(pid_t)); //write one byte to pipe for every process spawned
				depth += 1;
				snprintf(path, sizeof(path), "%s/%s", startDir, entry->d_name);
				traverseDirectory(columnName, path, outputDir);
				return;
			}
			else if(pid > 0)
			{
				wait(NULL);
			}
			else//pid < 0
			{
				fprintf(stderr, "ERROR while forking\n");
        return;
			}
		}
		else if(entry->d_type == DT_REG)//entry isnt a directory so it must be a file
		{
      //Need to fork() for every file
      char path[1024];
      int pid = fork();
      
      
      if(pid == 0)
      {
        pid_t childpid = getpid();
        write(pipefd[1], &childpid, sizeof(pid_t));
        depth += 1;
        snprintf(path, sizeof(path), "%s/%s", startDir, entry->d_name);
        
        //In child process, check if it a csv file and if it is a valid csv file
        int lenFileName = strlen(entry->d_name);
			  if (lenFileName > 4 && strcmp(entry->d_name + lenFileName - 4, ".csv")==0 && strstr(entry->d_name, "-sorted-")==NULL)
			  {
         
         //function to check if it's a valid csv file
         int isValid = isValidCSV(path);
         if(isValid == 0) //invalid CSV file
         {
           fprintf(stderr, "invalid csv file found %s \n", path);
           break;
         }
         
         
          //Create output file name
          char outputFileName[5000];
          strncpy(outputFileName, entry->d_name, lenFileName - 4);
          outputFileName[lenFileName - 4] = '\0';
          strcat(outputFileName, "-sorted-");
          strcat(outputFileName, columnName);
          strcat(outputFileName, ".csv");
          //printf("Output file name:  %s  \n", outputFileName);
          
					sorting(columnName, entry->d_name, path, outputDir, outputFileName);
          return;                     
        }
        else //Not a valid csv file
        {
          return;
        }
     }
     else if(pid > 0)
		 {
		  	wait(NULL);
	   }
    }
    else
		{
		  fprintf(stderr, "ERROR invalid file type\n");
      return;
		}
  }
  

	close(pipefd[1]);
	if (depth==0)
	{
		int numProcesses = 0;
    printf("CHILD PIDs: ");
		pid_t pidPlaceHolder;
		
    while(read(pipefd[0], &pidPlaceHolder, sizeof(pid_t)))
		{
      printf("%d, ", pidPlaceHolder);
			numProcesses += 1;
		}
		printf("\nThe number of processed are: %d\n", (numProcesses+1));
	}
}

int main(int argc, char* argv[])
{
  char * columnName;
  char * inputDir;
  char * outputDir;
  
  int inputDirSpecified = 0;
  int outputDirSpecified = 0;
  
  char *colParam = "-c";
  char *inputDirParam = "-d";
  char *outputDirParam = "-o";
  
  int colFlagCounter = 0;
  int inputDirFlagCounter = 0;
  int outputDirFlagCounter = 0;
  
  if (argc == 3 || argc == 5 || argc == 7) {
		// Appropriate amount of parameters
	}
	else {
		printf("Invalid format of parameters \n");
		exit(1);
	}

	// Find parameters
	int i;
	for (i = 1; i < argc; i = i + 2) {
		char* eachParam = argv[i];
		if (strcmp(eachParam, colParam) == 0) 
    {
				columnName = argv[i + 1];
        colFlagCounter = colFlagCounter + 1;
		}
		else if (strcmp(eachParam, inputDirParam) == 0) 
    {
				inputDir = argv[i + 1];
        inputDirSpecified = 1;
        inputDirFlagCounter = inputDirFlagCounter + 1;
		}
		else if (strcmp(eachParam, outputDirParam) == 0) 
    {
				outputDir = argv[i + 1];
        outputDirSpecified = 1;
        outputDirFlagCounter = outputDirFlagCounter + 1;
		}
		else {
			printf("Invalid number of parameters \n");
			return 1;
		}
	}
  
  if(colFlagCounter == 0)
  {
    //Column flag not found. Fatal error
    printf("Column flag not found \n");
    exit(1);
  }
  
  if(colFlagCounter > 1 || inputDirFlagCounter > 1 || outputDirFlagCounter > 1)
  {
    //Repeat of flags. Fatal Error
    printf("Invalid parameters format \n");
    exit(1);
  }
  
  pipe(pipefd);
  
  
	if (outputDirSpecified == 1) 
  {
	   //Check if directory exists
    DIR* checkDir = opendir(outputDir);
    if (checkDir)
    {
      closedir(checkDir);
    }
    else if (ENOENT == errno)
    {
      //Directory does not exist
      printf("Output directory does not exist \n");
      exit(1);
    }
	}
  else //Directory not specified so set to current folder
  {
    outputDir = ".";
  }
  
  //Defaults if all parameters not entered
  if (inputDirSpecified == 0) 
  {
		inputDir = ".";
	}
  
  traverseDirectory(columnName, inputDir, outputDir);
 
}