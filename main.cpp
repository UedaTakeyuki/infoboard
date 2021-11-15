#include "mainwindow.h"

#include <QApplication>

#include <QtCore/QSocketNotifier>
#include <QtCore/QTextStream>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // https://qt5.jp/2015/08/qt-stdin/
    QTextStream qstdin(stdin);
    QSocketNotifier notifier(fileno(stdin), QSocketNotifier::Read);
    QObject::connect(&notifier, &QSocketNotifier::activated, [&]() {
        while(!qstdin.atEnd()) {
            QString line = qstdin.readLine();
            if (line.isEmpty()) {
//                app.quit();
                qDebug() << line;
                w.updateLabelText(line);

//                break;
            } else {
                qDebug() << line;
                w.updateLabelText(line);
            }
        }
        qDebug() << "loop finished!";
    });

    return a.exec();
}
