/*********************************************************************
 * ** Program Filename: ellisken.adventure.c
 * ** Author: Kendra Ellis <ellisken@oregonstate.edu>
 * ** Date: May 2, 2018
 * ** Description: Part of the "adventure" project for CS_344.
 *      This program provides an interface for the room exploration
 *      adventure.
 * ** Input: None. ellisken.buildrooms.c must be run prior to gameplay
 * ** Output: None
 * *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <assert.h>

#define ROOM_CT 7
#define MAX_CONNECTIONS 6
#define MAX_PATH_LENGTH 100

/***********************************************************************
************************** DATA STRUCTURES *****************************
***********************************************************************/
struct GameState{
    int total_steps;//Number of total steps taken
    char *path;//For tracking path during gameplay
    char *cur_room;//For holding name of current room
    char *current_connects;//List of current room connections;
    int cur_room_cxct;//Connection count for current room
};



/***********************************************************************
************************ FUNCTION DEFINITIONS **************************
***********************************************************************/

/*********************************************************************
 * ** Function: initGameState()
 * ** Description: Initializes a gamestate struct. Path, cur_room, and 
 *      current_connects are initialized in loadRoomInfo()
 * ** Parameters: None
 * ** Pre-Conditions: There must exist a ptr to GameState to receive the
 *      function's output
 * ** Post-Conditions: Returns a pointer to an initialized GameState
 * *********************************************************************/
struct GameState* initGameState(){
    int i, j;
    //Reserve memory for the graph
    struct GameState *gamestate=malloc(sizeof(struct GameState));
    gamestate->cur_room = NULL;
    gamestate->current_connects = NULL;
    //Set total_steps and current room connection counts to zero
    gamestate->total_steps = 0;
    gamestate->cur_room_cxct = 0;
    //Allocate space for the game path
    gamestate->path = malloc(sizeof(char) * (MAX_PATH_LENGTH * MAX_CONNECTIONS * 10));
    //Return Graph
    return gamestate;
}


/*********************************************************************
 * ** Function: freeGameState()
 * ** Description: Frees all memory allocated for the gamestate struct
 * ** Parameters: pointer to GameState
 * ** Pre-Conditions: None
 * ** Post-Conditions: None
 * *********************************************************************/
void freeGameState(struct GameState* gamestate)
{
    free(gamestate->current_connects);
    free(gamestate->path);
    free(gamestate->cur_room);
    free(gamestate);
    return;
}


/*********************************************************************
 * ** Function: findNewestDir()
 * ** Description: Opens the most recently created ellisken.rooms.<ID>
 *      directory created
 * ** Parameters: Takes a pointer to a string of lenth 256 for storing
 *      the name of the newest directory in
 * ** Pre-Conditions: There must exist a ptr to dirent to receive the
 *      function's output
 * ** Post-Conditions: parameter passed will contain name of newest
 *      directory in the current directory
 * ** NOTE: Based on example provided on page "2.4 Manipulating Directories"
 * **   provided by Benjamin Brewster
 * *********************************************************************/
void findNewestDir(char *newestDirName){
    int newestDirTime = -1; //Modified timestamp of nest subdir examined
    char targetDirPrefix[32] = "ellisken.rooms."; //Prefix we're looking for

    DIR *dirToCheck; //Holds starting directory
    struct dirent *fileInDir; //Holds current subdir of starting dir
    struct stat dirAttributes; //Holds info about the current subdir

    dirToCheck = opendir("."); //Open current directory
    
    //Check success    
    if(dirToCheck > 0){
        //Check each entry in current directory
        while((fileInDir = readdir(dirToCheck)) != NULL){
            //If entry has the target prefix
            if(strstr(fileInDir->d_name, targetDirPrefix) != NULL){
                //Get that subdir's attributes
                stat(fileInDir->d_name, &dirAttributes);
                //If the time is larger than newestDirTime
                if((int)dirAttributes.st_mtime > newestDirTime){
                    //Reset newestDirTime to current subdir's time
                    newestDirTime = (int)dirAttributes.st_mtime;
                    //Store current subdir name in newestDirName
                    strcpy(newestDirName, fileInDir->d_name);
                }
            }
        }
    }
    //Close the opened current directory
    closedir(dirToCheck);
    return;
}  


/*********************************************************************
 * ** Function: loadRoomInfo()
 * ** Description: Stores all names of connections to current room
 * ** Parameters: directory name, file descriptor for current room,
 *      pointer to gamestate. Adds room to gamestate->path.
 * ** Pre-Conditions: directory, file descriptor and gamestate must be defined
 * ** Post-Conditions: gamestate->cuurent_connects[] will contain names
 *      of all connected rooms to current room
 * *********************************************************************/
void loadRoomInfo(FILE *room, struct GameState *gamestate){
    char line[256]; //For storing line's contents
    char name[256]; //For storing room name

    //Clear name, path, and current_connects
    if(gamestate->current_connects != NULL)
        free(gamestate->current_connects);
    if(gamestate->cur_room != NULL)
        free(gamestate->cur_room);
    gamestate->current_connects = malloc(sizeof(char) * (10 * (MAX_CONNECTIONS+1)));
    sprintf(gamestate->current_connects, "%s", "\0");
    gamestate->cur_room = malloc(sizeof(char) * 9);
    sprintf(gamestate->cur_room, "%s", "\0");
    //Reset current connection count
    gamestate->cur_room_cxct = 0;

    //Get room name from first line and store in gamestate
    memset(line, '\0', 256);
    fgets(line, 256, room);
    //Remove trailing newline
    strtok(line, "\n");

    memset(name, '\0', 256);
    //Room name always starts at index 11
    snprintf(name, 9, "%s", line + 11);
    strcat(gamestate->cur_room, name);
   
    //For each connecting room, add that connection's name
    //to gamestate->cur_room_connects
    //Get the first line and append name to gamestate->rooms
    memset(line, '\0', 256);
    while(fgets(line, 256, room)){
        memset(name, '\0', 256);
        //Room connection names always start at index 14
        //Copy name to current_connects
        //Note that this will also append junk from the
        //last line containing ROOM TYPE
        snprintf(name, 9, "%s", line + 14); 
        strcat(gamestate->current_connects, name);
        //Add delimiter
        strcat(gamestate->current_connects, "\n");
        //Increment current connection count
        gamestate->cur_room_cxct++;
        memset(line, '\0', 256);
    }
    //Decrement current connection count to offset for
    //last line's inclusion above
    gamestate->cur_room_cxct--;
    //Return to beginning of file
    fseek(room, 0, SEEK_SET);
    return;
}


/*********************************************************************
 * ** Function: findRoomByType()
 * ** Description: Searches all files in the given directory
 *      to find the room of type START_ROOM
 * ** Parameters: Pointer to string holding name of directory to 
 *      search and pointer to strong holding room type name 
 *      
 * ** Pre-Conditions: Pointer to DIR must not be NULL
 * ** Post-Conditions: Returns a pointer to the START_ROOM file
 * *********************************************************************/
FILE* findRoomByType(char *dirname, char *room_type){
    struct dirent *current_file;
    FILE *current_fd = NULL;
    char targetPrefix[5] = "file";//Prefix of files being searched
    char filepath[256]; //For storing complete filepath

    char line[256]; //For storing first line's contents
    char line_copy[256]; //For storing first line's contents
    DIR *dir = opendir(dirname);
    assert(dir > 0);

    //For each file in the directory
    while((current_file = readdir(dir)) != NULL){
        //If file name contains "file"
        if(strstr(current_file->d_name, targetPrefix) != NULL){
            //Create filepath
            memset(filepath, '\0', 256);
            sprintf(filepath, "%s/%s", dirname, current_file->d_name);
            current_fd = fopen(filepath, "r");
            assert(current_fd > 0);
            memset(line, '\0', 256);
            //Read through file until last line copied
            while(fgets(line, 256, current_fd)){
                memset(line_copy, '\0', 256);
                sprintf(line_copy, "%s", line);
            }
            //If last line contains room_type, return file descriptor
            if(strstr(line_copy, room_type) != NULL){
                //Return file pointer to beginning of file
                fseek(current_fd, 0, SEEK_SET);
                return current_fd;//Return without closing the file
            }
            //If not found, close file
            fclose(current_fd);
        }
    }   
    return NULL;
}


/*********************************************************************
 * ** Function: endRoomFound()
 * ** Description: Returns true if current room is of type END_ROOM,
 *      otherwise returns false.
 * ** Parameters: File Descriptor for current room
 * ** Pre-Conditions: gamestate must be defined
 * ** Post-Conditions: None.
 * *********************************************************************/
int endRoomFound(FILE *room){
    char line[256]; //For storing first line's contents
    char line_copy[256]; //For storing first line's contents
    char targetSubstr[10] = "END_ROOM";//Prefix of files being searched
    //Read through file until last line copied
    memset(line, '\0', 256);
    while(fgets(line, 256, room)){
        memset(line_copy, '\0', 256);
        sprintf(line_copy, "%s", line);
    }
    //If last line contains "END_ROOM", return true
    if(strstr(line_copy, targetSubstr) != NULL){
        //Return file pointer to beginning of file
        fseek(room, 0, SEEK_SET);
        return 1;
    }
    return 0;
}


/*********************************************************************
 * ** Function: displayRoomInfo()
 * ** Description: Displays the room's name and room connections
 *      in a comma-separated list
 * ** Parameters: Pointer to gamestate
 * ** Pre-Conditions: gamestate must be defined
 * ** Post-Conditions: The current room's info will be displayed to the
 *      console
 * *********************************************************************/
void displayRoomInfo(struct GameState *gamestate){
    int i;
    char list_copy[256];
    char *name = NULL; //Pointer to store name strings for strtok
    //Display current location
    printf("CURRENT LOCATION: %s\n", gamestate->cur_room);
    //Display connection names
    printf("POSSIBLE CONNECTIONS:");
    //Make a copy of current_connects for use with strtok
    memset(list_copy, '\0', 256);
    sprintf(list_copy, "%s", gamestate->current_connects);
    //For each '\n' separated name in gamestate->current_connects
    //Print name to same line
    name = strtok(list_copy, "\n");
    for(i=1; i < gamestate->cur_room_cxct; i++){
        //name = gamestate->current_connects;
        //If last name in list, format differently
        if(i == (gamestate->cur_room_cxct - 1))
            printf(" %s.", name);
        else printf(" %s,", name);
        name = strtok(NULL, "\n");
    }
    printf("\n");
    return;
}


/*********************************************************************
 * ** Function: getCheckUserInput()
 * ** Description: Prompts user, saves user input in a string, 
 *      and verifies that the input room exactly matches a room 
 *      connected to the current room. Returns true if so, else returns false.
 * ** Parameters: Pointer to malloc'd string
 * ** Pre-Conditions: The string must be allocated first
 * ** Post-Conditions: The user input will be "saved" with the pointer
 * *********************************************************************/
int getCheckUserInput(char *input, struct GameState *gamestate){
    //Prompt user
    printf("WHERE TO ? >");
    //Get input
    fgets(input, 256, stdin);
    //Remove trailing newline in input
    strtok(input, "\n");
    //Verify name entered is connected to the current room
    if(strstr(gamestate->current_connects, input) != NULL)
        return 1;
    else return 0;
}


/*********************************************************************
 * ** Function: switchRooms()
 * ** Description: Finds room file by name (from user input)
 *      and resets cur_file to point to next room. Also adds
 *      old room to path in gamestate and updates number of steps.
 * ** Parameters: Directory name, new room name, gamestate
 * ** Pre-Conditions: dirname, new_room, and gamestate must be
 *      defined
 * ** Post-Conditions: Closes old room file, opens next room file
 *      and returns that file's handle
 * *********************************************************************/
FILE* switchRooms(char *dirname, char *new_room, struct GameState *gamestate){
    struct dirent *specified_dir;
    FILE *current_fd = NULL;
    char targetPrefix[5] = "file";//Prefix of files being searched
    char filepath[256]; //For storing complete filepath

    char line[256]; //For storing first line's contents
    char name[256]; //For storing first line's contents
    DIR *dir = opendir(dirname);
    assert(dir > 0);

    //Add new room to path
    strcat(gamestate->path, new_room);
    strcat(gamestate->path, "-");//Add delimiter

    //For each file in the directory
    while((specified_dir = readdir(dir)) != NULL){
        //If file name contains "file"
        if(strstr(specified_dir->d_name, targetPrefix) != NULL){
            //Create filepath
            memset(filepath, '\0', 256);
            sprintf(filepath, "%s/%s", dirname, specified_dir->d_name);
            current_fd = fopen(filepath, "r");
            assert(current_fd > 0);
            memset(line, '\0', 256);

            //Get room name from first line of file
            fgets(line, 256, current_fd);
            memset(name, '\0', 256);
            //Room connection names always start at index 11
            strncpy(name, line + 11, strlen(line) - 11);
            
            //If name == new_room
            if(strstr(name, new_room) != NULL){
                //Increment step count
                gamestate->total_steps++;
                //Return file pointer to beginning of file
                fseek(current_fd, 0, SEEK_SET);
                return current_fd;//Return without closing the file
            }
            //If not found, close file and keep checking
            fclose(current_fd);
        }
    }   
    return NULL;
}



/*********************************************************************
 * ** Function: endGame()
 * ** Description: Displays end of game message, prints total steps
 *      and path taken. Does not verify game over.
 * ** Parameters: gamestate
 * ** Pre-Conditions: Game must be over (endRoomFound() == true)
 * ** Post-Conditions: Closes old room file, opens next room file
 *      and returns that file's handle
 * *********************************************************************/
void endGame(struct GameState *gamestate){
    int i;
    char *name = NULL; //Pointer to store name strings for strtok
    //Display end message
    printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
    //Print total steps
    printf("YOU TOOK %i STEPS. YOUR PATH TO VICTORY WAS:\n", gamestate->total_steps);
    //Print path
    name = strtok(gamestate->path, "-");
    for(i=1; i < gamestate->total_steps; i++){
        printf("%s\n", name);
        name = strtok(NULL, "-");
    }
    printf("%s", gamestate->path);
    return;
}



/***********************************************************************
******************************** MAIN **********************************
***********************************************************************/
int main(){
    //Create string for holding subdir name
    char *roomDirName = malloc(sizeof(char) * 256);
    char *input = malloc(sizeof(char) * 256);//Stores user input
    DIR *roomDir;//pointer to room dir
    char type[20];
    FILE *cur_file = NULL;
    FILE *end_file = NULL; //Stores pointer to descriptor for file containing END_ROOM
    int result; //For checking result of getCheckUserInput()

    //Initialize GameState
    struct GameState *gamestate = initGameState();
    assert(gamestate != NULL);
   
    //Find correct directory and open
    findNewestDir(roomDirName);

    //Find START_ROOM and END_ROOM
    memset(type, '\0', sizeof(type));
    sprintf(type, "START_ROOM");
    //Point cur_file to mem location returned
    cur_file = findRoomByType(roomDirName, type);
    assert(cur_file != NULL);

    //Load current room info into gamestate
    loadRoomInfo(cur_file, gamestate);

    //Loop for gameplay
    while(1){
        //At end?
        if(endRoomFound(cur_file)){
            //If so, display end message, path, and steps
            endGame(gamestate);
            fclose(cur_file);
            freeGameState(gamestate);
            free(roomDirName);
            free(input);
            return;
        }
        //Display room name and comma separated list of connections
        displayRoomInfo(gamestate);
        result = 0; //Set (or re-set) result to false for input loop
        //Check that name entered exists
        while(result == 0){
            //If not, displayerror and reprompt
            result = getCheckUserInput(input, gamestate);
            if(result == 0)
                printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
        }
        
        //Else, close current room file and switch rooms
        fclose(cur_file);
        cur_file = switchRooms(roomDirName, input, gamestate);
        //Load new room info into gamestate
        loadRoomInfo(cur_file, gamestate);
    }
    return 0;
}
