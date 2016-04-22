#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char key[64] = "org.gnome.settings-daemon.plugins.media-keys custom-keybindings";
char subkey1[65] = "org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:";
char item_s[66] = "/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/";
char firstname[7] = "custom";



char* concat(char *s1, char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char* mergeNewKeyAndCurrent(char* newKey, char** current){
    char* newCurrent = calloc(1,100*25); // 100 char per key times 25 keys
    //printf("\n---%s\n", newCurrent);
    int index;
    for(index = 0; strcmp( current[index], "FIN" ) && index < 50; index++){
        strcat(newCurrent, "'");
        strcat(newCurrent, current[index]);
        strcat(newCurrent, "', ");
    }
    
    strcat(newCurrent, "'");
    strcat(newCurrent, newKey);
    strcat(newCurrent, "'");

    //printf("---%s", newCurrent);
    return newCurrent;
}
char** parseCurrentKeysIntoArray(char* currentString){
    int index;
    char thisChar;
    char* stringHold;
    char** stringArray = (char **)calloc(50, 256);
    int stringHoldIndex = 0;
    int stringArrayIndex = 0;
    int collectString = 0;
    for (index = 0; currentString[index]; index++) {
        thisChar = currentString[index];
        //printf("%c-",thisChar);
        if(thisChar == '\'' && collectString == 0){
            //printf("here i am!");
            collectString = 1;
            stringHold = (char *)calloc(1,256);
            //printf("still i am!");
        } else if(thisChar == '\''){
            collectString = 0;
            stringArray[stringArrayIndex] = stringHold;
            stringArrayIndex++;
            stringHoldIndex = 0;
        } else if(collectString == 1){
            stringHold[stringHoldIndex] = thisChar;   
            stringHoldIndex++;
        }
       // i points successively to a[0], a[1], ... until a '\0' is observed.
    }
    /*
    stringHold = (char *)malloc(6);
    stringHold = "FINder";
    stringArray[stringArrayIndex] = stringHold;
    stringArrayIndex++;
    */
    stringHold = (char *)malloc(3);
    stringHold = "FIN";
    stringArray[stringArrayIndex] = stringHold;
    //printf("\n%s",stringArray[0]);
    return stringArray;
}
char* findUniqueKey(char** current){
    int index;
    //printf("%i", strcmp(current[0], "FIN"));
    //printf("%s",current[0]);
    char* newKey = concat(item_s, firstname);
    char* testKey;
    //printf("\n%s\n", newKey);
    int testN = 0;
    char buf[sizeof(int)*3+2];
    snprintf(buf, sizeof buf, "%i", testN);
    testKey = concat(newKey, buf);
    testKey = concat(testKey, "/");
    //printf("%s", testKey);
    for(index = 0; strcmp( current[index], "FIN" ) && index < 50; index++){
        if(!strcmp(current[index], testKey)){ // if this key already exists, increase N and run through them again.
            index=0;
            testN++;
            snprintf(buf, sizeof buf, "%i", testN);
            testKey = concat(newKey, buf);
            testKey = concat(testKey, "/");
        }
        //printf("\n%s\nvs\n%s\n", testKey, current[index]);
        //printf("running");
    }
    free(testKey);
    newKey = concat(newKey, buf);
    newKey = concat(newKey, "/");
    //printf("\n%s\n", newKey);
    
    return newKey;
}
char** findUniqueKeybindKeyAndNewCurrent(){
    FILE *fp;
    char path[1035];
    int n = 0;
    char** current;

    ////////////////////////////////////////////////////
    /////////// Run Command ////////////////////////////
    ////////////////////////////////////////////////////
    char* command = concat("gsettings get ", key);
    printf("%s\n",command);
    /* Open the command for reading. */
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    free(command);
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    /* Read the output line (should only be one for the above command) - parse it. */
    fgets(path, sizeof(path)-1, fp);
    /* close */
    pclose(fp);
    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    
    printf("%s", path);
    current = parseCurrentKeysIntoArray(path);
    //char* thisOne = current[0];
    //printf("%s", thisOne);
    
    char* newKey = findUniqueKey(current);
    
    
    char* newCurrent = mergeNewKeyAndCurrent(newKey, current);
    free(current);

    char** stringArray = (char **)calloc(2,sizeof(newCurrent));
    stringArray[0] = newKey;
    stringArray[1] = newCurrent;
    return stringArray;
}

int bindNewKey(char* newKey, char* newCurrent, char* name, char* command, char* binding){
    
    char cmd0[100*26] = {}; //100 chars per key, 25 keys in current new + main key
    strcat(cmd0, "gsettings set ");
    strcat(cmd0, key);
    strcat(cmd0, " \"[");
    strcat(cmd0, newCurrent);
    strcat(cmd0, "]\"");
    
    char cmd1[250] = {}; // two key values tops
    strcat(cmd1, "gsettings set ");
    strcat(cmd1, subkey1);
    strcat(cmd1, newKey);
    strcat(cmd1, " name '");
    strcat(cmd1, name);
    strcat(cmd1, "'");
    
    char cmd2[250] = {}; // two key values tops 
    strcat(cmd2, "gsettings set ");
    strcat(cmd2, subkey1);
    strcat(cmd2, newKey);
    strcat(cmd2, " command '");
    strcat(cmd2, command);
    strcat(cmd2, "'");
    
    char cmd3[250] = {}; // two key values tops 
    strcat(cmd3, "gsettings set ");
    strcat(cmd3, subkey1);
    strcat(cmd3, newKey);
    strcat(cmd3, " binding '");
    strcat(cmd3, binding);
    strcat(cmd3, "'");
    
    /*
cmd1 = 'gsettings set '+subkey1+new+" name '"+sys.argv[1]+"'"
cmd2 = 'gsettings set '+subkey1+new+" command '"+sys.argv[2]+"'"
cmd3 = 'gsettings set '+subkey1+new+" binding '"+sys.argv[3]+"'"
    */
    
    printf("\n%s\n", cmd0);
    printf("\n%s\n", cmd1);
    printf("\n%s\n", cmd2);
    printf("\n%s\n", cmd3);
    
    
    runThisCommand(cmd0);
    runThisCommand(cmd1);
    runThisCommand(cmd2);
    runThisCommand(cmd3);
    
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

int main( int argc, char *argv[] ){
    //printf("%s\n", gsettingsKey);
    
    //printf("%s\n\n", argv[1]);
    //exit(1);
    
    char** data = findUniqueKeybindKeyAndNewCurrent();
    
    printf("\n%s\n", data[0]);
    printf("\n%s\n", data[1]);
    
    char* newKey = data[0];
    char* newCurrent = data[1];
    
    bindNewKey(newKey, newCurrent, argv[1], argv[2], argv[3]);
    
    //int numExist = determineNumberOfExistingKeybinds();
    //printf("\n%i\n", numExist);
    
    //char cmd0 = "cmd0 = 'gsettings set '+key+' '";
    
    
    printf("\nEND\n");
    return 0;   
}