#include "stdafx.h"
#include "Config.h"



Config::Config()
{
	YAML::Node config = YAML::LoadFile("config.yaml");
	YAML::Node credentials = YAML::LoadFile("credentials.yaml");

	YAML::Node sdk = credentials["sdk"];
	m_sdk_key = sdk["key"].as<std::string>();
	m_sdk_secret = sdk["secret"].as<std::string>();

	YAML::Node s2s = credentials["s2s"];
	m_s2s_key = s2s["key"].as<std::string>();
	m_s2s_secret = s2s["secret"].as<std::string>();
	m_s2s_account = s2s["account"].as<std::string>();


	YAML::Node meeting = config["meeting"];

	m_meeting_id = meeting["id"].as<std::string>();
	m_meeting_id.erase(remove_if(m_meeting_id.begin(), m_meeting_id.end(), isspace), m_meeting_id.end());

	m_display_name = meeting["display_name"].as<std::string>();
	m_passcode = meeting["passcode"].as<std::string>();

	m_use_join_token = meeting["join_token"].as<bool>();

	cout << "Meeting ID: " << m_meeting_id << endl;
	cout << "Display Name: " << m_display_name << endl;
	cout << "Using Join Token: " << boolalpha << m_use_join_token << endl;

	cout << endl;
}

wstring Config::WidenStr(string str)
{
	return m_converter.from_bytes(str);
}

bool Config::use_join_token() const { return m_use_join_token; }
string Config::s2sKey() const { return m_s2s_key; }
string Config::s2sSecret() const { return m_s2s_secret; }
string Config::s2sAccount() const { return m_s2s_account; }
string Config::meetingId() const { return m_meeting_id; }
string Config::displayName() const { return m_display_name;}
string Config::passcode() const { return m_passcode; }
string Config::sdkKey() const { return m_sdk_key; }
string Config::sdkSecret() const { return m_sdk_secret; }