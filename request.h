#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <sstream>

using std::string, std::to_string;
using std::ostringstream, std::ostream;
using std::move;

class Request {
private:
    string ipIn;
    string ipOut;
    size_t duration;
public:
    Request();
    Request(const string& ipIn, const string& ipOut, size_t duration);
    Request(const Request& other);
    Request(Request&& other);
    ~Request();

    Request& operator=(const Request& other);
    Request& operator=(Request&& other);

    const size_t& getDuration() const;

    friend ostream& operator<<(ostream& os, const Request request);
};

#endif // REQUEST_H
