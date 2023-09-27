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
    Request() : ipIn{string{}}, ipOut{string{}}, duration{0} {}
    Request(const string& ipIn, const string& ipOut, size_t duration) : ipIn{ipIn}, ipOut{ipOut}, duration{duration} {}
    Request(const Request& other) : ipIn{other.ipIn}, ipOut{other.ipOut}, duration{other.duration} {}
    Request(Request&& other) : ipIn{move(other.ipIn)}, ipOut{move(other.ipOut)}, duration{other.duration} {
        other.duration = 0;
    }

    ~Request() = default;

    Request& operator=(const Request& other) {
        if (this != &other) {
            this->ipIn = other.ipIn;
            this->ipOut = other.ipOut;
            this->duration = other.duration;
        }

        return *this;
    }

    Request& operator=(Request&& other) {
        if (this != &other) {
            this->ipIn = move(other.ipIn);
            this->ipOut = move(other.ipOut);
            this->duration = move(other.duration);
            other.duration = 0;
        }

        return *this;
    }

    const size_t& getDuration() const;

    friend ostream& operator<<(ostream& os, const Request request);
};

#endif // REQUEST_H
