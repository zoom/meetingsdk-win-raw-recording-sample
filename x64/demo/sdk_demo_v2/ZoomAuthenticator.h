#pragma once

#undef min
#undef max
#include <jwt-cpp/jwt.h>

#include "Config.h"

using namespace jwt;
class ZoomAuthenticator
{
public:
    static LPCTSTR getJwt();
};
