#include "stdafx.h"
#include "ZoomAuthenticator.h"


LPCTSTR ZoomAuthenticator::getJwt()
{
    Config* config = &Config::getInstance();
    
    const auto sdk_key = config->sdkKey();
    const auto sdk_secret = config->sdkSecret();

    const auto iat = std::chrono::system_clock::now();
    const auto exp = iat + std::chrono::hours{ 24 };
    
    const auto token = jwt::create()
    .set_type("JWT")
    .set_issued_at(iat)
    .set_expires_at(exp)
    .set_payload_claim("appKey",claim(sdk_key))
    .set_payload_claim("tokenExp", claim(exp))
    .sign(algorithm::hs256{sdk_secret});
    
    return config->WidenStr(token).c_str();
}
