#include "bitmexauth.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include "cryptlib.h"
using CryptoPP::Exception;

#include "hmac.h"
using CryptoPP::HMAC;

#include "sha.h"
using CryptoPP::SHA256;

#include "hex.h"
using CryptoPP::HexEncoder;

#include "filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::HashFilter;

BitmexAuth::BitmexAuth()
{

}

string BitmexAuth::sign(string key, string plain)
{
    string mac, encoded;
    bool uppercase = false;
    try
    {
        HMAC< SHA256 > hmac((unsigned char*)key.c_str(), key.length());

        StringSource(plain, true,
            new HashFilter(hmac,
                new StringSink(mac)
            ) // HashFilter
        ); // StringSource
    }
    catch(const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
    }

    encoded.clear();
    StringSource(mac, true,
        new HexEncoder(
            new StringSink(encoded),
            uppercase
        ) // Base64Encoder
    ); // StringSource

    return encoded;
}
