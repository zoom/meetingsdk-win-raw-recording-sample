#pragma once
#include <yaml-cpp/yaml.h>
#include <boost/url/url_view.hpp>
#include <boost/algorithm/string.hpp>
#include <codecvt>
#include <iostream>
#include <algorithm>
#include <locale>
#include <string>
using namespace boost::urls;


#include "Singleton.h"

class Config : public Singleton<Config>
{
    friend class Singleton<Config>;
    Config();
    ~Config(){};

    bool m_use_join_token;

    string m_meeting_id;
    string m_display_name;
    string m_password;
    string m_join_url;
    string m_join_token;
    
    string m_sdk_key;
    string m_sdk_secret;

    string m_s2s_key;
    
    string m_s2s_secret;
    string m_s2s_account;

    wstring_convert<codecvt_utf8_utf16<wchar_t>> m_converter;

public:
    bool parseJoinUrl(string const& url);
    bool useJoinToken() const;

    string joinToken() const;
    void joinToken(string const& token);
    
    string meetingId() const;
    string displayName() const;
    string password() const;
    string sdkKey() const;
    string sdkSecret() const;
    string s2sKey() const;
    string s2sSecret() const;
    string s2sAccount() const;


    wstring widenStr(string str);
};
