#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void runThisCommand(char* command){
 
  FILE *fp;
  char path[1035];

  /* Open the command for reading. */
  fp = popen(command, "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }
  /* Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path)-1, fp) != NULL) {
    printf("%s", path);
  }
  /* close */
  pclose(fp);   
    
}

int main( int argc, char *argv[] ){
    char* command = argv[1];
    char* binding = argv[2];
    
    char clear1[200] = "xfconf-query --reset --channel xfce4-keyboard-shortcuts --property \"/commands/custom/"; 
    strcat(clear1, binding);
    strcat(clear1, "\"");
    char clear2[200] = "xfconf-query --reset --channel xfce4-keyboard-shortcuts --property \"/xfwm4/custom/";
    strcat(clear2, binding);
    strcat(clear2, "\"");
    
    char set[200] = "xfconf-query --create --channel xfce4-keyboard-shortcuts --property \"/commands/custom/";
    strcat(set, binding);
    strcat(set, "\" --type string --set '");
    strcat(set, command);
    strcat(set, "'");
        
    //printf("---%s\n", clear1); 
    //printf("---%s\n", clear2); 
    //printf("---%s\n", set);  
    
    runThisCommand(clear1);
    runThisCommand(clear2);
    runThisCommand(set);
    
    printf("\nEND\n");
    return 0;   
}