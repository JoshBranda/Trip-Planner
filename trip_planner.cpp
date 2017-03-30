/*
Josh Sander
10/23/2016
CS163
Program 2

This program helps a user plan and execute a trip.  There are three supporting ADTs:
Queue: queue_cities uses a circular linked list to maintain the user's first half of their trip
Stack: stack_cities uses a linear linked list of arrays to maintain the users return trip
Stop: stop_info contains the relevant information of each stop

The user application is divided into 3 menus:
Menu 1: Allows the user to create their itinerary.  This is separate from executing the queue
so that the user may remove an entry made in error before beginning their trip (without damaging the stack).

Menu 2: Once the user is ready to begin their trip, menu 2 is used.  Users complete stops on their trip
which are then added to the stack with the additional information of the lodging rating and gas price.
This menu uses the return value of the dequeue function to let the program know when their itinerary is empty.
Once empty, it automatically transitions to the return trip (and the stack).

Menu 3: This is the user's return trip.  Using return values from the pop function, the menu autmotically exits
once the stack list has been emptied. 
*/

#include<iostream>
#include<cstring>
#include"stack_cities.h"
#include"queue_cities.h"

using namespace std;

const int MAX_CHAR = 100; //For user input
const int MAX_ARRAY = 5; //To be passed to the stack class

int add_stop(q_cities & itinerary);
int view_next(q_cities & itinerary);
int add_return_stop(q_cities & itinerary, stack_cities & return_trip, char choice);
int view_next_return(stack_cities & return_trip);

int main()
{
	char choice;
	q_cities my_itinerary; //Queue object to be used for the program
	stack_cities return_trip(MAX_ARRAY); //Stack object to be used for the program

	do
	{
		cout << endl;
		cout << "Welcome to your trip planner!" << endl << endl;
		cout << "Please choose from the following:" << endl;
		cout << "A: Enter a new stop on your itenerary" << endl;
		cout << "B: Display your itinerary" << endl;
		cout << "C: Display your next stop" << endl;
		cout << "D: Remove your next stop from the list" << endl;
		cout << "E: My itinerary is done.  Begin my trip!" << endl;
		cout << "F: Exit program" << endl;
		cout << endl;

		cin >> choice;
		cin.ignore();
		cout << endl;

		switch (choice)
		{
			case 'a':
			case 'A':
				add_stop(my_itinerary);
				break;
			case 'b':
			case 'B':
				if (my_itinerary.display_all() == 0)
					cout << "There is nothing in your list!" << endl;
				break;
			case 'c':
			case 'C':
				view_next(my_itinerary);
				break;
			case 'd':
			case 'D':
				add_return_stop(my_itinerary, return_trip, choice);
				break;
			case 'e':
			case 'E':
				break;
			case 'f':
			case 'F':
				break;
			defualt:
				cout << "This is not a valid input!" << endl;
				break;
		}
	} while (choice != 'f' && choice != 'F' && choice != 'e' && choice != 'E'); //If user wants to quit or begin trip

	if (choice == 'e' || choice == 'E') //User begins trip
	{
		do
		{
			cout << endl;
			cout << "Please choose from the following:" << endl;
			cout << "A: Display your next stop" << endl;
			cout << "B: Display your itinerary" << endl;
			cout << "C: I've completed my stop!" << endl;
			cout << "D: Display your return trip so far" << endl;
			cout << "F: Exit program" << endl;
			cout << endl;

			cin >> choice;
			cin.ignore();
			cout << endl;

			switch (choice)
			{
				case 'a':
				case 'A':
					view_next(my_itinerary);
					break;
				case 'b':
				case 'B':
					if (my_itinerary.display_all() == 0)
						cout << "There is nothing in your list!" << endl;
					break;
				case 'c':
				case 'C':
					if (add_return_stop(my_itinerary, return_trip, choice) == 0)
						choice = 'e';
					break;
				case 'd':
				case 'D':
					return_trip.display_all();
					break;
				case 'f':
				case 'F':
					break;
				default:
					cout << "This is not a valid input!" << endl;
					break;
			}
		} while (choice != 'f' && choice != 'F' && choice != 'e');
	}

	if (choice == 'e')
	{
		do
		{
			cout << endl;
			cout << "You finished the first leg! Let's return!" << endl;
			cout << "A: Display your next stop" << endl;
			cout << "B: Display your return itinerary" << endl;
			cout << "C: I've completed my stop!" << endl;
			cout << "F: Exit program" << endl;
			cout << endl;

			cin >> choice;
			cin.ignore();
			cout << endl;

			switch (choice)
			{
				case 'a':
				case 'A':
					view_next_return(return_trip);
					break;
				case 'b':
				case 'B':
					return_trip.display_all();
					break;
				case 'c':
				case 'C':
					if (return_trip.pop_stop() == 0)
						choice = 'd';
					else
						cout << "One more down!" << endl;
					break;
				case 'f':
				case 'F':
					break;
				default:
					cout << "This is not a valid input!" << endl;
					break;
			}
		} while (choice != 'f' && choice != 'F' && choice != 'd');
	}

	if (choice == 'd')
	{
		cout << "You have completed your trip successfully!  You can now ride into Valhalla, shiny and chrome!" << endl;
	}

	return 0;
}



//Allows users to input new stop info
int add_stop(q_cities & itinerary)
{
	char stop_name[MAX_CHAR], location[MAX_CHAR], lodging[MAX_CHAR];
	int distance;

	cout << "Please enter the name of your stop: ";
	cin.getline(stop_name,MAX_CHAR);
	cout << endl;
	cout << "Please enter location (city and state): "; 
	cin.getline(location,MAX_CHAR);
	cout << endl;
	cout << "Please enter the lodging info (name, address, and price): ";
	cin.getline(lodging,MAX_CHAR);
	cout << endl;
	cout << "Please enter the number of miles to this location: ";
	cin >> distance;
	cin.ignore();

	stop_info temp_stop(stop_name,location,lodging,distance);

	itinerary.enqueue(temp_stop);

	return 1;
}



//Views the next stop in the list
int view_next(q_cities & itinerary)
{
	stop_info temp;

	if (itinerary.peek(temp) != 0) //Executes display if list is not empty
	{
		temp.display_q_stop();
		return 1;
	}

	cout << "There is nothing in your list!" << endl;
	return 0;
}



//Transfers the stop from the dequeue function of the queue to the push function of the stack
int add_return_stop(q_cities & itinerary, stack_cities & return_trip, char choice)
{
	stop_info new_stop;
	int rating, result;
	double cost;

	result = itinerary.dequeue(new_stop);	

	if (result  == -1) //Returns -1 if queue is empty
	{
		cout << "There is nothing in your list!" << endl;
		return -1;
	}

	//This checks to see if dequeue is being peformed during execution of the trip or not
	//If it is during the trip, it needs to be pushed onto the stack with the added information.
	if (choice == 'c' || choice == 'C')
	{
		cout << "How many stars would you give your lodging on 1-4? (4 = Excellent, 3 = good, 2 = average, 1 = poor" << endl;
		cin >> rating;
		cin.ignore();
		cout << endl << "How much do you spend on gas to get here?" << endl;
		cin >> cost;
		cin.ignore();
		cout << endl;

		new_stop.add_info(rating,cost);		

		return_trip.push_stop(new_stop);

	}

	else //Removal is done before the trip begins
	{
		cout << "Stop removed!" << endl;
	}

	if (result == 0) //Returns 0 if the last item of the queue has been dequeued
		return 0;

	return 1;
}		



//Uses the stack's peek function to display the top item of the stack
int view_next_return(stack_cities & return_trip)
{
	stop_info new_stop;

	if (return_trip.peek(new_stop) == 0)
		return 0;

	new_stop.display_stop();
	
	return 1;
}

