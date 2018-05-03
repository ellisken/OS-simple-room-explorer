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
#include <time.h>
#include <assert.h>

#define ROOM_CT 2
#define MAX_CONNECTIONS 6

/***********************************************************************
************************** DATA STRUCTURES *****************************
***********************************************************************/
struct Room{
    char *name;//Room name
    int connex_ct;//Number of connections
    struct Room *connex_list[MAX_CONNECTIONS];//List of room connections;
    char *type;//start, mid, or end
};

// Define Graph struct for storing all created rooms
struct Graph{
  struct Room *room_set[ROOM_CT];//Container for room graph
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
    int i, j;
    assert(room_ct > 0);
    
    //Malloc new Graph
    struct Graph *graph=malloc(sizeof(struct Graph));
    
    //Set all rooms to NULL
    //graph->room_set = malloc(sizeof(struct Room) * room_ct);

    //For each room in room_ct
    for(i=0; i < room_ct; i++){
        graph->room_set[i] = malloc(sizeof(struct Room)); //Add new blank room to room_set
        graph->room_set[i]->name = NULL;
        graph->room_set[i]->type = NULL;
        graph->room_set[i]->connex_ct = 0;
        //Init connection list to all NULL pointers 
        for(j=0; j < 6; j++){
            graph->room_set[i]->connex_list[j] = NULL;
        }
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
struct Room* getRandomRoom(struct Graph* graph){
    struct Room *room;
    //Generate a random number between 0-6
    srand(time(NULL)); //seed PRNG
    int rand_num = (rand() % ROOM_CT);
    //Grab from graph @ corresponding index
    room = graph->room_set[rand_num];
    //Return pointer for randomly chosen room
    return room;
}



/*********************************************************************
 * ** Function: canAddConnectionFrom()
 * ** Description: Returns true if a connection can be added, else
 *      returns false.
 * ** Parameters: pointer to Room
 * ** Pre-Conditions: The ptr to Room must not be NULL
 * ** Post-Conditions: None
 * *********************************************************************/
int canAddConnectionFrom(struct Room *room){
    //For given room, get connection count
    //If count < 6, return 1, else return 0
    if(room->connex_ct < 6) return 1;
    else return 0;
}



// Returns true if a connection from Room x to Room y already exists, false otherwise
int connectionAlreadyExists(struct Room *a, struct Room *b)
{
    assert(a != NULL);
    assert(b != NULL);
    int i;
    //Search all names in room a's connection list
    for(i=0; i < a->connex_ct; i++){
        //If a match is found, return true
        if(b->name == a->connex_list[i]->name)
            return 1;
    }
    //Else, return 0
    return 0;
}



// Connects Rooms a and b together, does not check if this connection is valid
void connectRoom(struct Room *a, struct Room *b) 
{
    //For room A, add pointer to B to A’s list of connections
    a->connex_list[a->connex_ct] = b;
    //Increment room A’s connection count
    a->connex_ct++;
    return;
}



// Returns true if Rooms x and y are the same Room, false otherwise
int IsSameRoom(struct Room *x, struct Room *y) 
{
    //For the given rooms, get the names
    //Compare names
    //If names are the same
        //Return true
    //Else, return false
    return;
}



// Function for printing graph contents in current dir
// with each room printed to a different file
void createRoomFiles(){
    return;
}



//Function to assign names to rooms
void nameRooms(){
    return;
}



//Function to assign types to rooms
void assignRoomTypes(){
    return;
}



//Function to delete created graph
/**
 * Frees all memory allocated for a graph and the graph itself.
 * @param graph
 */
void freeGraph(struct Graph* graph)
{
    return;
}



/*********************************************************************
 * ** Function: isGraphfull()
 * ** Description: Returns true if a connection can be added, else
 *      returns false.
 * ** Parameters: pointer to Room
 * ** Pre-Conditions: The ptr to Room must not be NULL
 * ** Post-Conditions: None
 * *********************************************************************/
// Returns true if all rooms have 3 to 6 outbound connections, false otherwise
int isGraphFull(struct Graph *graph)  
{
    int i;
    //For each room in the graph
    for(i=0; i < ROOM_CT; i++){
        //If each room has more than 3 and less than 6 connections
        if(graph->room_set[i]->connex_ct > 3 && graph->room_set[i]->connex_ct < 6)
            //return true
            return 1;
        //Else, return false
        else return 0;
    }
}



/***********************************************************************
******************************** MAIN **********************************
***********************************************************************/
int main(){ 
        //Initialize graph
        struct Graph *graph = initGraph(ROOM_CT);
        assert(graph != NULL);
        graph->room_set[0]->connex_ct = 3;
        graph->room_set[1]->connex_ct = 6;

        struct Room *room = getRandomRoom(graph);
        printf("The random room selected has %i connections\n", room->connex_ct);

        int result = canAddConnectionFrom(room);
        printf("Result returned from trying to add connection to room: %i\n", result); 

        //Connect graph
        //Name rooms
        //Assign types
        //Create dir
        //Print graph to files in dir
        //Delete graph
        //
        return 0;
}
