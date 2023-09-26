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
	Server();
	Server(const string& name);
	Server(const Server& other);
	Server(Server&& other);
	~Server();

	Server& operator=(const Server& other);
	Server& operator=(Server&& other);

	void setRequest(const Request& request);
	void setRequest(Request&& request);

	void handleCurrentRequest();

	const Request& getRequest() const;
	bool isRunning() const;

	friend ostream& operator<<(ostream& os, const Server& server);
};

#endif // SERVER_H
