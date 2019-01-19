#include <stdio.h>
#include "chaine.h"

int main(int argc, char *argv[]){

	int result;

  	result = palindrome(argv[1]);

  	if(result == 1){
    	printf("%s is a palindrome", argv[1]);
  	}
  	else{
    	printf("%s isn't a palindrome", argv[1]);
  	}

  	return 0;
}

int length(char string[]){

  	int i = 0;
  	while(string[i] != '\0'){
	  	i ++;
  	}
  	return i;
}

int palindrome(char string[]){
  	int i = 0, j = 0;
  	int size = length(string);

  	for(i = size - 1, j = 0; i >= 0, j <= size - 1; i--, j++){ 
    	if (string[i] != string[j]){
      		return 0;
    	}
  	}
  	return 1;
}
