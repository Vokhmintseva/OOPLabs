#include "HttpUrl.h"
#include <iostream>

const std::regex urlRe("^(https|http):\\/\\/(?:www\\.)?([-a-zA-Z\\d@%._\\+~#=]{2,256}|(?:[0-9]{1,3}[\\.]){3}[0-9]{1,3})(?::(\\d{1,5}))?(\\/[-a-zA-Z0-9@:%_\\+.~#?&\\=\\/]*)?$", std::regex::icase);
const std::regex domainRe("^[-a-zA-Z\\d@:%._\\+~#=]{2,256}\\.[a-zA-Z]{2,6}$", std::regex::icase);
const std::regex documentRe("^[-a-zA-Z0-9@:%_\\+.~#?&\\=\\/]+$", std::regex::icase);

HttpUrl::HttpUrl(std::string const& url)
{
	std::smatch matches;
	if (std::regex_match(url, matches, urlRe))
	{
		m_protocol = matches[1].str() == "http" ? Protocol::HTTP : Protocol::HTTPS;
		std::string domain = matches[2].str();
		std::string document = matches[4].str();
		m_domain = ToLowLetters(domain);
		m_port = GetPort(matches[3].str(), m_protocol);
		m_document = document.empty() ? "/" : ToLowLetters(document);
	}
	else
	{
		throw UrlParsingError("invalid url");
	}
}

HttpUrl::HttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: m_protocol(protocol)
{
	if (std::regex_match(domain, domainRe) && std::regex_match(document, documentRe))
	{
		m_domain = ToLowLetters(domain);
		m_document = ToLowLetters(document);
		m_port = m_protocol == Protocol::HTTPS ? 443 : 80;
		if (m_document[0] != '/')
		{
			m_document.insert(0, std::string("/"));
		}
	}
	else
	{
		throw std::invalid_argument("invalid url parameters");
	}
}

HttpUrl::HttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_protocol(protocol)
{
	if (port == 0)
	{
		throw std::invalid_argument("invalid url parameters");
	}
	m_port = port;
	if (std::regex_match(domain, domainRe) && std::regex_match(document, documentRe))
	{
		m_domain = ToLowLetters(domain);
		m_document = ToLowLetters(document);
		if (m_document[0] != '/')
		{
			m_document.insert(0, std::string("/"));
		}
	}
	else
	{
		throw std::invalid_argument("invalid url parameters");
	}
}

unsigned short HttpUrl::GetPort(const std::string& portStr, Protocol protocol)
{
	if (portStr.empty())
	{
		return protocol == Protocol::HTTP ? 80 : 443;
	}
	unsigned int port = std::stoi(portStr);
	if (port == 0 || port > 65535)
	{
		throw UrlParsingError("invalid port value");
	}
	return port;
}

std::string HttpUrl::ToLowLetters(const std::string& str)
{
	std::string strInLowLetters = str;
	std::transform(strInLowLetters.begin(), strInLowLetters.end(), strInLowLetters.begin(), tolower);
	return strInLowLetters;
}

std::string HttpUrl::GetURL()const
{
	std::string port = (m_port == 443 && m_protocol == Protocol::HTTPS || m_port == 80 && m_protocol == Protocol::HTTP) ? "" : (':' + std::to_string(m_port));
	std::string protocol = m_protocol == Protocol::HTTPS ? "https://" : "http://";
	std::string document = m_document;
	if (document == "/")
	{
		document = "";
	}
	return protocol + m_domain + port + document;
}

std::string HttpUrl::GetDomain()const
{
	return m_domain;
}

std::string HttpUrl::GetDocument()const
{
	return m_document;
}

Protocol HttpUrl::GetProtocol()const
{
	return m_protocol;
}

unsigned short HttpUrl::GetPort()const
{
	return m_port;
}