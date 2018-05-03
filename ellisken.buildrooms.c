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

#define ROOM_CT 7

/***********************************************************************
************************** DATA STRUCTURES *****************************
***********************************************************************/
struct Room{
    char *name;//Room name
    int connex_ct;//Number of connections
    struct room *connex_list;//List of room connections;
    char *type;//start, mid, or end
};

// Define Graph struct for storing all created rooms
struct Graph{
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
struct Graph* initGraph(int room_ct){
    int i;
    assert(room_ct > 0);
    
    //Malloc new Graph
    struct Graph *graph=malloc(sizeof(struct Graph));
    //Malloc space for rooms
    graph->room_set = malloc(sizeof(struct Room) * room_ct);

    //For each room in room_ct
    for(i=0; i < room_ct; i++){
        struct Room *room = &graph->room_set[i]; //Add new blank room to room_set
        room->name = NULL;
        room->type = NULL;
        room->connex_ct = 0;
        room->connex_list = NULL;
    }
    //Return Graph
    return graph;
}



/*********************************************************************
 * ** Function: getRandomRoom()
 * ** Description: Returns a random pointer to a Room, does NOT 
 *      validate if connection can be added.
 * ** Parameters: pointer to Graph
 * ** Pre-Conditions: There must exist an initialized  graph with Rooms.
 * ** Post-Conditions: Returns a pointer to a room in the selected graph.
 * *********************************************************************/
struct Room* getRandomRoom(struct Graph* g){
    //Generate a random number between 1-7
    //Grab from graph @ corresponding index
    //Return pointer for randomly chosen room
}



/*********************************************************************
 * ** Function: canAddConnectionFrom()
 * ** Description: Returns true if a connection can be added, else
 *      returns false.
 * ** Parameters: pointer to Room
 * ** Pre-Conditions: The ptr to Room must not be NULL
 * ** Post-Conditions: None
 * *********************************************************************/
int canAddConnectionFrom(struct Room* r){
    //For given room, get connection count
    //If count < 6, return 1, else return 0
    if(r->connex_ct < 6) return 1;
    else return 0;
}



// Returns true if a connection can be added from Room x (< 6 outbound connections), false otherwise
bool CanAddConnectionFrom(Room x) 
{
    //For given room, get connection count
    //If count < 6, return true
    //Else, return false
}



// Returns true if a connection from Room x to Room y already exists, false otherwise
bool ConnectionAlreadyExists(x, y)
{
    //In room x’s array of connections
        //Search for room y’s name
        //If room y’s name in room x’s connections
            //Return true
        //Else, return false
}



// Connects Rooms x and y together, does not check if this connection is valid
void ConnectRoom(Room x, Room y) 
{
    //For room A, add pointer to B to A’s list of connections
    //Increment room A’s connection count
}



// Returns true if Rooms x and y are the same Room, false otherwise
bool IsSameRoom(Room x, Room y) 
{
    //For the given rooms, get the names
    //Compare names
    //If names are the same
        //Return true
    //Else, return false
}



// Function for printing graph contents in current dir
// with each room printed to a different file
Void createRoomFiles(){

}



//Function to assign names to rooms
Void nameRooms(){
}



//Function to assign types to rooms
Void assignRoomTypes(){
}



//Function to delete created graph
/**
 * Frees all memory allocated for a graph and the graph itself.
 * @param graph
 */
void freeGraph(struct Graph* graph)
{
}


/***********************************************************************
******************************** MAIN **********************************
***********************************************************************/
int main(){ 
        //Initialize graph
        struct Graph *graph = initGraph(ROOM_CT);
        assert(graph != NULL);
        //Connect graph
        //Name rooms
        //Assign types
        //Create dir
        //Print graph to files in dir
        //Delete graph
        //
        return 0;
}
