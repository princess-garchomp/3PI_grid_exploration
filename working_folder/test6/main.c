//up to this point I have been manually changing X,Y and setting the next_trn
//this will be randomly selcting the direction

#include <stdio.h>
#include <time.h>
#include <stdlib.h> 


#include "module.h"


//to change the size of the maze, edit the MAP_MAX, NUMBER_OF_NODES, and MAP_SIZE values accordingly

#define MAP_MAX 5
#define MAP_MIN 0

#define X_AT_START 0
#define Y_AT_START 0

#define NUMBER_OF_NODES 36
#define NUMBER_OF_NODES_EXPLORED_AT_START 0

#define MAP_SIZE 6
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
void selcet_new_turn_direction(possible_turns possible_turns,  next_turn *next_turn);
void update_x_y(int *X, int *Y, direction current_direction);
int random_number(int lower, int upper);
int main()
{
	    srand(time(0));
	int whil_loop_itterations = 0;
        struct map map={WEST,CORNER_SW,SIDE_SOUTH,RIGHT,TURN_RIGHT,MAP_MAX,MAP_MIN,X_AT_START,Y_AT_START,NUMBER_OF_NODES,NUMBER_OF_NODES_EXPLORED_AT_START,{	{0,0,0},
																 			{0,0,0},
																		 	{0,0,0}}
																			};
                printf("x: %d, y: %d, c_node_type: %d, c_direction: %d, possible_turns: %d, nodes_ex: %d, loop_iterations: %d\nprior to the whle loop\n",
                                map.current_x, map.current_y, map.current_node_type, map.current_direction, map.possible_turns,map.nodes_explored,
                        whil_loop_itterations);

	while(1)
	{
		//print the values that we are updating		
		//update nodes explored and type of node
		map.nodes_explored=update_nodes_explored(&(map.node_map[map.current_x][map.current_y]),map.nodes_explored);
		
		
		
		check_node_type(map.current_x,map.current_y,map.min,map.max,&map.current_node_type, &map.previous_node_type);
		new_possible_turns(map.previous_node_type, map.current_node_type, map.current_direction,&map.possible_turns);

		selcet_new_turn_direction(map.possible_turns, &map.next_turn);
	
	
		//I want the update to x and y to be seperate for now
		//it may make the two robot solution easir
		//
                printf("x: %d, y: %d, c_node_type: %d, c_direction: %d, possible_turns: %d, nodes_ex: %d, loop_iterations: %d, next_turn: %d\n",
                                map.current_x, map.current_y, map.current_node_type, map.current_direction, map.possible_turns,map.nodes_explored,
                        whil_loop_itterations, map.next_turn);

		new_current_direction(map.next_turn, &map.current_direction);
		update_x_y(&map.current_x,&map.current_y,map.current_direction);

		//check if we have explored every map location
		//check_for_completion(map.number_of_nodes, map.nodes_explored);
              
		
		
		if(whil_loop_itterations==2000000)
                {
			printf("we is did, whil_loop_itterations=50\n");
			return 0;
		}
		whil_loop_itterations=(whil_loop_itterations+1)%2000001;

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
	if(((current_node==SIDE_NORTH)||(current_node==SIDE_EAST)||(current_node==SIDE_SOUTH)||(current_node==SIDE_WEST))&&(previous_node==INTERIOR))
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
{///////////////////////////////////////////////////////////////////////////////////////////////////////
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
void selcet_new_turn_direction(possible_turns possible_turns, next_turn *next_turn)
{
	int random_num;
	if(possible_turns == LEFT_RIGHT_FORWARD)
	{
		random_num=random_number(0,2);
		if(random_num==0)
		{
			*next_turn=TURN_RIGHT;
		}
		else if(random_num==1)
		{
			*next_turn=TURN_LEFT;
		}
		else if(random_num==2)
		{
			*next_turn=KEEP_FORWARD;
		}

	}
	if(possible_turns == FORWARD_LEFT)
	{
		random_num=random_number(0,1);
                if(random_num==0)
                {
			*next_turn=TURN_LEFT;
                }
                else if(random_num==1)
                {
			*next_turn=KEEP_FORWARD;
                }


	}
	if(possible_turns == FORWARD_RIGHT)
	{
		random_num=random_number(0,1);
                if(random_num==0)
                {
			*next_turn=TURN_RIGHT;
                }
                else if(random_num==1)
                {
			*next_turn=KEEP_FORWARD;
                }

	}
	if(possible_turns == LEFT_RIGHT)
	{
		random_num=random_number(0,1);
                if(random_num==0)
                {
			*next_turn=TURN_RIGHT;
                }
                else if(random_num==1)
                {
			*next_turn=TURN_LEFT;
                }

	}

	if(possible_turns == RIGHT)
	{
		*next_turn = TURN_RIGHT;
	}
        if(possible_turns == LEFT)
        {
                *next_turn = TURN_LEFT;
        }
//	printf("random_number: %d\n",random_num);
	return;
}

/*
 *typedef enum {RIGHT=11,LEFT=22,FORWARD_LEFT=33,FORWARD_RIGHT=44,LEFT_RIGHT=55,LEFT_RIGHT_FORWARD=66}possible_turns;

typedef enum {KEEP_FORWARD=7777,TURN_RIGHT=8888,TURN_LEFT=9999} next_turn;


new_current_direction(map.next_turn, &map.current_direction);
void new_current_direction(next_turn turn_direction, direction *direction);


 */

//this will do for random for my testing, but I will likely implement it differently in the software that goes onto the robot
int random_number(int lower, int upper)
{
        return (rand() %(upper - lower + 1)) + lower;
}


void update_x_y(int *X, int *Y, direction current_direction)
{
	if (current_direction == NORTH)
	{
		*Y=*Y+1;
	}
        if (current_direction == EAST)
        {
                *X=*X+1;
        }
        if (current_direction == SOUTH)
        {
                *Y=*Y-1;
        }
        if (current_direction == WEST)
        {
                *X=*X-1;
        }
	return;
}
