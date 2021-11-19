#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QSettings>
#include <QString>


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

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){
        QTextStream qstdin(stdin);
        QString line = qstdin.readLine();
            if (!line.isEmpty()){
            ui->label->setText(line);}});
    timer->start(500);

    // https://stackoverflow.com/questions/24239822/how-to-remove-space-margin-that-between-qmainwindow-and-mdiarea/24240025
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);

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

/*
void MainWindow::updateLabelText(QString &text){
    ui->label->setText(text);
    ui->label->repaint(); // https://stackoverflow.com/a/57571837/11073131
}
*/
