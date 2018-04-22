#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "bitmexclient.h"

#include <armadillo>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>

namespace ba = boost::accumulators;
namespace bt = ba::tag;
typedef ba::accumulator_set < uint32_t, ba::stats <bt::rolling_mean, bt::rolling_sum > > MeanAccumulator;

int main(int argc, char *argv[])
{

    // boost
    MeanAccumulator acc(bt::rolling_window::window_size = 5u);

    for (uint32_t i : { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }) {
        acc(i);
        qDebug() << i << " actualMean: " << ba::rolling_mean(acc);
    }

    qDebug() << "After : " << ba::rolling_mean(acc);
    qDebug() << "After : " << ba::rolling_mean(acc);
    qDebug() << "After : " << ba::rolling_mean(acc);
    qDebug() << "After : " << ba::rolling_sum(acc);

    // arma
    arma::running_stat_vec<arma::vec> stats;

    arma::vec sample;

    for(arma::uword i=0; i<10000; ++i)
    {
        sample = arma::linspace(1, 5000, 5000) + i;
        stats(sample);
    }

    std::cout << "mean = " << stats.mean();
    std::cout << "var  = " << stats.var();
    std::cout << "max  = " << stats.max();


    // Qt
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc,argv);

    BitmexClient client("a", "b", "c", "d");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
