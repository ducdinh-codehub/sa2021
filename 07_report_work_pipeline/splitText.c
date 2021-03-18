#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int main() {
 char str[50];
  memset(str,0,sizeof(str));
  printf("Type str:\n");
  fgets(str, sizeof(str), stdin);
  int len = strlen(str);
  // display
  for(int i=0; i < len - 1; i++){
    printf("str[%d]: %c\n",i,str[i]);
  }
  // remove space
  printf("String with none space\n");
  for(int i = 0; i < len - 1; i++){
    if(str[i] == ' '){
      len = len - 1; // reduce size of string
      for(int h = i; h < len - 1; h++){
        str[h] = str[h+1];
      }  
    }
  }
  printf("Stirng length: %d\n",len);
  // display
  for(int i=0; i < len - 1; i++){
    printf("str[%d]: %c\n",i,str[i]);
  }
  // split string
  printf("Split string\n");
  char splitString[50][50];

  int numberOfSubString = 1;
  int j = 0;
  int stringIndex = 0;
  int redirectLoc = 0;
  memset(splitString[0],0,sizeof(splitString[0]));
  for(int i = 0; i < len - 1; i++){
    if(str[i] == '>' || str[i] == '|'){
      stringIndex = 0;
      j++;
      memset(splitString[j],0,sizeof(splitString[j]));
      if(str[i] == '>'){
        redirectLoc = j;
        printf("File redirect location:%d\n",redirectLoc);
      }
      i++;
      numberOfSubString++;
    }
    printf("j: %d\n",j);
    printf("stringIndex: %d\n",stringIndex);
    splitString[j][stringIndex] = str[i];
    printf("splitString[%d][%d]:%s\n",j,stringIndex,splitString[j]);
    stringIndex++;
  }
  
  // display
  for(int i = 0; i < numberOfSubString; i++){
    printf("splitString[%d]: %s\n",i,splitString[i]);
  }
    return 0;
}
  
