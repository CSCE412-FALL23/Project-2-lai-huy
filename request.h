#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <sstream>

using std::string, std::to_string;
using std::ostringstream, std::ostream;
using std::move;

/**
 * @brief Represents a request with IP information and duration.
 */
class Request {
private:
	/**
	 * @brief The incomming IP address.
	 */
	string ipIn;

	/**
	 * @brief The outgoing IP address.
	 */
	string ipOut;

	/**
	 * @brief The duration of the request in seconds
	 */
	size_t duration;
public:
	/**
	 * @brief Default constructor for Request.
	 */
	Request() : ipIn{string{}}, ipOut{string{}}, duration{0} {}

	/**
	 * @brief Parameterized constructor for Request.
	 * @param ipIn The incoming IP address.
	 * @param ipOut The outgoing IP address.
	 * @param duration The duration of the request in seconds.
	 */
	Request(const string& ipIn, const string& ipOut, size_t duration) : ipIn{ipIn}, ipOut{ipOut}, duration{duration} {}

	/**
	 * @brief Copy constructor for Request.
	 * @param other The Request object to copy.
	 */
	Request(const Request& other) : ipIn{other.ipIn}, ipOut{other.ipOut}, duration{other.duration} {}

	/**
	 * @brief Move constructor for Request.
	 * @param other The Request object to move.
	 */
	Request(Request&& other) : ipIn{move(other.ipIn)}, ipOut{move(other.ipOut)}, duration{other.duration} {
		other.duration = 0;
	}

	/**
	 * @brief Destructor for Request.
	 */
	~Request() = default;

	/**
	 * @brief Copy assignment operator for Request.
	 * @param other The Request object to copy.
	 * @return A reference to the current Request object.
	 */
	Request& operator=(const Request& other) {
		if (this != &other) {
			this->ipIn = other.ipIn;
			this->ipOut = other.ipOut;
			this->duration = other.duration;
		}

		return *this;
	}

	/**
	 * @brief Move assignment operator for Request.
	 * @param other The Request object to move.
	 * @return A reference to the current Request object.
	 */
	Request& operator=(Request&& other) {
		if (this != &other) {
			this->ipIn = move(other.ipIn);
			this->ipOut = move(other.ipOut);
			this->duration = move(other.duration);
			other.duration = 0;
		}

		return *this;
	}

	/**
	 * @brief Get the duration of the request.
	 * @return A constant reference to the duration.
	 */
	const size_t& getDuration() const {
		return this->duration;
	}

	/**
	 * @brief Overload the << operator to display the Request object as a string.
	 * @param os The output stream.
	 * @param request The Request object to display.
	 * @return The output stream with the Request object representation.
	 */
	friend ostream& operator<<(ostream& os, const Request request) {
		os << "Request{ipIn=" << request.ipIn << ", ipOut=" << request.ipOut << ", duration=" << to_string(request.duration) << "}";
		return os;
	}
};

#endif // REQUEST_H
