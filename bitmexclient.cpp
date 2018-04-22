#include "bitmexclient.h"
#include "bitmexauth.h"
#include <QNetworkAccessManager>
#include <QByteArray>
#include <QUrl>
#include <QDateTime>
#include <iostream>
#include <QJsonDocument>

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

    request.setUrl(QUrl("https://www.bitmex.com/api/v1/instrument"));
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
    request.setRawHeader("user-agent", "liquidbot-1");
    request.setRawHeader("content-type", "application/json");
    request.setRawHeader("accept", "application/json");
    qint64 expires = QDateTime::currentSecsSinceEpoch() + 5;
    QByteArray s_expires = QByteArray::number(expires);
    request.setRawHeader("api-expires", s_expires);
    request.setRawHeader("api-key", "hImUSySfSitmsaSrYv4IKecu");

    QByteArray data = "GET/api/v1/instrument"+s_expires;
    BitmexAuth auth;
    string sign = auth.sign(
                "0LC7T3jzS9M9Dk0Ce1sbUmKmg5rZ_sd352gYeLtCUtu6apzb",
                data.toStdString());

    request.setRawHeader("api-signature",
                         QByteArray::fromStdString(sign));


    QNetworkReply *reply = manager->get(request);
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(slotReadyRead()));

    manager->get(request);

//    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
//            this, SLOT(slotError(QNetworkReply::NetworkError)));
//    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
//            this, SLOT(slotSslErrors(QList<QSslError>)));

}

BitmexClient::BitmexClient(string base_url, string symbol, string api_key, string api_secret)
    : BitmexClient{base_url, symbol, api_key, api_secret, "mm_bitmex_", true, false, 7} { }

BitmexClient::~BitmexClient()
{

}

void BitmexClient::replyFinished(QNetworkReply* r)
{
    QByteArray array = r->readAll();
    QList<QByteArray> headerList = r->rawHeaderList();
    foreach(QByteArray head, headerList) {
        qDebug() << head << ":" << r->rawHeader(head);
    }

    QJsonDocument doc = QJsonDocument::fromJson(array);

//    if(doc.isNull()){
//        qDebug()<<"Failed to create JSON doc.";

//    }
//    if(!doc.isObject()){
//        qDebug()<<"JSON is not an object.";

//    }

//    if(!doc.isArray()){
//        qDebug() << "JSON doc is not an array.";
//    }

//    QJsonArray json_array = doc.array();

//    for(int i=0; i< json_array.count(); ++i){
//        qDebug() << json_array.at(i).toString();
//    }
}


void BitmexClient::slotReadyRead() {
//    std::cout << "read to read" << std::endl;
}

