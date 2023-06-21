#pragma once
#include <yaml-cpp/yaml.h>
#include <codecvt>
#include <iostream>
#include <algorithm>
#include <locale>
#include <string>

#include "Singleton.h"

class Config : public Singleton<Config>
{
    friend class Singleton<Config>;
    Config();
    ~Config(){};

    bool m_use_join_token;

    string m_meeting_id;
    string m_display_name;
    string m_passcode;
    
    string m_sdk_key;
    string m_sdk_secret;

    string m_s2s_key;
    
    string m_s2s_secret;
    string m_s2s_account;

    wstring_convert<codecvt_utf8_utf16<wchar_t>> m_converter;

public:
    bool use_join_token() const;

    string meetingId() const;
    string displayName() const;
    string passcode() const;
    string sdkKey() const;
    string sdkSecret() const;
    string s2sKey() const;
    string s2sSecret() const;
    string s2sAccount() const;


    wstring WidenStr(string str);
};
