#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "steamwebrequest.h"
#include "steamjson.h"
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , manager(new QNetworkAccessManager)
    , chart(new QChart)
    , chartView(new QChartView)
{
    ui->setupUi(this);
    QUrl url = * new QUrl("https://api.steampowered.com/IPlayerService/GetRecentlyPlayedGames/v0001/?key=A5978F3811ECCDF3FCE90D78F81B1779&steamid=76561198037712778&format=json");
    sendWebRequest(url);


}

MainWindow::~MainWindow()
{
    delete ui;
}

// emits webResponseReceived
void MainWindow::sendWebRequest(QUrl url)
{
    QNetworkRequest request(url);
    // Perform the GET request
    QNetworkReply *reply = manager.get(request);

    // Connect the finished signal to the handleNetworkReply slot
    connect(reply, &QNetworkReply::finished, this, &MainWindow::handleResponse);
}

void MainWindow::handleResponse()
{
    ///
    /// make sure response was okay
    ///
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QByteArray response;
    if (reply)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            // Success: read the data
            response = reply->readAll();
        } else {
            // Error: display the error message
            qDebug() << "Error:" << reply->errorString();
        }

        // Cleanup
        reply->deleteLater();
    }

    ///
    /// parse json
    ///
    QList<SteamGameTime> listOfGameTimes = SteamJson::tryParseJson(response);

    ///
    /// call update chart with game data
    ///
    updateChart(listOfGameTimes);
}



void MainWindow::updateChart(QList<SteamGameTime> listOfSGT)
{
    QList<QBarSet*> *barSets = new QList<QBarSet*>();
    for(auto i=0; i<listOfSGT.size(); i++)
    {
        SteamGameTime game = listOfSGT[i];
        QBarSet *barSet = new QBarSet(game.steamGame.name);
        *barSet << game.playtime2Weeks / 60;
        barSets->append(barSet);
    }

    QBarSeries *series = new QBarSeries;
    series->append(*barSets);

    // Add the series to the chart
    chart.addSeries(series);

    // Set chart title and other properties
    chart.setTitle("Time Played on Steam");
    chart.setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories {"Now"};
    auto axisX = new QBarCategoryAxis;
    axisX->append(categories);
    chart.addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto axisY = new QValueAxis;
    chart.addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart.legend()->setVisible(true);
    chart.legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(&chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set the QChartView to the placeholder widget
    ui->chartWidget->setLayout(new QVBoxLayout());
    ui->chartWidget->layout()->addWidget(chartView);
}
