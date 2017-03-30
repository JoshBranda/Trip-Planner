#include"stop_info.h"
#include<cstring>
#include<iostream>

using namespace std;

//Initializes the object to NULL/0
stop_info::stop_info()
{
	stop_name = NULL;
	location = NULL;
	lodging = NULL;
	distance = 0;
	lodging_rating = 0;
	gas_cost = 0;
}



//Constructor for direct input from main
stop_info::stop_info(char * name, char * loc, char * lodge, int dist)
{

	stop_name = new char[strlen(name) + 1];
	strcpy(stop_name,name);
	location = new char[strlen(loc) + 1];
	strcpy(location,loc);
	lodging = new char[strlen(lodge) + 1]; 
	strcpy(lodging,lodge);
	distance = dist;
	lodging_rating = 0;
	gas_cost = 0;

}



//Destructor checks for any existing dynamic data and deletes
stop_info::~stop_info()
{
	if (stop_name)
		delete [] stop_name;
	if (location)
		delete [] location;
	if (lodging)
		delete [] lodging;
}	



//Prints the data relevant for the first half of the trip (queue)
int stop_info::display_q_stop(void)
{
	cout << stop_name << endl;
	cout << location << endl;
	cout << lodging << endl;
	cout << distance << " miles" << endl << endl;
	
	return 1;
}



//Prints the data relevant for the return trip (stack)
int stop_info::display_stop(void)
{
	cout << stop_name << endl;
	cout << location << endl;
	cout << lodging << endl;
	cout << distance << " miles" << endl;
	cout << lodging_rating << " stars" << endl;
	cout << "$" << gas_cost << " in gas" << endl << endl;

	return 1;
}



//Copies info from a stop passed as an argument to this stop 
int stop_info::copy_stop(const stop_info & to_copy)
{
	if (stop_name)
		delete [] stop_name;
	if (location)
		delete [] location;
	if (lodging)
		delete [] lodging;
		
	stop_name = new char[strlen(to_copy.stop_name) + 1];
	strcpy(stop_name,to_copy.stop_name);
	location = new char[strlen(to_copy.location) + 1];
	strcpy(location,to_copy.location);
	lodging = new char[strlen(to_copy.lodging) + 1]; 
	strcpy(lodging,to_copy.lodging);
	distance = to_copy.distance;
	lodging_rating = to_copy.lodging_rating;
	gas_cost = to_copy.gas_cost;

	return 1;
}



//This modifies the object from the initial trip by adding
//a rating and cost for the return trip
int stop_info::add_info(const int rating, const double cost)
{
	lodging_rating = rating;
	gas_cost = cost;
	return 1;
}
