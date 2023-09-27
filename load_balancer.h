#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
#include <queue>
#include <tuple>
#include "server.h"

using std::vector, std::queue;
using std::string;
using std::tuple;
using std::cout;

class LoadBalancer {
private:
    size_t runtime;
    size_t clock;

    vector<Server> servers;
    vector<tuple<Request, Server, size_t>> handled;
public:
    LoadBalancer() : runtime{0}, clock{0}, servers{vector<Server>{}}, handled{vector<tuple<Request, Server, size_t>>{}} {}
    LoadBalancer(size_t runtime, size_t num_servers, size_t num_requests) : runtime{runtime}, clock{0}, servers{vector<Server>(num_servers)}, handled{vector<tuple<Request, Server, size_t>>{}} {}
    LoadBalancer(const LoadBalancer& other) : runtime{other.runtime}, clock{other.clock}, servers{other.servers}, handled{other.handled} {}
    LoadBalancer(LoadBalancer&& other) : runtime{other.runtime}, clock{other.clock}, servers{move(other.servers)}, handled{move(other.handled)} {
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
        }

        return *this;
    }

    LoadBalancer& operator=(LoadBalancer&& other) {
        if (this != &other) {
            this->runtime = other.runtime;
            this->clock = other.clock;
            this->servers = move(other.servers);
            this->handled = move(other.handled);

            other.runtime = 0;
            other.clock = 0;
        }

        return *this;
    }

    void run();

    void printLog(ostream& os = cout) const {
        for (const auto& [request, server, time] : this->handled)
            os << "At " << to_string(time) << " " << server << " processed request " << request << "\n";
    }
};

#endif // LOAD_BALANCER_H
