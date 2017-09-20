#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHostAddress>
#include <QMessageBox>
#include <QGroupBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    hostField(new QLineEdit(this)),
    connectButton(new QPushButton("Connect", this)),
    output(new QTextEdit())
{
    this->setWindowTitle("SSL Client");
    QGroupBox *groupBox = new QGroupBox("Secure Socket Layer");
    QVBoxLayout *layout = new QVBoxLayout();
    groupBox->setLayout(layout);
    layout->addWidget(new QLabel("Host:"));
    layout->addWidget(hostField);
    layout->addWidget(connectButton);
    layout->addWidget(new QLabel("Output:"));
    layout->addWidget(output);
    output->setReadOnly(true);
    this->setCentralWidget(groupBox);

    // Conexiones
    QObject::connect(connectButton, &QPushButton::clicked,
                     this, &MainWindow::buttonPressed);
    changeState(Idle);
}

void MainWindow::buttonPressed()
{
    changeState(Connecting);
}

void MainWindow::changeState(State newState)
{
    state = newState;
    switch(state)
    {
    case Idle:
        hostField->setEnabled(true);
        connectButton->setEnabled(true);
        output->setEnabled(false);
        break;
    case Connecting:
        hostField->setEnabled(false);
        connectButton->setEnabled(false);
        output->setEnabled(false);
        break;
    case Connected:
        hostField->setEnabled(false);
        connectButton->setEnabled(false);
        output->setEnabled(true);
        break;
    }
}

void MainWindow::connected()
{
    changeState(Connected);
    output->insertPlainText("Connected.\n");
}

void MainWindow::disconnected()
{
    changeState(Idle);
    output->insertPlainText("Disconnected.\n");
}

void MainWindow::encrypted()
{
    output->insertPlainText("Encrypted.\n");
}

void MainWindow::sslError()
{
}

void MainWindow::readyToRead()
{
    QByteArray array(socket->readAll());
    output->insertPlainText(QString::fromLatin1(array));
}

MainWindow::~MainWindow()
{
}
