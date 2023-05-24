
/*
Class: CSC_352
Assignment: PA_3
Instructor: Benjamin Dicken
Author: Nishant Athawale
Description: This program encrypts a given input stream of 
strings using the Beaufort encryption scheme.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes

int rangeCheck(char* rangeStr);
int colRangeGen(char* rangeStr, int* rangeList);
void rangeParser(char* section,int* start,int* end,int lastHyphenIndex,int firsthyphenIndex);
void charColumns(char* inpstr, int* colList);
void commaColumns(char* inpstr, int* colList);
void whiteSpColumns(char* inpstr, int* colList);


// Main to parse the input
int main(int argc, char *argv[]){// main for input                                                                                                     
  /*
    This function runs the scut function.
    Parameters:
    	argc: Number of arguments passed from the command line
	argv: List of arguments separated by space.
    Returns:
    	1: If the query is successful
	0 status: If incorrect input the return 0. 
   */
  char inputline[100];                                                                                                                                
  // Error Check cmd arugments                                                                                                                       
  if(argc != 3){                                // Check if only 3 argument                                                                            
        fwrite("expected 2 command line arguments.",34,1,stderr);  //         If no the print error message and return 0                    
        exit(1);
  }
  else{    // Else                                                                                           
    if((strcmp(argv[1], "-l")!=0) && (strcmp(argv[1], "-w")!=0) && (strcmp(argv[1], "-c")!=0)){  // Then extract flag and check if it is valid
        fwrite("Invalid delimiter type.",23,1,stderr );// If no then print error message and return 0;                                          
        exit(1);
    }
    if(rangeCheck(argv[2]) == 0){//     Extract the column range check if it is valid.                                                                  
      fwrite("Invalid selection.",18,1,stderr);//             If no then error message and return 0
      exit(1);
    }
  }

  int rangeList[128];
  colRangeGen(argv[2], rangeList);// Process column ranges to get a list of column numbers                                               


  // printf("%s\n %s\n %s\n%d", argv[0], argv[1], argv[2],colLen);
   while(fgets(inputline, 100, stdin) != NULL){          // while the given input stream has no EOF                                              
     if(strcmp(argv[1],"-l") == 0){
       charColumns(inputline, rangeList);
       }
     else if(strcmp(argv[1],"-c") == 0){
       commaColumns(inputline, rangeList);
     }
     else{
       whiteSpColumns(inputline, rangeList);
     }
   }
   return 0;
}


// Function for the the range check                                                                             
int rangeCheck(char* rangeStr){
  /*
    This function checks the validity of input range
    Parameter:
    	rangeStr: String whose validity is to be checked
    Returns:
    	1 : If input is valid
	0 : If input is invalid 
   */
  int index = 0;
  if((rangeStr[index] != '0') && (rangeStr[index] != '1') && (rangeStr[index] != '2') && (rangeStr[index] != '3') && (rangeStr[index] != '4') && (rangeStr[index] != '5') && (rangeStr[index] != '6') && (rangeStr[index] != '7') && (rangeStr[index] != '8') && (rangeStr[index] != '9')){
    // printf("Precheck");
    return 0;
  }
  while(rangeStr[index] != '\0'){
        if((rangeStr[index] != '0') && (rangeStr[index] != '1') && (rangeStr[index] != '2') && (rangeStr[index] != '3') && (rangeStr[index] != '4') && (rangeStr[index] != '5') && (rangeStr[index] != '6') && (rangeStr[index] != '7') && (rangeStr[index] != '8') && (rangeStr[index] != '9') && (rangeStr[index] != ',') && (rangeStr[index] != '-')){
          //  printf("InCheck1 %c",rangeStr[index]);
          return 0;
        }
        index++;
  }
  if((rangeStr[index-1] != '0') && (rangeStr[index-1] != '1') && (rangeStr[index-1] != '2') && (rangeStr[index-1] != '3') && (rangeStr[index-1] != '4') && (rangeStr[index-1] != '5') && (rangeStr[index-1] != '6') && (rangeStr[index-1] != '7') && (rangeStr[index-1] != '8') && (rangeStr[index-1] != '9')){
    // printf("Precheck2")
    return 0;
  }
  return 1;
}

// Function for column extraction

int colRangeGen(char* rangeStr, int* rangeList){
  /*
    This function parses the input string
    Parameter:
    	rangeStr: Input String to be parsed
	rangeList: The pointer to the array of integers in which column indices are to be stored. 
    Return:
    	This function returns the number of columns. 
   */
  int traverseIndex = 0;
  int colIndex = 0;
  char section [40];
  int sectionIndex=0;
  while(rangeStr[traverseIndex] != '\0'){
    if(rangeStr[traverseIndex] != ','){  // Build the substring split with commas                                                          
      section[sectionIndex] = rangeStr[traverseIndex];
      sectionIndex++;
      if(rangeStr[traverseIndex+1] == '\0'){
	section[sectionIndex] = '\0';
	int hyphenCount =0;
	int lastHyphenIndex=0;
	int firsthyphenIndex=0;
	for(int i = 0; i < sectionIndex; i++){// Check if there is hyphen                                                                            
	  if(section[i]== '-'){// Check for multiple If yes shorten the range                                                                           
	    if(hyphenCount ==0){
	      firsthyphenIndex = i;
	    }
	    hyphenCount++;
	    lastHyphenIndex = i;
	  }
	  //printf("%s", section);                                                                                                                    
	}
	if(hyphenCount == 0){
	  //printf("%d\n%d\n%d\n", atoi(section), firsthyphenIndex, lastHyphenIndex);                                                                  
	  rangeList[colIndex] = atoi(section);// If not then convert the string to integer and store it in the column lisst                             
	  colIndex++;
	  sectionIndex = 0;
	}
	// Figure how to take care of hyphens                                                                                                      
	else{
	  int start;
	  int end;
	  rangeParser(section, &start,&end,lastHyphenIndex,firsthyphenIndex);
	  for(int i=start; i<=end; i++){
	    rangeList[colIndex] = i;
	    colIndex++;
	  }
	  //	  printf("%d\n%d",start,end);
	}
	//printf("%d\n%d\n%d\n%s\n\n", atoi(section),lastHyphenIndex,firsthyphenIndex,section);
	sectionIndex=0;
	hyphenCount=0;
	
      } 
    }
    else{
      section[sectionIndex] = '\0';
      int hyphenCount =0;
      int lastHyphenIndex=0;
      int firsthyphenIndex=0;
      for(int i = 0; i < sectionIndex; i++){// Check if there is hyphen                                                                             
        if(section[i]== '-'){// Check for multiple If yes shorten the range                                                                           
          if(hyphenCount ==0){
	    firsthyphenIndex = i;
          }
          hyphenCount++;
	  lastHyphenIndex = i;
        }
        //printf("%s", section);                                                                                                                    
      }
      if(hyphenCount == 0){
        //printf("%d\n%d\n%d\n", atoi(section), firsthyphenIndex, lastHyphenIndex);
        rangeList[colIndex] = atoi(section);// If not then convert the string to integer and store it in the column lisst                             
        colIndex++;
        sectionIndex = 0;
      }
      else{
	// Figure how to take care of hyphens
	int start;
	int end;
	rangeParser(section, &start,&end,lastHyphenIndex,firsthyphenIndex);
	for(int i=start; i<=end; i++){
	  rangeList[colIndex] =	i;
	  colIndex++;
	}
      }
      //printf("%d\n%d\n%s\n\n",lastHyphenIndex,firsthyphenIndex,section);
      sectionIndex=0;
      hyphenCount=0;
    }
    traverseIndex++;
  }
  return colIndex;
}

void rangeParser(char* section,int* start,int* end,int lastHyphenIndex,int firsthyphenIndex){
  /*                                                                                                                                                                         
    This function parses a range into a list of columns														 
    Parameters:                                                                                                                       
        section: The range string                                                                                                                                        
	start: pointer to start 
	end: pointer to end
	lastHyphenIndex: index of last occurence of hyphen in range string
	firsthyphenIndex: index of first occurence of hyphen in range string
    Returns:
    	Nothing
   */
  char startstr[50];
  int i;
  for(i=0; i<firsthyphenIndex;i++){
    startstr[i] = section[i]; 
  }
  startstr[i] = '\0';
  *start = atoi(startstr);
  i=0;
  for(int j=lastHyphenIndex+1;j<strlen(section);j++){
    startstr[i] = section[j];
    i++;
  }
  startstr[i] = '\0';  
  *end = atoi(startstr);
}
   

// Function for printing character based columns


void charColumns(char* inpstr, int* colList){
  /*
    This function splits the string into columns based on characters and prints the desired columns
    Parameters:
        inpstr: String to be split in columns
	colList: List of column indexes
    Returns:
    	Nothing
  */
  int colIndex = 0;
  for(int i = 0; i < strlen(inpstr); i++){
    if((i+1) == colList[colIndex]){
      printf("%c ",inpstr[i]);
      colIndex++;
    }
    else if(strlen(inpstr)<colList[colIndex]){
      break;
    }
  }
  printf("\n");

}


// Function for printing comma based columns

void commaColumns(char* inpstr, int* colList){          
/*                                                                                                                                                                          
    This function splits the string into columns based on commas and prints the desired columns                                                                         
    Parameters:                                                                                                                                                             
        inpstr: String to be split in columns                                                                                                                               
        colList: List of column indexes                                                                                                                                     
    Returns:                                                                                                                                                                
        Nothing                                                                                                                                                            
  */
  int colIndex = 0;                                      
  char splitCols [100][100];                                                                                    
  int currChar = 0;                                      
  int strIndex = 0;                                      
  int charIndex= 0;                                      
  while(inpstr[currChar] != '\0'){                        
    //    printf("%d\n%d\n%d\n", strIndex, charIndex,currChar);
    while(inpstr[currChar] != ','){
      if(inpstr[currChar] == '\0'||inpstr[currChar] == '\n'){
	break;
      }
      //      printf("%d\n%d\n%d\n", strIndex, charIndex,currChar);
      splitCols[strIndex][charIndex] = inpstr[currChar];  
      charIndex++;                                       
      currChar++;                                        
    }
    if(inpstr[currChar]== '\0'||inpstr[currChar] == '\n'){
      break;
    }
    if(charIndex == 0){                                  
      splitCols[strIndex][charIndex] = ' ';              
      charIndex++;                                       
    }                                                    
    splitCols[strIndex][charIndex] = '\0';               
    charIndex = 0;                                       
    currChar++;                                          
    strIndex++;                                          
  }                                                      
  splitCols[strIndex][charIndex] = '\0';                 
  for(int i = 0; i <= strIndex; i++){                     
    if((i+1) == colList[colIndex]){                      
      printf("%s ",splitCols[i]);                        
      colIndex++;                                        
    }                                                    
    else if(strIndex<colList[colIndex]){                 
      break;                                              
    }                                                                                                                 
  }                                                       
  printf("\n");                                           
                                                          
}                                                         

// Function for whitespace based columns

void whiteSpColumns(char* inpstr, int* colList){
  /*                                                                                                                                                                        
    This function splits the string into columns based on whitespaces and prints the desired columns                                                                         
    Parameters:                                                                                                                                                             
    inpstr: String to be split in columns                                                                                                                               
        colList: List of column indexes                                                                                                                                     
    Returns:                                                                                                                                                             
        Nothing                                                                                                                                                             
  */
  int colIndex = 0;
  char splitCols [100][100];
  int currChar = 0;                                       
  int strIndex = 0;                                       
  int charIndex= 0;                                       
  while(inpstr[currChar] != '\0'){                         
    while(inpstr[currChar] != ' '){                      
      if(inpstr[currChar] == '\0'||inpstr[currChar] == '\n' ){
	break;
      }
      splitCols[strIndex][charIndex] = inpstr[currChar];   
      charIndex++;                                        
      currChar++;                                         
    }
    if(inpstr[currChar] == '\0'||inpstr[currChar] == '\n'){
      break;
    }
    if(charIndex == 0){                                   
      splitCols[strIndex][charIndex] = ' ';               
      charIndex++;                                        
    }                                                     
    splitCols[strIndex][charIndex] = '\0';                
    charIndex = 0;                                        
    currChar++;                                           
    strIndex++;                                           
  }                                                       
  splitCols[strIndex][charIndex] = '\0';
  for(int i = 0; i <= strIndex; i++){
    if((i+1) == colList[colIndex]){
      printf("%s ",splitCols[i]);
      colIndex++;
    }
    else if(strIndex<colList[colIndex]){
      break;
    }
  }
  printf("\n");

}

















