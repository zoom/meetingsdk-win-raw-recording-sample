#include "stdafx.h"
#include "ZoomAPI.h"

#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/beast/version.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <iostream>


ZoomApi::ZoomApi()
{ }

bool ZoomApi::authorize()
try {
	const Config* config = &Config::getInstance();

	stringstream body;
	body << "grant_type=account_credentials";
	body << "&account_id=" << config->s2sAccount();

	const auto authorization = encode64(config->s2sKey() + ":" + config->s2sSecret());

	auto res = request(
		http::verb::post,
		m_token_uri,
		authorization,
		body.str(),
		"application/x-www-form-urlencoded",
		true
	);
	
	const auto pt = parseJson(res);
	auto access_token = pt.get<std::string>("access_token");

	m_access_token = access_token;
	
	return true;
} catch(std::exception const& e)
{
	std::cerr << "GetAccessToken Error: " << e.what() << std::endl;
	return false;
}

http::response<http::dynamic_body> ZoomApi::request(http::verb const& method, string const& endpoint, string const& authorization, string const& body, string const& content_type, bool const& is_token_request) const try
{
	const auto host = is_token_request ? "zoom.us" : m_host;
	const auto auth = is_token_request ? "Basic " + authorization : "Bearer " + m_access_token;
	const auto endp = is_token_request ?  endpoint : "/v2" + endpoint;
	
	net::io_context ioc;

	ssl::context ctx(ssl::context::tlsv13_client);
	ctx.set_default_verify_paths();
	ctx.set_options(ssl::context::default_workarounds |
						 ssl::context::verify_peer);
	
	tcp::resolver resolver(ioc);
	beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

	// Set SNI Hostname (many hosts need this to handshake successfully)
	if(!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str()))
	{
		beast::error_code ec{static_cast<int>(::ERR_get_error()),net::error::get_ssl_category()};
		throw beast::system_error{ec};
	}

	auto const results = resolver.resolve(host, "443");
	beast::get_lowest_layer(stream).connect(results);
	stream.handshake(ssl::stream_base::client);

	http::request<http::string_body> req{method,endp,11};
	req.set(http::field::host, m_host);
	req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
	req.set(http::field::content_type, content_type);
	req.set(http::field::authorization, auth);
	
	if (method != http::verb::get && !body.empty())
	{
		req.body() = body;
		req.prepare_payload();
	}

	cout << "Request: " << endl <<  req << endl;

	http::write(stream, req);

	beast::flat_buffer buffer;
	http::response<http::dynamic_body> res;

	http::read(stream, buffer, res);

	cout << "Response: " << endl <<  res << endl;

	return res;
}
catch(std::exception const& e)
{
	std::cerr << "Request Error: " << e.what() << std::endl;
	return http::response<http::dynamic_body>();
}

std::string ZoomApi::encode64(const std::string& v) const
{
	using namespace boost::archive::iterators;
	using it = base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>;
	auto tmp = std::string(it(std::begin(v)), it(std::end(v)));
	return tmp.append((3 - v.size() % 3) % 3, '=');
}
boost::property_tree::ptree ZoomApi::parseJson(const http::response<http::dynamic_body>& json) const
{
	stringstream ss;
	ss << beast::make_printable(json.body().data());
	boost::property_tree::ptree pt;
	read_json(ss, pt);

	return pt;
}

string ZoomApi::accessToken() const { return m_access_token; }