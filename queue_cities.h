#ifndef QUEUE_DIDDLY
#define QUEUE_DIDDLY

/*
queue_cities: This ADT represents the queue of the initial trip.
This also implements a recursive function, the display
INPUT:Objects to add to the queue.
OUTPUT:Int values to indicate success or failure and objects passed by reference.
OUTPUT:Display function prints objects from the queue
*/

struct q_node {
	stop_info next_stop;
	q_node * next;
};

class q_cities
{
	public:
		q_cities();
		~q_cities();

		//accessor functions
		int peek(stop_info & to_peek);
		int display_all(void);
		int display_all(q_node * &current);

		//mutator functions
		int enqueue(const stop_info & to_add);
		int dequeue(stop_info & to_copy);
		int copy_data(const stop_info & to_add);

	private:
		q_node * rear;
}; 

#endif
