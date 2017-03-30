#ifndef STACK_ADT
#define STACK_ADT
#include"stop_info.h"

/*
stack_cities: This ADT represents the return trip.  The struct here is the framework for
each node in the stack.  The class has the functions and indices to manage the stack.
INPUT:Size of the dynamic arrays and stop objects from the user application
OUTPUT:Int values to indicate success or failure and stop objects passed by reference.
OUTPUT:A display function prints the contents of the stack
*/

struct stack_node
{
	stack_node();
	~stack_node();

	stop_info * array;
	stack_node * next;
};



class stack_cities
{
	public:
		stack_cities();
		stack_cities(int dynamic_size);
		~stack_cities();

		//accessor functions
		int peek(stop_info & to_peek);
		int display_all(void);

		//mutator functions
		int push_stop(stop_info & to_add);
		int pop_stop(void);


	private:
		stack_node * head; 
		int top_index;
		int array_size;
};


#endif
