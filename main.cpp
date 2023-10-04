#include <iostream>
#include <string>

#include "load_balancer.h"

using std::cout, std::cin, std::getline;
using std::string;

int main() {
	srand(0);
	string user_input{};
	size_t num_servers{};
	size_t runtime{};

	cout << "Please enter the number of servers: ";
	getline(cin, user_input);
	num_servers = stoul(user_input);

	cout << "Please enter the amount of time you would like to run the load balancer: ";
	getline(cin, user_input);
	runtime = stoul(user_input);

	//start the load balancer
	cout << "-------------------------------------------------------\n";
	cout << "Starting queue size: " << to_string(num_servers * 5) << "\n";
	cout << "Clock cycles: " << to_string(runtime) << "\n";
	cout << "Range for request time: 3-16 clock cycles\n";
	cout << "-------------------------------------------------------\n";
	cout << "Starting load balancer...\n";
	LoadBalancer loadbalancer(runtime, num_servers, num_servers * 5);
	loadbalancer.run();

	//Once the load balancer stops running, it means that time is up or queue is empty
	cout << "Done\n\n";
	loadbalancer.printLog();

	return 0;
}
