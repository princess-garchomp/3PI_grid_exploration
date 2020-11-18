#include "module.h"

int thing;

void evaluate(){
	if (thing>0){
	function();
	}
}

void set(int input){
	thing = input;
}


void function(){
	printf("vroom vroom");
}

void foo(int *input){
	*input = 3;
}
