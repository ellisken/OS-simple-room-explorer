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

/***********************************************************************
************************** DATA STRUCTURES *****************************
***********************************************************************/
struct GameState{
    int total_steps;//Number of total steps taken
    char *cur_room;//For holding name of current room
    char *current_connects;//List of current room connections;
    int cur_room_cxct;//Connection count for current room
};



/***********************************************************************
************************ FUNCTION DEFINITIONS **************************
***********************************************************************/

/*********************************************************************
 * ** Function: initGameState()
 * ** Description: Initializes a gamestate struct
 * ** Parameters: None
 * ** Pre-Conditions: There must exist a ptr to GameState to receive the
 *      function's output
 * ** Post-Conditions: Returns a pointer to an initialized GameState
 * *********************************************************************/
struct GameState* initGameState(){
    int i, j;
    //Reserve memory for the graph
    struct GameState *gamestate=malloc(sizeof(struct GameState));
    gamestate->current_connects = malloc(sizeof(char) * (9 * MAX_CONNECTIONS));
    //Set current room name to NULL
    gamestate->cur_room = NULL;
    //Set total_steps and current room connection counts to zero
    gamestate->total_steps = 0;
    gamestate->cur_room_cxct = 0;
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
 *      pointer to gamestate
 * ** Pre-Conditions: directory, file descriptor and gamestate must be defined
 * ** Post-Conditions: gamestate->cuurent_connects[] will contain names
 *      of all connected rooms to current room
 * *********************************************************************/
void loadRoomInfo(FILE *room, struct GameState *gamestate){
    char line[256]; //For storing line's contents
    char name[256]; //For storing room name

    //Get room name from first line and store in gamestate
    memset(line, '\0', 256);
    fgets(line, 256, room);
    memset(name, '\0', 256);
    //Room name always starts at index 11
    printf("Right before name copy. Line is %s\n", line);
    strncpy(name, line + 11, strlen(line) - 11);
    printf("Right after name copy\n");
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
        strncpy(name, line + 14, strlen(line) - 14);
        strcat(gamestate->current_connects, name);
        //Increment current connection count
        gamestate->cur_room_cxct++;
        memset(line, '\0', 256);
    }
    //Decrement current connection count to offset for
    //last line's inclusion above
    gamestate->cur_room_cxct--;
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
                strcpy(line_copy, line);
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
 * ** Function: displayRoomInfo()
 * ** Description: Displays the room's name
 * ** Parameters: Directory name, pointer to gamestate
 * ** Pre-Conditions: Directory name and gamestate must be defined
 * ** Post-Conditions: gamestate->rooms[] will contain pointers to
 *      the names of each room in the game play.
 * *********************************************************************/


/***********************************************************************
******************************** MAIN **********************************
***********************************************************************/
int main(){
    //Create string for holding subdir name
    char *roomDirName = malloc(sizeof(char) * 256);
    DIR *roomDir;//pointer to room dir
    char type[20];
    FILE *cur_file = NULL;
    FILE *end_file = NULL; //Stores pointer to descriptor for file containing END_ROOM

    //Initialize GameState
    struct GameState *gamestate = initGameState();
    assert(gamestate != NULL);
   
    //Find correct directory and open
    findNewestDir(roomDirName);

    //Load all room names into gamestate

    //Find START_ROOM and END_ROOM
    memset(type, '\0', sizeof(type));
    strcpy(type, "START_ROOM");
    //Point cur_file to mem location returned
    cur_file = findRoomByType(roomDirName, type);
    assert(cur_file != NULL);
    memset(type, '\0', sizeof(type));
    strcpy(type, "END_ROOM");
    //Point end_file to endlocation returned
    end_file = findRoomByType(roomDirName, type);
    assert(end_file != NULL);

    //Load current room info into gamestate
    loadRoomInfo(cur_file, gamestate);
    printf("Current room name: %s\n", gamestate->cur_room);
    printf("Current room connections: %s\n", gamestate->current_connects);
    printf("Current room connect_ct: %i\n", gamestate->cur_room_cxct);

    //At end?
    if(cur_file == end_file){
        //Display end message
        printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
        //Print total steps
        //Print path
        //Clean up
        fclose(cur_file);
        fclose(end_file);
        freeGameState(gamestate);
        free(roomDirName);
    }
    //Display room name and comma separated list of connections
    //Prompt WHERE TO?
    //Check that name entered exists
        //If not, displayerror and reprompt
        //Else, go to chosen room and continue play
    return 0;
}
