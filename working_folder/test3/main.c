//dertermine type of node that we are at


#include <stdio.h>
#include <time.h>


#include "module.h"

#define MAP_MAX 2
#define MAP_MIN 0

#define X_AT_START 0
#define Y_AT_START 0

#define NUMBER_OF_NODES 9
#define NUMBER_OF_NODES_EXPLORED_AT_START 0

#define MAP_SIZE 3
typedef enum {NORTH=1111,SOUTH=1221,EAST=1331,WEST=1441} direction;

typedef enum {CORNER_NW=100,CORNER_NE=200,CORNER_SW=300,CORNER_SE=400,SIDE_NORTH=10,SIDE_EAST=20,SIDE_SOUTH=30,SIDE_WEST=40,INTERIOR=255} node_type;

struct map
{
	direction current_direction;
	node_type current_node_type;

	int max;
	int min;

	int current_x;
	int current_y;

	int number_of_nodes;
	int nodes_explored;
	int node_map[MAP_SIZE][MAP_SIZE];
		
};

void delay(int number_of_seconds);
int update_x(int X);
int update_y(int X, int Y);
void check_for_completion( int nodes_max, int nodes_explored);
int update_nodes_explored(int *node_map, int nodes_explored);
node_type check_node_type(int X, int Y,int min, int max);

int main()
{
	int whil_loop_itterations = 0;
        struct map map={SOUTH,CORNER_SW,MAP_MAX,MAP_MIN,X_AT_START,Y_AT_START,NUMBER_OF_NODES,NUMBER_OF_NODES_EXPLORED_AT_START,{{0,0,0},
																 {0,0,0},
																 {0,0,0}}
																};

	while(1)
	{
		//print the values that we are updating		
		//update nodes explored and type of node
		map.nodes_explored=update_nodes_explored(&(map.node_map[map.current_x][map.current_y]),map.nodes_explored);
		map.current_node_type=check_node_type(map.current_x,map.current_y,map.min,map.max);
                printf("x: %d, y: %d, type of node: %d, nodes_explored: %d\n", map.current_x, map.current_y,map.current_node_type,map.nodes_explored);
		//update the x and y coordiantes
		map.current_x=update_x(map.current_x);
		map.current_y=update_y(map.current_x,map.current_y);

		//check if we have explored every map location
		check_for_completion(map.number_of_nodes, map.nodes_explored);
              
	       	//once we go through the entire map once, restart	
		if(map.current_y==3)
		{
			map.current_y=0;
			map.current_x=0;
		}

		//chang this to %20 and ==19 for back-tracking of the the maze
			//shows that it is working better
		//stop the while loop after 19 iterations
		whil_loop_itterations=(whil_loop_itterations+1)%20;
		if(whil_loop_itterations==19)
                {
			printf("we is did, whil_loop_itterations=19\n");
			return 0;
		}

	}
}

int update_x(int X)
{
	X=(X+1)%3;
	return X;

}
int update_y(int X, int Y)
{
	if(X==0)
	{
		Y=(Y+1)%4;
		return Y;
	}
		return Y;
}
int update_nodes_explored( int *node_map, int nodes_explored)
{
	if(!((*node_map)&&1))
	{
		*node_map=1;
		nodes_explored=nodes_explored +1;
	}
	return nodes_explored;

}
void check_for_completion(int nodes_max, int nodes_explored)
{
                if(nodes_explored==nodes_max)
		{
			printf("explored all the grid\n"); 
		}
}


node_type check_node_type(int X, int Y,int min, int max)
{
//typedef enum {CORNER_NW=100,CORNER_NE=200,CORNER_SW=300,CORNER_SE=400,SIDE_NORTH=10,SIDE_EAST=20,SIDE_SOURTH=30,SIDE_WEST=40,INTERIOR=255} node_type;
	//the interior is check first, in even a 4x4 grid, there are the highest number of interior positons
	if((X!=max)&&(X!=min)&&(Y!=max)&&(Y!=min))
	{
		//printf("\nX: %d, Y: %d\n\n", X,Y);
		return INTERIOR;
	}
	/////////////////////////////////
	if((X!=max)&&(X!=min)&&(Y==max))
	{
		return SIDE_NORTH;
	}
	if((X==max)&&(Y!=max)&&(Y!=min))
        {
                return SIDE_EAST;
        }
	if((X!=max)&&(X!=min)&&(Y==min))
        {
                return SIDE_SOUTH;
        }
	if((X==min)&&(Y!=max)&&(Y!=min))
        {
                return SIDE_WEST;
        }
	////////////////////////////////
        if((X==min)&&(Y==max))
        {
                return CORNER_NW;
        }
        if((X==max)&&(Y==max))
        {
                return CORNER_NE;
        }
        if((X==max)&&(Y==min))
        {
                return CORNER_SE;
        }
        if((X==min)&&(Y==min))
        {
                return CORNER_SW ;
        }
	return 1212121212;
	//sides are checked next, there are the second most of these types of nodes
	//corners are checked last, there will only ever be 4 of theses node types
}





void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

