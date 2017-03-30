#include"stack_cities.h"
#include"stop_info.h"
#include<iostream>
#include<cstring>

using namespace std;



//Default constructor
stack_node::stack_node()
{
	array = NULL;
	next = NULL;
}



//Default destructor
stack_node::~stack_node()
{
	if (array)
		delete [] array;
}



//Constructor for the stack class.
//It only exists in the case that the user
//adds code to initialize an object
//without passing the array size as an argument
stack_cities::stack_cities()
{
	head = NULL;
	top_index = 0;
	array_size = 0;
}



//Constructor with size of dynamic array passed as argument
stack_cities::stack_cities(int dynamic_size)
{
	head = NULL;
	top_index = 0;
	array_size = dynamic_size;
}



//Destructor removes each node from the stack
stack_cities::~stack_cities()
{
	stack_node * current;
	current = head;

	while (current)
	{
		head = head->next;
		delete current;
		current = head;
	}

	head = NULL;
}



//Peek function sends the top element back by reference stop from main
int stack_cities::peek(stop_info & to_peek)
{
	stack_node * current;//In case data is in the next node
	stop_info * p_index; //For pointer arithmetic

	//This checks to see if the list is empty either because
	//it doesn't exist or it exists but everything has been popped
	if (!head || (head->next == NULL && top_index == 0))
		return 0;

	//If the top index has moved to a new/empty node, this moves back
	//to the previous (technically next) node's top element for retrieval
	if (top_index == 0)
	{
		current = head->next;
		p_index = current->array;
		to_peek.copy_stop(*(p_index + array_size - 1));
		return 1;
	}	

	p_index = head->array;
	to_peek.copy_stop(*(p_index + top_index - 1));

	return 1;
}



//This traverses the stack and calls the display function for each object in the arrays.
int stack_cities::display_all(void)
{
	stack_node * current = head; //For traversal
	stop_info * p_index; //For pointer arithmetic
	int display_index = top_index - 1; //display_index allows for top_index to remain unmodified

	//Returns 0 if the list is empty either because
	//it doesn't exist or exists but everything has been popped
	if (!head || (head->next == NULL && top_index == 0))
		return 0;

	while (current)
	{
		while (display_index > -1)
		{
			p_index = current->array;
			(*(p_index + display_index)).display_stop();
			--display_index; //Moves down the stack
		}
		
		display_index = array_size - 1; //Resets the display index to the top for the next array
		current = current->next;
	}

	return 1;
}	



//Push function to add new objects to the stack
int stack_cities::push_stop(stop_info & to_add)
{
	stack_node * current; //For creation of new head if needed
	stop_info * p_index; //For pointer arithmetic

	//Checks if stack has not yet been created
	if (!head)
	{
		head = new stack_node;
		head->array = new stop_info[array_size];
		p_index = head->array;
		(*(p_index + top_index)).copy_stop(to_add);
		++top_index; //Moves top of stack to new position
		return 1;
	}

	//Checks to see if the array is full to add a new node/array
	if (top_index == array_size)
	{
		top_index = 0; //Sets index back to first element in array
		current = new stack_node;
		current->array = new stop_info[array_size];
		p_index = current->array;
		(*(p_index + top_index)).copy_stop(to_add);
		current->next = head;
		head = current;
		++top_index;
		return 1;
	}

	p_index = head->array;
	(*(p_index + top_index)).copy_stop(to_add);
	++top_index;

	return 1;
}



//Pops the element at the top of the stack
int stack_cities::pop_stop(void)
{
	stack_node * current = head; //In case the head node needs to be deleted

	//Returns 0 if the stack has not been created or
	//if it exists but everything has already been popped
	if (!head || ((head->next == NULL) && (top_index == 1)))
		return 0;

	//The previous if establishes that there must be 2 nodes
	//for this if statement to occur.  It checks if the head node
	//is empty and needs to be removed.
	if (top_index == 0)
	{
		head = head->next;
		delete current;
		current = NULL;
		top_index = array_size - 1;
		return 1;
	}

	--top_index;	

	return 1;
}
