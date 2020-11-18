//dertermine the directions that we can go
//detemine the direction we are currently faceing
//test enough of the cases to be certain that it worked


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
typedef enum {NORTH=1111,EAST=1221,SOUTH=1331,WEST=1441} direction;

typedef enum {CORNER_NE=100,CORNER_SE=200,CORNER_SW=300,CORNER_NW=400,SIDE_NORTH=10,SIDE_EAST=20,SIDE_SOUTH=30,SIDE_WEST=40,INTERIOR=255} node_type;

typedef enum {RIGHT=11,LEFT=22,FORWARD_LEFT=33,FORWARD_RIGHT=44,LEFT_RIGHT=55,LEFT_RIGHT_FORWARD=66}possible_turns;

typedef enum {KEEP_FORWARD=7777,TURN_RIGHT=8888,TURN_LEFT=9999} next_turn;

struct map
{
	direction current_direction;
	node_type current_node_type;
	node_type previous_node_type;
	possible_turns possible_turns;
	next_turn next_turn;
	
	int max;
	int min;

	int current_x;
	int current_y;

	int number_of_nodes;
	int nodes_explored;
	int node_map[MAP_SIZE][MAP_SIZE];
		
};

void check_for_completion( int nodes_max, int nodes_explored);
int update_nodes_explored(int *node_map, int nodes_explored);
void check_node_type(int X, int Y,int min, int max, node_type *new_node_type, node_type *previous_node_type);

void new_possible_turns(node_type previous_node, node_type current_node, direction current_direction,possible_turns *possible_turns);
void new_current_direction(next_turn turn_direction, direction *direction);
//
//this will be in test5 doing this randomly
//for now I will hard code it into the swirch statement
//void randomly_slect_next_direction();


int main()
{
	int whil_loop_itterations = 0;
        struct map map={WEST,CORNER_SW,SIDE_SOUTH,RIGHT,RIGHT,MAP_MAX,MAP_MIN,X_AT_START,Y_AT_START,NUMBER_OF_NODES,NUMBER_OF_NODES_EXPLORED_AT_START,{{0,0,0},
																		 {0,0,0},
																		 {0,0,0}}
																		};

	while(1)
	{
		//print the values that we are updating		
		//update nodes explored and type of node
		map.nodes_explored=update_nodes_explored(&(map.node_map[map.current_x][map.current_y]),map.nodes_explored);
		check_node_type(map.current_x,map.current_y,map.min,map.max,&map.current_node_type, &map.previous_node_type);
		new_possible_turns(map.previous_node_type, map.current_node_type, map.current_direction,&map.possible_turns);

			//I am never changing the next_turn based on possible_turns

		new_current_direction(map.next_turn,&map.current_direction);
                printf("x: %d, y: %d, current_node_type: %d, precious_node_type: %d, current_direction: %d, possible_turns: %d\n", 
				map.current_x, map.current_y, map.current_node_type, map.previous_node_type, map.current_direction, map.possible_turns);

		//check if we have explored every map location
		check_for_completion(map.number_of_nodes, map.nodes_explored);
              
		//simulates the robot moving through the maze. 
		//eventually this will be automated and random, for now I want to be specific the directions it goes
		switch(whil_loop_itterations)
		{
			//move through maze clockwise
			case(0):
			printf("start at 0,0 clockwise\n");
			map.current_x=0;
			map.current_y=0;
			map.next_turn=TURN_RIGHT;
			break;
                        case(1):
                        map.current_x=0;
                        map.current_y=1;
			map.next_turn=KEEP_FORWARD;
                        break;
                        case(2):
                        map.current_x=0;
                        map.current_y=2;
			map.next_turn=TURN_RIGHT;
                        break;
                        case(3):
                        map.current_x=1;
                        map.current_y=2;
			map.next_turn=KEEP_FORWARD;
                        break;
                        case(4):
                        map.current_x=2;
                        map.current_y=2;
			map.next_turn=TURN_RIGHT;
                        break;
                        case(5):
                        map.current_x=2;
                        map.current_y=1;
			map.next_turn=KEEP_FORWARD;
                        break;
                        case(6):
                        map.current_x=2;
                        map.current_y=0;
			map.next_turn=TURN_RIGHT;
                        break;
                        case(7):
                        map.current_x=1;
                        map.current_y=0;
			map.next_turn=KEEP_FORWARD;
                        break;
			
                        case(8):
                        map.current_x=0;
                        map.current_y=0;
			map.next_turn=TURN_RIGHT;
                        break;
			case(9):
                        map.current_x=0;
                        map.current_y=1;
			map.next_turn=TURN_RIGHT;
			//move to the center
                        break;
                        case(10):
                        map.current_x=1;
                        map.current_y=1;
			map.next_turn=TURN_RIGHT;
                        break;
                        case(11):
                        map.current_x=1;
                        map.current_y=0;
			map.next_turn=TURN_LEFT;
                        break;
                        case(12):
                        map.current_x=2;
                        map.current_y=0;
			map.next_turn=TURN_LEFT;
			//possible direction should be 22
			//direction should be 1111 butis 1331
                        break;
                        case(13):
                        map.current_x=2;
                        map.current_y=1;
			//should be 33
			map.next_turn=KEEP_FORWARD;
                        break;
                        case(14):
                        map.current_x=2;
                        map.current_y=2;
			map.next_turn=TURN_LEFT;
                        break;
                        case(15):
                        map.current_x=1;
                        map.current_y=2;
			map.next_turn=KEEP_FORWARD;
                        break;
                        case(16):
                        map.current_x=0;
                        map.current_y=2;
			map.next_turn=TURN_LEFT;
                        break;
                        case(17):
                        map.current_x=0;
                        map.current_y=1;
			map.next_turn=TURN_LEFT;
                        break;
                        case(18):
                        map.current_x=1;
                        map.current_y=1;
			map.next_turn=TURN_LEFT;
                        break;
                        case(19):
                        map.current_x=1;
                        map.current_y=2;
			//////////////////
                        break;
                        case(20):
                        map.current_x=1;
                        map.current_y=1;
                        break;
                        case(21):
                        map.current_x=2;
                        map.current_y=1;
                        break;
                        case(22):
                        map.current_x=1;
                        map.current_y=1;
                        break;
                        case(23):
                        map.current_x=1;
                        map.current_y=2;
                        break;
                        case(24):
                        map.current_x=1;
                        map.current_y=1;
                        break;
                        case(25):
                        map.current_x=0;
                        map.current_y=1;
                        break;
                        case(26):
                        map.current_x=0;
                        map.current_y=0;
                        break;
			case(27):
			break;
		}

		if(whil_loop_itterations==19)
                {
			printf("we is did, whil_loop_itterations=27\n");
			return 0;
		}
		whil_loop_itterations=(whil_loop_itterations+1)%28;

	}
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
			printf("explored all the grid--"); 
		}
}


void check_node_type(int X, int Y,int min, int max, node_type *new_node_type, node_type *previous_node_type)
{
//typedef enum {CORNER_NW=100,CORNER_NE=200,CORNER_SW=300,CORNER_SE=400,SIDE_NORTH=10,SIDE_EAST=20,SIDE_SOURTH=30,SIDE_WEST=40,INTERIOR=255} node_type;
	//the interior is check first, in even a 4x4 grid, there are the highest number of interior positons
	if((X!=max)&&(X!=min)&&(Y!=max)&&(Y!=min))
	{
		//printf("\nX: %d, Y: %d\n\n", X,Y);
		*previous_node_type = *new_node_type;
		*new_node_type = INTERIOR;
		return;	
	}
	/////////////////////////////////
	if((X!=max)&&(X!=min)&&(Y==max))
	{
		*previous_node_type = *new_node_type;
		*new_node_type = SIDE_NORTH;
	}
	if((X==max)&&(Y!=max)&&(Y!=min))
        {
		*previous_node_type = *new_node_type;
		*new_node_type = SIDE_EAST;
        }
	if((X!=max)&&(X!=min)&&(Y==min))
        {
		*previous_node_type = *new_node_type;
		*new_node_type = SIDE_SOUTH;
        }
	if((X==min)&&(Y!=max)&&(Y!=min))
        {
		*previous_node_type = *new_node_type;
		*new_node_type = SIDE_WEST;
	//	printf("previous_node_type: %d, new_node_type: %d\n",*previous_node_type,*new_node_type);
        }
	////////////////////////////////
        if((X==min)&&(Y==max))
        {
		*previous_node_type = *new_node_type;
		*new_node_type = CORNER_NW;
        }
        if((X==max)&&(Y==max))
        {
		*previous_node_type = *new_node_type;
		*new_node_type = CORNER_NE;
        }
        if((X==max)&&(Y==min))
        {
		*previous_node_type = *new_node_type;
		*new_node_type = CORNER_SE;
        }
        if((X==min)&&(Y==min))
        {
		*previous_node_type = *new_node_type;
		*new_node_type =  CORNER_SW ;
        }
	return;
	//sides are checked next, there are the second most of these types of nodes
	//corners are checked last, there will only ever be 4 of theses node types
}


void new_possible_turns(node_type previous_node, node_type current_node, direction current_direction, possible_turns *possible_turns)
{
	//again we want to have the fews insturctions while the grogram is running, so the more likely cases should come first
	//ever at interior
	if(current_node==INTERIOR)
	{
		*possible_turns=LEFT_RIGHT_FORWARD;
		return;
	}
	//side node from interior node
	if(((current_node==SIDE_NORTH)||(current_node==SIDE_EAST)||(current_node==SIDE_SOUTH)||(current_node==SIDE_EAST))&&(previous_node==INTERIOR))
	{
		*possible_turns=LEFT_RIGHT;
		return;
	}
	//next is side node to side node
	if((current_node==SIDE_NORTH) && (current_direction==EAST))
	{
		*possible_turns=FORWARD_RIGHT;
	}
        if((current_node==SIDE_NORTH) && (current_direction==WEST))
        {
                *possible_turns=FORWARD_LEFT;
        }
        if((current_node==SIDE_EAST) && (current_direction==NORTH))
        {
                *possible_turns=FORWARD_LEFT;
        }
        if((current_node==SIDE_EAST) && (current_direction==SOUTH))
        {
                *possible_turns=FORWARD_RIGHT;
        }
        if((current_node==SIDE_SOUTH) && (current_direction==EAST))
        {
                *possible_turns=FORWARD_LEFT;
        }
        if((current_node==SIDE_SOUTH) && (current_direction==WEST))
        {
                *possible_turns=FORWARD_RIGHT;
        }
        if((current_node==SIDE_WEST) && (current_direction==NORTH))
        {
                *possible_turns=FORWARD_RIGHT;
        }
        if((current_node==SIDE_WEST) && (current_direction==SOUTH))
        {
                *possible_turns=FORWARD_LEFT;
        }


	//finally all 8 corner cases
	if((current_node==CORNER_NW) && (current_direction==NORTH))
	{
		*possible_turns=RIGHT;
	}
        if((current_node==CORNER_NW) && (current_direction==WEST))
        {
                *possible_turns=LEFT;
        }
        if((current_node==CORNER_NE) && (current_direction==NORTH))
        {
                *possible_turns=LEFT;
        }
        if((current_node==CORNER_NE) && (current_direction==EAST))
        {
                *possible_turns=RIGHT;
        }
        if((current_node==CORNER_SE) && (current_direction==SOUTH))
        {
                *possible_turns=RIGHT;
        }
        if((current_node==CORNER_SE) && (current_direction==EAST))
        {
                *possible_turns=LEFT;
        }
        if((current_node==CORNER_SW) && (current_direction==SOUTH))
        {
                *possible_turns=LEFT;
        }
        if((current_node==CORNER_SW) && (current_direction==WEST))
        {
                *possible_turns=RIGHT;
        }

	return;
}
void new_current_direction(next_turn turn_direction, direction *direction)
{
	//need so many returns here becasue I am changing what I am checking and then I keep checking
	if(turn_direction==KEEP_FORWARD)
	{
		//direction stays the same
		return;
	}
	if((turn_direction==TURN_RIGHT))
	{
			if(*direction==NORTH)
			{
				*direction=EAST;
				return;
			}
			if(*direction==EAST)
			{
				*direction=SOUTH;
				return;
			}
			if(*direction==SOUTH)
			{
				*direction=WEST;
				return;
			}
			if(*direction==WEST)
			{
				*direction=NORTH;
				return;
			}
	}
        if((turn_direction==TURN_LEFT))
        {
                        if(*direction==NORTH)
                        {
                                *direction=WEST;
				return;
                        }
                        if(*direction==EAST)
                        {
				*direction=NORTH;
				return;
                        }
                        if(*direction==SOUTH)
                        {
				*direction=EAST;
				return;
                        }
                        if(*direction==WEST)
                        {
				*direction=SOUTH;
				return;
                        }
        }

}
