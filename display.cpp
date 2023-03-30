#include "display.h"
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <QFile>

Display::Display()
{
    QFile file( "/sys/class/graphics/fb0/virtual_size" );

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "can not open file." ;
        return;
    }
    QTextStream in(&file);
    QString inStr = in.readAll();
    file.close();
    QStringList l = inStr.trimmed().split(",");

    QString w = l[0];
    QString h = l[1];


/*
    // https://stackoverflow.com/a/17344946/11073131
    QProcess pingProcess;
    QString exec = "tvservice";
    QStringList params;
    params << "-s";
    pingProcess.start(exec, params);
    pingProcess.waitForFinished(); // sets current thread to sleep and waits for pingProcess end
    QString tvservice(pingProcess.readAllStandardOutput());

    QString reso = tvservice.split(",")[1];
    QRegExp r(" ([0-9]+)x([0-9]+) ");
    r.exactMatch(reso);
    QStringList l = r.capturedTexts();


    QString w = l[1];
    QString h = l[2];
*/
/*
    QMessageBox Msgbox;
    Msgbox.setText(w);
    Msgbox.exec();
    Msgbox.setText(h);
    Msgbox.exec();
*/
    bool is_ok;
    width = w.toInt(&is_ok, 10);
    height = h.toInt(&is_ok, 10);

    qDebug() << width << ":" << height;
}

Display::~Display()
{
}
