#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
#include <queue>
#include <tuple>
#include <string>
#include <sstream>
#include "server.h"

using std::vector, std::queue;
using std::string;
using std::tuple;
using std::cout, std::ostringstream;

/**
 * @brief The LoadBalancer class represents a load balancer that distributes
 *        requests to a group of servers and logs their processing.
 */
class LoadBalancer {
private:
	/**
	 * @brief The total runtime of the load balancer.
	 */
	size_t runtime;

	/**
	 * @brief The current time elapsed in the load balancer.
	 */
	size_t clock;

	/**
	 * @brief The list of servers managed by the load balancer.
	 */
	vector<Server> servers;

	/**
	 * @brief Records of handled requests.
	 */
	vector<tuple<Request, Server, size_t>> handled;

	/**
	 * @brief Queue of incoming requests.
	 */
	queue<Request> requests;

	/**
	 * @brief the number of rejected requests
	 */
	size_t rejected_requests;

	/**
	 * @brief Generates a random number between min and max (inclusive).
	 * @param min The minimum value of the range.
	 * @param max The maximum value of the range.
	 * @return A random number within the specified range.
	 */
	size_t random(size_t min, size_t max) {
		return min + rand() % (max - min + 1);
	}

	/**
	 * @brief Generates a random IP address in the format "X.X.X.X".
	 * @return A randomly generated IP address.
	 */
	string generate_IP() {
		ostringstream oss;
		oss << random(1, 255) << "." << random(0, 255) << "." << random(0, 255) << "." << random(1, 255);
		return oss.str();
	}

	/**
	 * @brief Generates a specified number of random requests and populates the request queue.
	 * @param num_requests The number of requests to generate and enqueue.
	 * @param os The output stream for logging (default is std::cout).
	 */
	void generateRequests(size_t num_requests, ostream& os = cout) {
		size_t num_generated{};
		for (size_t i = 0; i < num_requests; ++i) {
			if (this->requests.size() + 1 > this->servers.size() * 5) {
				this->rejected_requests += (num_requests - i);
				os << "Too many incomming requests. Rejected " << to_string(num_requests - i) << " incomming request(s).\n";
				break;
			}

			Request request{this->generate_IP(), this->generate_IP(), this->random(3, 16)};
			os << "New request:\t" << request << "\n";
			this->requests.push(request);
			++num_generated;
		}
		os << "Request queue has been populated with " << to_string(num_generated) << " requests.\n";
		os << "-----------------------------------------------------------------------------\n\n";
	}

	/**
	 * @brief Creates a specified number of server instances.
	 * @param num_servers The number of server instances to create.
	 * @param os The output stream for logging (default is std::cout).
	 */
	void createServers(size_t num_servers, ostream& os = cout) {
		os << "New webservers created: ";
		for (size_t i = 0; i < num_servers; ++i) {
			this->servers.emplace_back("S" + to_string(i));
			os << this->servers.at(i);
			if (i != num_servers - 1)
				cout << ", ";
		}
		os << "\n";
	}

public:
	/**
	 * @brief Default constructor for the LoadBalancer class.
	 */
	LoadBalancer() : runtime{0}, clock{0}, servers{vector<Server>{}}, handled{vector<tuple<Request, Server, size_t>>{}}, requests{queue<Request>{}}, rejected_requests{0} {}

	/**
	 * @brief Parameterized constructor for the LoadBalancer class.
	 * @param runtime The total runtime of the load balancer.
	 * @param num_servers The number of server instances to create.
	 * @param num_requests The number of requests to generate and enqueue.
	 */
	LoadBalancer(size_t runtime, size_t num_servers, size_t num_requests)
		: runtime{runtime}, clock{0}, servers{vector<Server>{}}, handled{vector<tuple<Request, Server, size_t>>{}}, requests{queue<Request>{}}, rejected_requests{0} {
		this->createServers(num_servers);
		this->generateRequests(num_requests);
	}

	/**
	 * @brief Copy constructor for the LoadBalancer class.
	 * @param other The load balancer object to copy.
	 */
	LoadBalancer(const LoadBalancer& other)
		: runtime{other.runtime}, clock{other.clock}, servers{other.servers}, handled{other.handled}, requests{other.requests}, rejected_requests{other.rejected_requests} {
	}

	/**
	 * @brief Move constructor for the LoadBalancer class.
	 * @param other The load balancer object to move.
	 */
	LoadBalancer(LoadBalancer&& other)
		: runtime{other.runtime}, clock{other.clock}, servers{move(other.servers)}, handled{move(other.handled)}, requests{move(other.requests)}, rejected_requests{other.rejected_requests} {
		other.runtime = 0;
		other.clock = 0;
		other.rejected_requests = 0;
	}

	/**
	 * @brief Destructor for the LoadBalancer class.
	 */
	~LoadBalancer() = default;

	/**
	 * @brief Copy assignment operator for the LoadBalancer class.
	 * @param other The load balancer object to copy.
	 * @return A reference to the current load balancer object after the copy.
	 */
	LoadBalancer& operator=(const LoadBalancer& other) {
		if (this != &other) {
			this->runtime = other.runtime;
			this->clock = other.clock;
			this->servers = other.servers;
			this->handled = other.handled;
			this->requests = other.requests;
			this->rejected_requests = other.rejected_requests;
		}

		return *this;
	}

	/**
	 * @brief Move assignment operator for the LoadBalancer class.
	 * @param other The load balancer object to move.
	 * @return A reference to the current load balancer object after the move.
	 */
	LoadBalancer& operator=(LoadBalancer&& other) {
		if (this != &other) {
			this->runtime = other.runtime;
			this->clock = other.clock;
			this->servers = move(other.servers);
			this->handled = move(other.handled);
			this->requests = move(other.requests);
			this->rejected_requests = other.rejected_requests;

			other.runtime = 0;
			other.clock = 0;
			other.rejected_requests = 0;
		}

		return *this;
	}

	/**
	 * @brief Assign a request to a server
	 *
	 * @param server server to assign a request to
	 */
	void assignRequest(Server& server) {
		server.setRequest(this->requests.front());
		this->requests.pop();
	}

	/**
	 * @brief Runs the load balancer and manages the distribution of requests to servers.
	 * @param os The output stream for logging (default is std::cout).
	 */
	void run(ostream& os = cout) {
		for (Server& server : this->servers) {
			server.setActive(true);
			this->assignRequest(server);
		}

		while (++this->clock <= this->runtime) {
			os << "Clock:\t" << this->clock << "\n";
			for (Server& server : this->servers) {
				if (server.isRunning()) {
					server.handleCurrentRequest();
				} else {
					if (server.isActive()) {
						this->handled.emplace_back(server.getRequest(), server, this->clock);
						if (this->requests.empty()) {
							server.setActive(false);
							os << server << " deactivated.\n";
						} else
							this->assignRequest(server);
						os << server << " has finished running and is waiting for a new request.\n";
						os << server.getRequest() << " marked as finished.\n";
					} else if (!this->requests.empty()) {
						server.setActive(true);
						this->assignRequest(server);
					}
				}
			}

			os << "\n";

			// Randomly add requests
			if (!this->random(0, 100))
				this->generateRequests(this->random(1, 0x40));
		}
	}

	/**
	 * @brief Prints the log of handled requests by the load balancer.
	 * @param os The output stream for logging (default is std::cout).
	 */
	void printLog(ostream& os = cout) const {
		for (const auto& [request, server, time] : this->handled)
			os << "At " << to_string(time) << " " << server << " processed " << request << "\n";

		os << "Processed a total of " << to_string(this->handled.size()) << " requests.\n";
		os << "Rejected a total of " << to_string(this->rejected_requests) << " requests.\n";
	}
};

#endif // LOAD_BALANCER_H
