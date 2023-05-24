// Main function

// Function to validate the search pattern

// Function to execute and search
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strValidator(char* pattern);
void strSearch(char* pattern, char* instr,int caseFlag,int patternFlag,int printFlag);
char toLower(char inp);

int main(int argc, char *argv[]){
  if(argc == 0){
    fwrite("Requires more command-line arguments.\n",34,1,stderr);
    exit(1);
  }
  int caseSen = 0;
  int pattern = 0;
  int printStat =  0;
  int patternIndex;
  char inputline[200];

  // Split into pattern and flags
  for (int i=0;i<argc; i++){
    if(strcmp(argv[i], "-o") == 0){
      printStat = 1;
    }
    else if(strcmp(argv[i], "-i")==0){
      caseSen = 1;
   }
    else if(strcmp(argv[i], "-e")==0){
      pattern = 1;
    }
    else{
      patternIndex = i;
    }
  }
  if(strValidator(argv[patternIndex]) == 0){
    printf("Invalid search term.\n");
    exit(2);
  }
  
 
  //  printf("%d\n%d\n%d\n%d\n", caseSen,pattern,printStat,patternIndex);
  while (fgets(inputline, 200, stdin) != NULL){
    strSearch(argv[patternIndex], inputline, caseSen, pattern,printStat);
  }
}

int strValidator(char* pattern){
  int hashCount =0;
  int periodCount = 0;
  
  for(int i = 0; i<strlen(pattern); i++){
    if(pattern[i] == '#'){
      if(pattern[i+1] == '#' || pattern[i+1] == '.'){
	return 0;
      }
      if(i>0 &&(pattern[i-1] == '#' || pattern[i-1] == '.')){
	return 0; 
      }
      if(periodCount == 1){
	return 0;
      }
      else if(hashCount == 1){
	hashCount--;
      }
      else{
	hashCount++;
      }
    }
    else if(pattern[i] == '.'){
      if(hashCount == 1){
	return 0;
      }
      else if(periodCount == 1){
	periodCount--;
      }
      else{
	periodCount++;
      }
    }
  }
  return 1;
}

void strSearch(char* pattern, char* instr,int caseFlag,int patternFlag,int printFlag){
  char exactStr[200];
  int insertionIndex=0;
  int currCharPointer=0;
  //  int setPointer;
  int matchStat = 0;
  if(caseFlag == 0){ // Case sensitive	    
    if(patternFlag == 0){// non pattern match
      for(int i=0; i<strlen(instr); i++){
	if(pattern[currCharPointer] == '\0'){
	  exactStr[insertionIndex] = '\0';
	  matchStat++;
	  if(printFlag == 0){
	     printf("%s",instr );
	     break;
	  }
	  else{
	    printf("%s\n",exactStr);
	  }
	  insertionIndex = 0;
	  currCharPointer = 0;
	}
	else if(instr[i] == pattern[currCharPointer]){
	    exactStr[insertionIndex] = instr[i];
	    insertionIndex++;
	    currCharPointer++;
	}
	else{
	  insertionIndex = 0;
	  currCharPointer = 0;
	}
      }
    }
    // Pattern match
    else{
      for(int i=0; i<strlen(instr); i++){
	if(pattern[currCharPointer] == '\0'){
	  exactStr[insertionIndex] = '\0';
	  if(printFlag == 0){
	    printf("%s",instr );
	    break;
	  }
	  else{
	    printf("%s\n",exactStr);
	  }
	  insertionIndex = 0;
	  currCharPointer = 0;
	}
	else if(instr[i] == pattern[currCharPointer] || pattern[currCharPointer] == '.'){
	  exactStr[insertionIndex] = instr[i];
	  insertionIndex++;
	  currCharPointer++;
	}
	else if(pattern[currCharPointer] == '#'){
	  if(pattern[currCharPointer+1] == instr[i+1]){
	    exactStr[insertionIndex] = instr[i];
	    insertionIndex++;
	    currCharPointer++;
	  }
	  else{
	    exactStr[insertionIndex] = instr[i];
	    insertionIndex++;
	    
	  }
	}
	else{
       	  insertionIndex = 0;
	  currCharPointer = 0;
	}
      }
    }
  }
  else{// Case insensitive	    
    if(patternFlag == 0){// non pattern match
      for(int i=0; i<strlen(instr); i++){
	if(pattern[currCharPointer] == '\0'){
	  exactStr[insertionIndex] = '\0';
	  matchStat++;
	  if(printFlag == 0){
	    printf("%s",instr);
	    break;
	  }
	  else{
	    printf("%s\n",exactStr);
	  }
	  insertionIndex = 0;
	  currCharPointer = 0;
	  //	  printf("wot");
	}
	else if(toLower(instr[i]) == toLower(pattern[currCharPointer]) ){
	  exactStr[insertionIndex] = instr[i];
	  insertionIndex++;
	  currCharPointer++;
	  // printf("how");
	}
	else{
	  insertionIndex = 0;
	  currCharPointer = 0;
	  // printf("why!!");
	}       
      }
    }
    else{ 	// Pattern match
      for(int i=0; i<strlen(instr);i++){
	if(pattern[currCharPointer] == '\0'){
	  exactStr[insertionIndex] = '\0';
	  if(printFlag == 0){
	    printf("%s",instr );
	    break;
	  }
	  else{
	    printf("%s\n",exactStr);
	  }
	  insertionIndex = 0;
	  currCharPointer = 0;
	}
	else if(toLower(instr[i]) == toLower(pattern[currCharPointer])){
	  exactStr[insertionIndex] = instr[i];
	  insertionIndex++;
	  currCharPointer++;
	}
	else if(pattern[currCharPointer] == '#'){
	  if(toLower(pattern[currCharPointer+1]) == toLower(instr[i+1])){
	    exactStr[insertionIndex] = instr[i];
	    insertionIndex++;
	    currCharPointer++;
	  }
	  else{
	    exactStr[insertionIndex] = instr[i];
	    insertionIndex++;
	  }
	}
	else{
	  insertionIndex++;
	  currCharPointer++;
	}
      }
    }
  }
}

char toLower(char inp){
  if(inp>=65 && inp <=90){
    return inp+32;
  }
  return inp;
}
