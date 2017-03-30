#ifndef STOP_STRUCT
#define STOP_STRUCT

/*
stop_info: The stop_info class holds all of the relevant information for each stop. 
This same class will be used both by the queue and the stack.
Although the queue requires less information, this object
has two display functions, one for the queue and the stack
to address their different requirements.  The rating and cost
are initialized to 0 while in the queue.
*/

class stop_info
{
	public:
		stop_info();
		stop_info(char * name, char * loc, char * lodge, int dist);
		~stop_info();

		int display_q_stop(void);
		int display_stop(void);

		int copy_stop(const stop_info & to_copy);
		int add_info(const int rating, const double cost);

	private:
		char * stop_name;
		char * location;
		char * lodging;
		int distance;
		int lodging_rating;
		double gas_cost;
};


#endif
