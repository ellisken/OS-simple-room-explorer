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
 * ** Function: findRightDir()
 * ** Description: Opens the most recently created ellisken.rooms.<ID>
 *      directory created
 * ** Parameters: 
 * ** Pre-Conditions: There must exist a ptr to dirent to receive the
 *      function's output
 * ** Post-Conditions: Returns a pointer to the correct directory
 * *********************************************************************/
struct dirent* findRightDir(){



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
