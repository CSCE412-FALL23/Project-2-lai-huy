#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <iostream>
#include "request.h"

using std::string;
using std::ostream;
using std::cout;
using std::move;

/**
 * @brief The Server class represents a server that can handle requests.
 */
class Server {
private:
	/**
	 * @brief The name of the server
	 */
	string name;

	/**
	 * @brief The current request being handled by the server.
	 */
	Request curr_request;

	/**
	 * @brief The time elapsed while handling the current request.
	 *
	 */
	size_t time;

	/**
	 * @brief Indicates whether the server is actively handling a request.
	 */
	bool active;

	bool finished;

public:
	/**
	 * @brief Default constructor for the Server class.
	 */
	Server() : name{string{}}, curr_request{Request{}}, time{0}, active{false}, finished{false} {}

	/**
	 * @brief Constructor for the Server class with a specified name.
	 * @param name The name of the server.
	 */
	Server(const string& name) : name{name}, curr_request{Request{}}, time{0}, active{false}, finished{false} {}

	/**
	 * @brief Copy constructor for the Server class.
	 * @param other The server object to copy.
	 */
	Server(const Server& other) : name{other.name}, curr_request{other.curr_request}, time{other.time}, active{other.active}, finished{other.finished} {}

	/**
	 * @brief Move constructor for the Server class.
	 * @param other The server object to move.
	 */
	Server(Server&& other) : name{move(other.name)}, curr_request{move(other.curr_request)}, time{other.time}, active{other.active}, finished{other.finished} {
		other.time = 0;
		other.active = false;
		other.finished = false;
	}

	/**
	 * @brief Destructor for the Server class.
	 */
	~Server() = default;

	/**
	 * @brief Copy assignment operator for the Server class.
	 * @param other The server object to copy.
	 * @return A reference to the current server object after the copy.
	 */
	Server& operator=(const Server& other) {
		if (this != &other) {
			this->name = other.name;
			this->curr_request = other.curr_request;
			this->time = other.time;
			this->active = other.active;
			this->finished = other.finished;
		}

		return *this;
	}

	/**
	 * @brief Move assignment operator for the Server class.
	 * @param other The server object to move.
	 * @return A reference to the current server object after the move.
	 */
	Server& operator=(Server&& other) {
		if (this != &other) {
			this->name = move(other.name);
			this->curr_request = move(other.curr_request);
			this->time = other.time;
			this->active = other.active;
			this->finished = other.finished;

			other.time = 0;
			other.active = false;
			other.finished = false;
		}

		return *this;
	}

	/**
	 * @brief Set the current request for the server.
	 * @param request The request to be set.
	 */
	void setRequest(const Request& request) {
		this->curr_request = request;
		this->time = 0;
		this->active = true;
	}

	/**
	 * @brief Set the current request for the server using move semantics.
	 * @param request The request to be set.
	 */
	void setRequest(Request&& request) {
		this->curr_request = move(request);
		this->time = 0;
		this->active = true;
	}

	void clearRequest() {
		this->active = false;
		this->time = 0;
		this->finished = true;
	}

	/**
	 * @brief Handle the current request.
	 * @param os The output stream to print messages to (default is std::cout).
	 */
	void handleCurrentRequest(ostream& os = cout) {
		os << *this << " is handling " << this->curr_request << "\n";
		if (++this->time == this->curr_request.getDuration())
			this->active = false;
	}

	/**
	 * @brief Get the current request being handled by the server.
	 * @return A const reference to the current request.
	 */
	const Request& getRequest() const {
		return this->curr_request;
	}

	/**
	 * @brief Check if the server is actively handling a request.
	 * @return true if the server is active, false otherwise.
	 */
	bool isRunning() const {
		return this->active;
	}

	bool isFinished() const {
		return this->finished;
	}

	/**
	 * @brief Overloaded << operator to print the server's name.
	 * @param os The output stream.
	 * @param server The server object to print.
	 * @return The output stream.
	 */
	friend ostream& operator<<(ostream& os, const Server& server) {
		os << "Server{name=" << server.name << "}";
		return os;
	}
};

#endif // SERVER_H
