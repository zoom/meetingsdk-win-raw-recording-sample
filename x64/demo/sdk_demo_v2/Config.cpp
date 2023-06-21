#include "stdafx.h"
#include "Config.h"

Config::Config()
{
	YAML::Node config = YAML::LoadFile("config.yaml");
	YAML::Node credentials = YAML::LoadFile("credentials.yaml");

	YAML::Node sdk = credentials["sdk"];
	m_sdk_key = sdk["key"].as<string>();
	m_sdk_secret = sdk["secret"].as<string>();

	YAML::Node s2s = credentials["s2s"];
	m_s2s_key = s2s["key"].as<string>();
	m_s2s_secret = s2s["secret"].as<string>();
	m_s2s_account = s2s["account"].as<string>();


	YAML::Node meeting = config["meeting"];

	m_meeting_id = meeting["id"].as<string>();
	m_meeting_id.erase(remove_if(m_meeting_id.begin(), m_meeting_id.end(), isspace), m_meeting_id.end());

	m_display_name = meeting["display_name"].as<string>();
	m_password = meeting["passcode"].as<string>();

	m_join_url = meeting["join_url"].as<string>();

	if(m_join_url != "null")
		parseJoinUrl(m_join_url);

	m_use_join_token = meeting["join_token"].as<bool>();
	
	cout << "Meeting ID: " << m_meeting_id << endl;
	cout << "Display Name: " << m_display_name << endl;
	cout << "Using Join Token: " << boolalpha << m_use_join_token << endl;

	cout << endl;
}

wstring Config::widenStr(string str)
{
	return m_converter.from_bytes(str);
}

bool Config::parseJoinUrl(string const& url)
{
	cout << "Parsing Join URL: " << url << endl;

	const url_view uv(url);

	if (uv.empty()) return false;

	
	for( auto v : uv.params())
	{
		if (v.key == "pwd")
		{
			m_password = v.value;
			cout << "Password: " << m_password << endl;
		}
	}
	
	std::vector<std::string> paths;
	split(paths, uv.path(), boost::is_any_of("/"));
	m_meeting_id =  paths.at(2);
	
	return true;
}

/* Setters */
void Config::joinToken(string const& token) { m_join_token = token; }

/* Getters */
bool Config::useJoinToken() const { return m_use_join_token; }
string Config::joinToken() const { return m_join_token; }
string Config::s2sKey() const { return m_s2s_key; }
string Config::s2sSecret() const { return m_s2s_secret; }
string Config::s2sAccount() const { return m_s2s_account; }
string Config::meetingId() const { return m_meeting_id; }
string Config::displayName() const { return m_display_name;}
string Config::password() const { return m_password; }
string Config::sdkKey() const { return m_sdk_key; }
string Config::sdkSecret() const { return m_sdk_secret; }