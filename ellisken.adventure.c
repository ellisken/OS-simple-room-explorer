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
    char *rooms[ROOM_CT];//Room names in game
    int total_steps;//Number of total steps taken
    char *cur_room;//For holding name of current room
    char *current_connects[MAX_CONNECTIONS];//List of current room connections;
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
    //For each room in room_ct
    //Init room list to all NULL pointers 
    for(j=0; j < ROOM_CT; j++){
        gamestate->rooms[j] = NULL;
    }
    //Do the same for current_connects
    for(i=0; i < MAX_CONNECTIONS; i++){
        gamestate->current_connects[i] = NULL;
    }
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
    //Free the gamestate itself
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
void findNewestDir(char *newestDir){
    int newestDirTime = -1; //Modified timestamp of nest subdir examined
    char targetDirPrefix[32] = "ellisken.rooms."; //Prefix we're looking for
    memset(newestDir, '\0', sizeof(newestDir)); //Clear newestDir memory

    DIR *dirToCheck; //Holds starting directory
    struct dirent *fileInDir; //Holds current subdir of starting dir
    struct stat dirAttributes; //Holds info about the current subdir

    dirToCheck = open("."); //Open current directory
    
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
                    memset(newestDir, '\0', sizeof(newestDir));
                    strcpy(newestDir, fileInDir->d_name);
                }
            }
        }
    }
    //Close the opened current directory
    closedir(dirToCheck);
    return;
}  


/***********************************************************************
******************************** MAIN **********************************
***********************************************************************/
int main(){
    //Initialize GameState
    struct GameState *gamestate = initGameState();
    assert(gamestate != NULL);
   
    //Verify in correct directory

    //Find START_ROOM
    //Load room connections to gamestate
    //At end?
        //Display end message
        //Print total steps
        //Print path
        //Delete graph
        freeGameState(gamestate);
    //Display room name
    //Display comma separated list of connections
    //Prompt WHERE TO?
    //Check that name entered exists
        //If not, displayerror and reprompt
        //Else, go to chosen room and continue play
    return 0;
}
