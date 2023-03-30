#include "mainwindow.h"
#include "display.h"
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
            ui->label->setText(line);
        }
    });
    timer->start(500);

    // https://stackoverflow.com/questions/24239822/how-to-remove-space-margin-that-between-qmainwindow-and-mdiarea/24240025
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
    restoreSettings();

    // http://pido.seesaa.net/article/183717126.html
/*    QSettings settings("setting.ini", QSettings::IniFormat);
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());*/
}

MainWindow::~MainWindow()
{
    // http://pido.seesaa.net/article/183717126.html
/*    QSettings setting("setting.ini", QSettings::IniFormat);
    setting.setValue("geometry", saveGeometry());
    setting.setValue("windowState", saveState());*/
    saveSettings();
    delete ui;
}

/*
void MainWindow::updateLabelText(QString &text){
    ui->label->setText(text);
    ui->label->repaint(); // https://stackoverflow.com/a/57571837/11073131
}
*/

void MainWindow::saveSettings()
{
    // http://pido.seesaa.net/article/183717126.html
    QSettings setting("setting.ini", QSettings::IniFormat);
    setting.setValue("geometry", saveGeometry());
    setting.setValue("windowState", saveState());
}

void MainWindow::restoreSettings()
{
    // http://pido.seesaa.net/article/183717126.html
    QSettings settings("setting.ini", QSettings::IniFormat);

    // resotre geometory or set default
    const auto geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty())
        setDefaultGeometory();
    else
        restoreGeometry(geometry);

    // restore windowState
    const auto windowState = settings.value("windowState", QByteArray()).toByteArray();
    if (!windowState.isEmpty())
        restoreState(windowState);
}

void MainWindow::setDefaultGeometory(){
    Display *display = new Display;

    // set default geometory
    int screenWidth = display->getWidth();
    int screenHeight = display->getHeight();
    int height = screenHeight/10;
    int width = (screenWidth * 5)/6;
    int x=0, y=0;
//    x=screenWidth - width;
    y=screenHeight - height;

/*
    if (screenWidth >= 1800 && screenHeight >= 1080){
      x=screenWidth - width*1.1;
      y=screenHeight - height*1.7;
    } else {
      // screenWidth = 720, screenHeight = 480
      x=screenWidth - width*1.7;
      y=screenHeight - height*2.2;
    }
*/
    qDebug() << "screenWidth: " << screenWidth;
    qDebug() << "screenHeight: " << screenHeight;
    qDebug() << "height: " << height;
    qDebug() << "width: " << width;
    qDebug() << "x: " << x;
    qDebug() << "y: " << y;
    setGeometry(x,y,width,height);
}
