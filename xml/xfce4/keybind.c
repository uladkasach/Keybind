#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//http://stackoverflow.com/questions/779875/what-is-the-function-to-replace-string-in-c
// You must free the result if result is non-NULL.
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep
    int len_with; // length of with
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    if (!orig)
        return NULL;
    if (!rep)
        rep = "";
    len_rep = strlen(rep);
    if (!with)
        with = "";
    len_with = strlen(with);

    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}


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

void clearThisBinding(char* binding){
    char clear1[200] = "xfconf-query --reset --channel xfce4-keyboard-shortcuts --property \"/commands/custom/"; 
    strcat(clear1, binding);
    strcat(clear1, "\"");
    char clear2[200] = "xfconf-query --reset --channel xfce4-keyboard-shortcuts --property \"/xfwm4/custom/";
    strcat(clear2, binding);
    strcat(clear2, "\"");

    printf("---%s\n", clear1); 
    printf("---%s\n", clear2); 
    
    runThisCommand(clear1);
    runThisCommand(clear2);
}
void clearImplicitBinding(char* binding){
    char* newBinding;
    int foundBinding = 0;
    if(strstr(binding, "<Control>") != NULL){
        newBinding = str_replace(binding, "<Control>", "<Primary>");
        foundBinding = 1;
    } else if(strstr(binding, "<Primary>") != NULL){
        newBinding = str_replace(binding, "<Control>", "<Primary>");
        foundBinding = 1;
    }
    if(foundBinding == 1) {
        //printf("FOUND ONE, was %s, now %s", binding, newBinding);  
        printf("Special Case: <Control> is equivilent to <Primary>. \n");
        clearThisBinding(newBinding);
    }
}


void setThisBinding(char* binding, char* command){
    
    char set[200] = "xfconf-query --create --channel xfce4-keyboard-shortcuts --property \"/commands/custom/";
    strcat(set, binding);
    strcat(set, "\" --type string --set '");
    strcat(set, command);
    strcat(set, "'");
    
    printf("---%s\n", set); 
    
    runThisCommand(set);
}

int main( int argc, char *argv[] ){
    printf("\n");
    
    printf("Clearing Bindings:\n");
    char* binding = argv[1];
    clearThisBinding(binding);
    clearImplicitBinding(binding); // for pairs like <Primary> and <Control>
    
    
    if(argc > 2){
        printf("\nSetting New Binding:\n");
        char* command = argv[2];
        setThisBinding(binding, command);
    }
    
    printf("\n");
    return 0;   
}