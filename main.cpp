#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QSslSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!QSslSocket::supportsSsl())
    {
        QMessageBox msgBox(QMessageBox::Critical,
                           "OpenSSL error",
                           "OpenSSL library old or not present.");
        msgBox.exec();
        return -1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
