#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QSslSocket>
#include <QAbstractSocket>
#include <QSslCertificate>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum State {Idle, Connected, Connecting};
    QLineEdit *hostField;
    QPushButton *connectButton;
    QTextEdit *output;
    QSslSocket *socket;
    State state;
    QSslCertificate certificate;

    void changeState(State newState);
    void loadCACertificate();
private slots:
    void buttonPressed();
    void connected();
    void disconnected();
    void encrypted();
    void readyToRead();
    void error(QAbstractSocket::SocketError err);
    void sslErrors(const QList<QSslError> &errors);
public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
};

#endif // MAINWINDOW_H
