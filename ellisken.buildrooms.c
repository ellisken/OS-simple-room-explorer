/*********************************************************************
 * ** Program Filename: ellisken.buildrooms.c
 * ** Author: Kendra Ellis <ellisken@oregonstate.edu>
 * ** Date: May 2, 2018
 * ** Description: Part of the "adventure" project for CS_344.
 *      This program builds a "graph" of connected rooms for 
 *      use in ellisken.adventure.c
 * ** Input: None
 * ** Output: A new directory called "ellisken.rooms.<PROCESS_ID>"
 *      containing 7 files, each file containing the details (name, 
 *      connections, type) of a room.
 * *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/***********************************************************************
************************** DATA STRUCTURES *****************************
***********************************************************************/
Struct Room{
    char *name;//Room name
    int connex_ct;//Number of connections
    char *connex_list;//List of room connections;
    char *type;//start, mid, or end
};

// Define Graph struct for storing all created rooms
Struct Graph{
  struct Room *room_set;//Container for room graph
};



/***********************************************************************
************************ FUNCTION DEFINITIONS **************************
***********************************************************************/
/*********************************************************************
 * ** Function: initGraph()
 * ** Description: Initializes a Graph struct with 7 rooms.
 * ** Parameters: int room_ct, signifying the number of rooms to
 *      create.
 * ** Pre-Conditions: There must exist a ptr to Graph to receive the
 *      function's output
 * ** Post-Conditions: Returns a pointer to an initialized Graph
 * *********************************************************************/

*Graph initGraph(int room_ct){
    int i;
    assert(room_ct > 0);
    
    //Malloc new Graph
    Graph *graph=malloc(sizeof(Graph));
    //Malloc space for rooms
    graph->room_set = malloc(sizeof(Room) * room_ct);

    //For each room in room_ct
    for(i=0; i < room_ct; i++){
        Room *room = &graph->room_set[i]; //Add new blank room to room_set
        room->name = NULL;
        room->type = NULL;
        room->connex_ct = 0;
        room->connex_list = NULL;
    }
    //Return Graph
    return graph;
}



/***********************************************************************
******************************** MAIN **********************************
***********************************************************************/
int main{
        //Initialize graph
        //Connect graph
        //Name rooms
        //Assign types
        //Create dir
        //Print graph to files in dir
        //Delete graph
}
