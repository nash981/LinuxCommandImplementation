#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strValidator(char* pattern);
char toLower(char inp);
void strSearchCaseSen(char* pattern, char* instr,int printFlag);
void strSearchCaseSenPattern(char* pattern, char* instr,int printFlag);
void strSearchCaseInSen(char* pattern, char* instr,int printFlag);
void strSearchCaseInSenPattern(char* pattern, char* instr,int printFlag);

int main(int argc, char *argv[]){
  if(argc == 0){
    fwrite("Requires more command-line arguments.\n",38,1,stderr);
    exit(1);
  }
  int caseSen = 0;
  int pattern = 0;
  int printStat =  0;
  int patternIndex;
  char inputline[200];

  // Split into patterns and flags

  for(int i=0;i<argc;i++){
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
  // Validating the Search pattern
  if(strValidator(argv[patternIndex]) == 0){
    fwrite("Invalid search term.\n",21,1,stderr);
    exit(2);
  }

  // Processing the input Strings
  while (fgets(inputline, 200, stdin) != NULL){
    if(caseSen == 0){	// Case Sensitive
      if(pattern == 0){ // Without pattern match
	strSearchCaseSen(argv[patternIndex], inputline, printStat);
      }
      else{ // With pattern match
	strSearchCaseSenPattern(argv[patternIndex], inputline, printStat);
      }
    }
    else{
      if(pattern == 0){
	strSearchCaseInSen(argv[patternIndex], inputline, printStat);
      }
      else{
	strSearchCaseInSenPattern(argv[patternIndex], inputline, printStat);
      }
    }
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

void strSearchCaseSen(char* pattern, char* instr,int printFlag){
  char exactStr[200];
  int insertionIndex =0;
  int currCharPointer = 0 ;
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
      insertionIndex =0;
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


void strSearchCaseSenPattern(char* pattern, char* instr,int printFlag){  
  char exactStr[200];
  int insertionIndex =0;
  int currCharPointer = 0;
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
      insertionIndex =0;
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

void strSearchCaseInSen(char* pattern, char* instr,int printFlag){  
  char exactStr[200];
  int insertionIndex =0;
  int currCharPointer = 0;
   for(int i=0; i<strlen(instr); i++){
     if(pattern[currCharPointer] == '\0'){
       exactStr[insertionIndex] = '\0';
       if(printFlag == 0){
	 printf("%s",instr);
	 break;
       }
       else{
	 printf("%s\n",exactStr);
       }
       insertionIndex = 0;
       currCharPointer = 0;
       //      printf("wot");
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

void strSearchCaseInSenPattern(char* pattern, char* instr,int printFlag){  
  char exactStr[200];
  int insertionIndex =0;
  int currCharPointer = 0;
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

char toLower(char inp){
  if(inp>=65 && inp <=90){
    return inp+32;
  }
  return inp;
}
