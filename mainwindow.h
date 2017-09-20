#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QSslSocket>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum State {Idle, Connected, Connecting};
    QLineEdit *hostField;
    QPushButton *connectButton;
    QTextEdit *output;
    QSslSocket *socket;
    State state;

    void changeState(State newState);
private slots:
    void buttonPressed();
    void connected();
    void disconnected();
    void encrypted();
    void readyToRead();
    void sslError();
public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
};

#endif // MAINWINDOW_H
