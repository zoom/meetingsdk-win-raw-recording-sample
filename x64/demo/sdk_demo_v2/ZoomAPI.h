#pragma once
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/property_tree/ptree_fwd.hpp>

#include "Config.h"

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
namespace ssl = net::ssl;       // from <boost/asio/ssl.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class ZoomApi
{
	const string m_token_uri = "/oauth/token";
	string m_host = "api.zoom.us";
	string m_access_token;
public:
	ZoomApi();
	bool authorize();
	std::string encode64(const std::string& v) const;
	boost::property_tree::ptree parseJson(const http::response<http::dynamic_body>& json) const;
	http::response<http::dynamic_body> request(http::verb const& method, string const& endpoint, string const& authorization= "", string const& body= "", string const& content_type = "application/json", bool const& is_token_request = false) const;

	string accessToken() const;


};
