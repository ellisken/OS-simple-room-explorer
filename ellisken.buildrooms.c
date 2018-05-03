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

#define ROOM_CT 7
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
 * ** Description: Initializes a Graph struct with room_ct rooms.
 * ** Parameters: int room_ct, signifying the number of rooms to
 *      create.
 * ** Pre-Conditions: There must exist a ptr to Graph to receive the
 *      function's output
 * ** Post-Conditions: Returns a pointer to an initialized Graph
 * *********************************************************************/
struct Graph* initGraph(int room_ct){
    int i, j;
    
    //Reserve memory for the graph
    struct Graph *graph=malloc(sizeof(struct Graph));
    
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
    srand(time(NULL)); //seed pseudo-random num generator
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


/*********************************************************************
 * ** Function: connectionAlreadyExists()
 * ** Description: Returns true if a connection from Room a to Room b
 *      already exists, else returns fals
 * ** Parameters: pointers to Rooms a and b
 * ** Pre-Conditions: The ptrs must not be NULL
 * ** Post-Conditions: None
 * *********************************************************************/
int connectionAlreadyExists(struct Room *a, struct Room *b)
{
    assert(a != NULL);
    assert(b != NULL);
    int i;
    //Search all names in room a's connection list
    for(i=0; i < a->connex_ct; i++){
        //If a match is found, return true
        if(b == a->connex_list[i])
            return 1;
    }
    //Else, return 0
    return 0;
}


/*********************************************************************
 * ** Function: connectRoom()
 * ** Description: Connects Rooms a and b together, does not check if
 *      the connection is valid.
 * ** Parameters: pointers to rooms a and b
 * ** Pre-Conditions: The pointers must not be NULL
 * ** Post-Conditions: None
 * *********************************************************************/
void connectRoom(struct Room *a, struct Room *b) 
{
    assert(a != NULL && b != NULL);
    //For room A, add pointer to B to A’s list of connections
    a->connex_list[a->connex_ct] = b;
    //Increment room A’s connection count
    a->connex_ct++;
    return;
}


/*********************************************************************
 * ** Function: isSameRoom()
 * ** Description: Returns true if Rooms a and b are the same based
 *      on pointer equivalency.
 * ** Parameters: pointers to rooms a and b
 * ** Pre-Conditions: None
 * ** Post-Conditions: None
 * *********************************************************************/
int isSameRoom(struct Room *a, struct Room *b) 
{
    //If pointers are the same, return true (i.e., rooms are the same)
    if(a == b)
        return 1;
    //Else, return false
    return 0;
}


/*********************************************************************
 * ** Function: createRoomFiles()
 * ** Description: Creates new directory and creates individual
 *      files for each room containing room details
 * ** Parameters: pointer to Graph
 * ** Pre-Conditions: The ptr to Graph must not be NULL
 * ** Post-Conditions: None
 * *********************************************************************/
void createRoomFiles(struct Graph *graph){
    assert(graph != NULL);
    int i, j;
    for(i=0; i < ROOM_CT; i++){
        printf("Room %i connection count: %i\n", i, graph->room_set[i]->connex_ct);
        /*for(j=0; j < MAX_CONNECTIONS; j++){
            printf("\t Connection %i: %s\n", j, graph->room_set[i]->connex_list[j]->name);
        }*/
    }
    return;
}


//Function to assign names to rooms
/*********************************************************************
 * ** Function: isGraphfull()
 * ** Description: Returns true if a connection can be added, else
 *      returns false.
 * ** Parameters: pointer to Room
 * ** Pre-Conditions: The ptr to Room must not be NULL
 * ** Post-Conditions: None
 * *********************************************************************/
void nameRooms(){
    return;
}


//Function to assign types to rooms
/*********************************************************************
 * ** Function: isGraphfull()
 * ** Description: Returns true if a connection can be added, else
 *      returns false.
 * ** Parameters: pointer to Room
 * ** Pre-Conditions: The ptr to Room must not be NULL
 * ** Post-Conditions: None
 * *********************************************************************/
void assignRoomTypes(){
    return;
}


/*********************************************************************
 * ** Function: freeGraph()
 * ** Description: Frees all memory allocated for the graph's rooms
 *      and for the graph itself.
 * ** Parameters: pointer to Graph
 * ** Pre-Conditions: None
 * ** Post-Conditions: None
 * *********************************************************************/
void freeGraph(struct Graph* graph)
{
    int i;
    //Free each room in the graph
    for(i=0; i < ROOM_CT; i++){
        free(graph->room_set[i]);
    }
    //Free the graph itself
    free(graph);
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


/*********************************************************************
 * ** Function: addRandomConnection()
 * ** Description: Retrieves two randomly-selected rooms from the graph,
 *      then connects them if both have room for an additional 
 *      connection, they have no existing connection to each other, and
 *      they are not the same room
 * ** Parameters: pointer to Graph
 * ** Pre-Conditions: The ptr to Graph must not be NULL
 * ** Post-Conditions: None
 * *********************************************************************/
//Adds random connection between two rooms
void addRandomConnection(struct Graph* graph)  
{
    assert(graph != NULL);
    struct Room *A;
    struct Room *B;

    //Assign a random room to A with room for connections
    while(1)
    {
        A = getRandomRoom(graph);
        if (canAddConnectionFrom(A) == 1)
             break;
    }

    do
    {
        //Assign a random room to B
        //until a room is found that has room for connections,
        //is not the same room as A, and is not already connected to A
        B = getRandomRoom(graph);
    }
    while(canAddConnectionFrom(B) == 0 || isSameRoom(A, B) == 1 || connectionAlreadyExists(A, B) == 1);

    //Establish two-way connection between rooms
    connectRoom(A, B);
    connectRoom(B, A);
    return;
}



/***********************************************************************
******************************** MAIN **********************************
***********************************************************************/
int main(){ 
        //Initialize graph
        struct Graph *graph = initGraph(ROOM_CT);
        assert(graph != NULL);
        
        /*graph->room_set[0]->connex_ct = 3;
        graph->room_set[1]->connex_ct = 2;

        struct Room *room = getRandomRoom(graph);
        printf("The random room selected has %i connections\n", room->connex_ct);

        int result = canAddConnectionFrom(room);
        printf("Result returned from canAddConnection to room: %i\n", result);

        result = connectionAlreadyExists(graph->room_set[0], graph->room_set[1]);
        printf("Result returned from connectionAlreadyExists: %i\n", result);
        printf("Connecting rooms 1 and 2\n");
        connectRoom(graph->room_set[0], graph->room_set[1]);
        result = connectionAlreadyExists(graph->room_set[0], graph->room_set[1]);
        printf("Result returned from connectionAlreadyExists: %i\n", result);
    
        result = isSameRoom(graph->room_set[0], graph->room_set[0]);
        printf("Result returned from isSameRoom (room1, room1): %i\n", result);
        result = isSameRoom(graph->room_set[1], graph->room_set[0]->connex_list[3]);
        printf("Result returned from isSameRoom (room2, room1.2): %i\n", result);*/

        //Connect graph
        while(isGraphFull(graph) == 0){
            addRandomConnection(graph);
        }
        //Name rooms
        //Assign types
        //Create dir
        //Print graph to files in dir
        createRoomFiles(graph);
        //Delete graph
        freeGraph(graph);
        //
        return 0;
}
