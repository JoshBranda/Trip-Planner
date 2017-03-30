1:
	g++ -g -ansi trip_planner.cpp queue_cities.cpp stop_info.cpp -o test
2:
	g++ -g -ansi *.cpp -o test
clean:
	rm test
