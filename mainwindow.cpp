#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
// #include <QTimer>
#include <QDateTime>
#include <QSettings>

#include <QtCore/QSocketNotifier>
#include <QtCore/QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){
        QDateTime dt = QDateTime::currentDateTime();
        ui->label->setText(dt.toString("hh:mm:ss"));});
    timer->start(50);
    */

    // https://qt5.jp/2015/08/qt-stdin/
    QTextStream qstdin(stdin);
    ui->label->setText(qstdin.readLine());
    QSocketNotifier notifier(fileno(stdin), QSocketNotifier::Read);
    QObject::connect(&notifier, &QSocketNotifier::activated, [&]() {
        while(!qstdin.atEnd()) {
            QString line = qstdin.readLine();
            if (line.isEmpty()) {
//                app.quit();
                qDebug() << line;
//                break;
            } else {
                qDebug() << line;
                ui->label->setText(line);
            }
        }
    });

    // https://stackoverflow.com/questions/24239822/how-to-remove-space-margin-that-between-qmainwindow-and-mdiarea/24240025
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
    statusBar()->hide();

    // http://pido.seesaa.net/article/183717126.html
    QSettings settings("setting.ini", QSettings::IniFormat);
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());


}

MainWindow::~MainWindow()
{
    // http://pido.seesaa.net/article/183717126.html
    QSettings setting("setting.ini", QSettings::IniFormat);
    setting.setValue("geometry", saveGeometry());
    setting.setValue("windowState", saveState());

    delete ui;
}
