#include "bitmexclient.h"
#include <QNetworkAccessManager>
#include <QByteArray>
#include <QUrl>
#include <iostream>

BitmexClient::BitmexClient(
        string base_url, string symbol, string api_key,
        string api_secret, string order_id_prefix = "mm_bitmex_",
        bool should_ws_auth = true, bool post_only = false, int timeout = 7
    )
    : base_url(base_url),
      symbol(symbol),
      api_key(api_key),
      api_secret(api_secret),
      order_id_prefix(order_id_prefix),
      should_ws_auth(should_ws_auth),
      post_only(post_only),
      timeout(timeout)
{
    if (api_key.empty())
    {
        std::cerr << "Please set an API key and Secret to get started. See "
                     "https://github.com/BitMEX/sample-market-maker/#getting-started for more information."
        << std::endl;
    };

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    request.setUrl(QUrl("https://www.qt.io"));
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
    request.setRawHeader("user-agent", "liquidbot-1");
    request.setRawHeader("content-type", "application/json");
    request.setRawHeader("accept", "application/json");

    QNetworkReply *reply = manager->get(request);
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(slotReadyRead()));
//    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
//            this, SLOT(slotError(QNetworkReply::NetworkError)));
//    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
//            this, SLOT(slotSslErrors(QList<QSslError>)));

}

void BitmexClient::replyFinished(QNetworkReply* r)
{
    QByteArray array = r->readAll();
}


void BitmexClient::slotReadyRead() {
    std::cout << "read to read" << std::endl;
}
