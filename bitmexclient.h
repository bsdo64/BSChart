#ifndef BITMEXCLIENT_H
#define BITMEXCLIENT_H

#include <QtCore>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <string>
using std::string;

class BitmexClient : public QObject
{
    Q_OBJECT

public:
    BitmexClient(
            string base_url, string symbol, string api_key,
            string api_secret, string order_id_prefix, bool should_ws_auth,
            bool post_only, int timeout);
    BitmexClient(
            string base_url, string symbol, string api_key,
            string api_secret);
    ~BitmexClient();

public slots:
    void replyFinished(QNetworkReply* reply);
    void slotReadyRead();

private:
    string base_url;
    string symbol;
    string api_key;
    string api_secret;
    string order_id_prefix = "mm_bitmex_";
    bool should_ws_auth = true;
    bool post_only = false;
    int timeout = 7;
    int retries = 0;

    QNetworkRequest request;
};

#endif // BITMEXCLIENT_H
