#include<cstring>
#include<iostream>
#include"stop_info.h"
#include"queue_cities.h"

using namespace std;



//Default constructor the the queue
q_cities::q_cities()
{
	rear = NULL;
}



//Destructor for the queue
q_cities::~q_cities()
{
	q_node * temp;

	if (rear != NULL)
	{
		while (rear != rear->next)
		{
			temp = rear->next;
			rear->next = rear->next->next;
			delete temp;
		}

		delete rear;
		rear = NULL;
	}
}



//Peek function
int q_cities::peek(stop_info & to_peek)
{
	if (!rear) //Checks to see if queue is empty
		return 0;

	//Passed front object to main for printing
	to_peek.copy_stop(rear->next->next_stop);
	
	return 1;
}



//Recursive wrapper function returns 0 if queue is empty
int q_cities::display_all(void)
{
	if (!rear)
	{
		return 0;
	}

	return display_all(rear->next);
}



//Recursive function's base case is the node pointer for
//traversal finally matches the rear pointer.
//This works even if the queue only has 1 node.
int q_cities::display_all(q_node * &current)
{
	if (current == rear)
	{
		current->next_stop.display_q_stop();	
		return 1;
	}

	current->next_stop.display_q_stop();	

	return display_all(current->next);
}	



//Enqueue function
int q_cities::enqueue(const stop_info & to_add)
{
	q_node * current;

	if (!rear) //Creates new head if queue has not been created
	{
		rear = new q_node;
		rear->next_stop.copy_stop(to_add);
		rear->next = rear;
		return 1;
	}

	//If the list already exists, this creates a new node with
	//the new info and links it into the existing list
	current = new q_node;
	current->next_stop.copy_stop(to_add);
	current->next = rear->next;
	rear->next = current;
	rear = current;
	return 1;
}	



//Dequeue function
int q_cities::dequeue(stop_info & to_copy)
{
	q_node * temp;

	if (!rear) //Returns -1 if the list is empty
	{
		return -1;
	}

	//Returns 0 if the list only has one node
	//This is important for the calling function
	//because it transitions to the return trip
	//once the queue is emptied.
	if (rear == rear->next) 
	{
		to_copy.copy_stop(rear->next_stop);
		delete rear;
		rear = NULL;
		return 0;
	}

	temp = rear->next;
	to_copy.copy_stop(temp->next_stop);
	rear->next = rear->next->next;
	delete temp;
	
	return 1;
}	
