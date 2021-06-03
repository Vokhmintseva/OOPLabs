#include <string>
#include <regex>
#include "UrlParsingError.h"

enum class Protocol
{
	HTTP,
	HTTPS
};

class HttpUrl
{
public:
	HttpUrl(std::string const& url);

	HttpUrl(std::string const& domain, std::string const& document, Protocol protocol = Protocol::HTTP);

	HttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port);

	std::string GetURL()const;

	std::string GetDomain()const;

	std::string GetDocument()const;

	Protocol GetProtocol()const;

	unsigned short GetPort()const;
private:
	unsigned short GetPort(const std::string& portStr, Protocol protocol);
	std::string ToLowLetters(const std::string& str);
	Protocol m_protocol;
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;
};