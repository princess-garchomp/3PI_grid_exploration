//how to update maze exploration 
//how to determine if the entire thing has been explored

#include <stdio.h>
#include <time.h>


#include "module.h"

typedef enum {NORTH=0,SOUTH=1,EAST=2,WEST=3} direction;

struct map
{
//	direction currnt_direction = EAST;
//	cant intalize struct variables like this
	direction currnt_direction;
	
	int max;
	int min;
	int number_of_nodes;
	int nodes_explored;
	int node_map[3][3];
		
};

void delay(int number_of_seconds);


int main()
{
	int x=0;
	int y=0;

	struct map current_map={WEST,2,0,9,0,{{0,0,0},{0,0,0},{0,0,0}}};

	
	while(1)
	{
		if(!(current_map.node_map[x][y] && 1))
		{
			current_map.node_map[x][y] = 1;
			current_map.nodes_explored = current_map.nodes_explored + 1;
		}
		else{}
		
	//	delay(300);	
		printf("x: %d, y: %d, nodes_explored: %d\n", x, y,current_map.nodes_explored);

		x = (x+1)%3;
		if(x==0)
		{
			y=(y+1)%5;
		}
		else{}

		if(current_map.nodes_explored == current_map.number_of_nodes)
		{
			printf("done exploring, nodes_explored: %d\n", current_map.nodes_explored);
		//	return 0;
		}
		if(y==4)
		{
		y=1;x=1;printf("x: %d, y: %d, nodes_explored: %d\n", x, y,current_map.nodes_explored);
		if(!(current_map.node_map[x][y] && 1))
                {
                        current_map.node_map[x][y] = 1;
                        current_map.nodes_explored = current_map.nodes_explored + 1;
                }

		y=1;x=2;printf("x: %d, y: %d, nodes_explored: %d\n", x, y,current_map.nodes_explored);
		if(!(current_map.node_map[x][y] && 1))
                {
                        current_map.node_map[x][y] = 1;
                        current_map.nodes_explored = current_map.nodes_explored + 1;
                }

		y=1;x=3;printf("x: %d, y: %d, nodes_explored: %d\n", x, y,current_map.nodes_explored);
		if(!(current_map.node_map[x][y] && 1))
                {
                        current_map.node_map[x][y] = 1;
                        current_map.nodes_explored = current_map.nodes_explored + 1;
                }

		y=2;x=1;printf("x: %d, y: %d, nodes_explored: %d\n", x, y,current_map.nodes_explored);
		if(!(current_map.node_map[x][y] && 1))
                {
                        current_map.node_map[x][y] = 1;
                        current_map.nodes_explored = current_map.nodes_explored + 1;
                }

			printf("failure y: %d\n",y);
			return 0;
		}
	//	delay(300);
	}
	//while(!(current_map.node_map&complete_map))
	//printf("node_map: %d\n",current_map.node_map[1][1]);
	//current_map.node_map[1][1]=2;	
	//printf("node_map: %d\n",current_map.node_map[1][1]);

	

	//if(current_map.node_map & complete_map)
	//{
	//	printf("all the values are one\n");
	//}
	printf("direction: %d\n", current_map.currnt_direction);
	current_map.currnt_direction=SOUTH;
	printf("direction: %d\n", current_map.currnt_direction);
	current_map.currnt_direction=EAST;
	printf("direction: %d\n", current_map.currnt_direction);
	current_map.currnt_direction=WEST;
	printf("direction: %d\n", current_map.currnt_direction);
	printf("direction: %d,max: %d, min: %d, number_of_nodes: %d, number_explored: %d\n", current_map.currnt_direction,current_map.max,current_map.min,current_map.number_of_nodes,current_map.nodes_explored);



}
/*
void 

if()
	//do nothing;
if(is not filled)
	fill;
	incrament counter;

*/


void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
