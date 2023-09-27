#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <iostream>
#include "request.h"

using std::string;
using std::ostream;
using std::cout;
using std::move;

class Server {
private:
	string name;
	Request curr_request;
	size_t time;
	bool active;

public:
	Server() : name{string{}}, curr_request{Request{}}, time{0}, active{false} {}
	Server(const string& name) : name{name}, curr_request{Request{}}, time{0}, active{false} {}
	Server(const Server& other) : name{other.name}, curr_request{other.curr_request}, time{other.time}, active{other.active} {}
	Server(Server&& other) : name{move(other.name)}, curr_request{move(other.curr_request)}, time{other.time}, active{other.active} {
		other.time = 0;
		other.active = false;
	}

	~Server() = default;

	Server& operator=(const Server& other) {
		if (this != &other) {
			this->name = other.name;
			this->curr_request = other.curr_request;
			this->time = other.time;
			this->active = other.active;
		}

		return *this;
	}

	Server& operator=(Server&& other) {
		if (this != &other) {
			this->name = move(other.name);
			this->curr_request = move(other.curr_request);
			this->time = other.time;
			this->active = other.active;
			other.time = 0;
			other.active = false;
		}

		return *this;
	}

	void setRequest(const Request& request);

	void setRequest(Request&& request);

	void handleCurrentRequest();

	const Request& getRequest() const;
	bool isRunning() const;

	friend ostream& operator<<(ostream& os, const Server& server);
};

#endif // SERVER_H
