#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#endif

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QtCharts>
#include "steamgametime.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void webResponseReceived();

public slots:
    void handleResponse();
    void sendWebRequest(QUrl url);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
    QChart chart;
    QChartView *chartView;

    void updateChart(QList<SteamGameTime>);
};
