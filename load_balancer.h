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

class LoadBalancer {
private:
    size_t runtime;
    size_t clock;

    vector<Server> servers;
    vector<tuple<Request, Server, size_t>> handled;
    queue<Request> requests;

    size_t random(size_t min, size_t max) {
        return min + rand() % (max - min + 1);
    }

    string generate_IP() {
        ostringstream oss;
        oss << random(1, 255) << "." << random(0, 255) << "." << random(0, 255) << "." << random(1, 255);
        return oss.str();
    }

    void generateRequests(size_t num_requests, ostream& os = cout) {
        for (size_t i = 0; i < num_requests; ++i) {
            Request request{this->generate_IP(), this->generate_IP(), this->random(3, 16)};
            os << "New request:\t" << request << "\n";
            this->requests.push(request);
        }
        os << "Request queue has been populated with " << to_string(num_requests) << " requests.\n";
        os << "-----------------------------------------------------------------------------\n\n";
    }

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
    LoadBalancer() : runtime{0}, clock{0}, servers{vector<Server>{}}, handled{vector<tuple<Request, Server, size_t>>{}}, requests{queue<Request>{}} {}
    LoadBalancer(size_t runtime, size_t num_servers, size_t num_requests) : runtime{runtime}, clock{0}, servers{vector<Server>{}}, handled{vector<tuple<Request, Server, size_t>>{}}, requests{queue<Request>{}} {
        this->generateRequests(num_requests);
        this->createServers(num_servers);
    }

    LoadBalancer(const LoadBalancer& other) : runtime{other.runtime}, clock{other.clock}, servers{other.servers}, handled{other.handled}, requests{other.requests} {}
    LoadBalancer(LoadBalancer&& other) : runtime{other.runtime}, clock{other.clock}, servers{move(other.servers)}, handled{move(other.handled)}, requests{move(other.requests)} {
        other.runtime = 0;
        other.clock = 0;
    }

    ~LoadBalancer() = default;

    LoadBalancer& operator=(const LoadBalancer& other) {
        if (this != &other) {
            this->runtime = other.runtime;
            this->clock = other.clock;
            this->servers = other.servers;
            this->handled = other.handled;
            this->requests = other.requests;
        }

        return *this;
    }

    LoadBalancer& operator=(LoadBalancer&& other) {
        if (this != &other) {
            this->runtime = other.runtime;
            this->clock = other.clock;
            this->servers = move(other.servers);
            this->handled = move(other.handled);
            this->requests = move(other.requests);

            other.runtime = 0;
            other.clock = 0;
        }

        return *this;
    }

    void run(ostream& os = cout) {
        for (Server& server : this->servers) {
            server.setRequest(this->requests.front());
            this->requests.pop();
        }

        size_t finished_count{};
        while (++this->clock <= this->runtime) {
            finished_count = 0;
            os << "Clock:\t" << this->clock << "\n";
            for (Server& server : this->servers) {
                if (server.isRunning()) {
                    server.handleCurrentRequest();
                } else {
                    ++finished_count;
                    os << server << " has finished running and is waiting for a new request\n";
                    this->handled.emplace_back(server.getRequest(), server, this->clock);
                    if (!this->requests.empty()) {
                        server.setRequest(this->requests.front());
                        this->requests.pop();
                    }
                }

            }
            os << "\n";

            if (finished_count == this->servers.size())
                break;
        }
    }

    void printLog(ostream& os = cout) const {
        for (const auto& [request, server, time] : this->handled)
            os << "At " << to_string(time) << " " << server << " processed request " << request << "\n";
    }
};

#endif // LOAD_BALANCER_H
