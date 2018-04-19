#ifndef BITMEXAUTH_H
#define BITMEXAUTH_H

#include <string>
using std::string;

class BitmexAuth
{
public:
    BitmexAuth();
    string sign(string key, string plain);
};

#endif // BITMEXAUTH_H
