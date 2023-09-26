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
    LoadBalancer();
    LoadBalancer(size_t runtime, size_t num_servers, size_t num_requests);
    LoadBalancer(const LoadBalancer& other);
    LoadBalancer(LoadBalancer&& other);
    ~LoadBalancer();

    LoadBalancer& operator=(const LoadBalancer& other);
    LoadBalancer& operator=(LoadBalancer&& other);

    void run();
    void printLog(ostream& os = cout) const;
};

#endif // LOAD_BALANCER_H
