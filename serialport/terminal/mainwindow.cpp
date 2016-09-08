#include <QMessageBox>
#include <QLabel>
#include <QtSerialPort/QSerialPort>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    console = new Console;
    console->setEnabled(false);
    setCentralWidget(console);
    serialPort = new QSerialPort(this);
    settingDialog = new SettingDialog();

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);

    status = new QLabel;
    ui->statusBar->addWidget(status);

    initActionsConnections();

    connect(serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);
    connect(serialPort,  &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(console, &Console::getData,       this, &MainWindow::writeData);
}

MainWindow::~MainWindow()
{
    delete settingDialog;
    delete ui;
}

void MainWindow::openSerialPort()
{
    SettingDialog::Setting setting = settingDialog->getSetting();
    serialPort->setPortName(setting.name);
    serialPort->setBaudRate(setting.baudRate);
    serialPort->setDataBits(setting.dataBits);
    serialPort->setParity(setting.parity);
    serialPort->setStopBits(setting.stopBits);
    serialPort->setFlowControl(setting.flowControl);
    if (serialPort->open(QIODevice::ReadWrite)) {
        console->setEnabled(true);
        console->setLocalEchoEnabled(setting.localEchoEnabled);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfigure->setEnabled(false);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                .arg(setting.name).arg(setting.stringBaudRate).arg(setting.stringDataBits)
                .arg(setting.stringParity).arg(setting.stringStopBits).arg(setting.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serialPort->errorString());

        showStatusMessage(tr("Open error"));
    }
}

void MainWindow::closeSerialPort()
{
    if (serialPort->isOpen()) {
        serialPort->close();
    }
    console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    showStatusMessage(tr("Disconnectd"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
            tr("The <b>Simple Terminal</b> example demonstrates how to "
               "use the Qt Serial Port module in modern GUI applications "
               "using Qt, with a menu bar, toolbars, and a status bar."));
}

void MainWindow::writeData(const QByteArray &data)
{
    serialPort->write(data);
}

void MainWindow::readData()
{
    QByteArray data = serialPort->readAll();
    console->putData(data);
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serialPort->errorString());
        closeSerialPort();
    }
}

void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionConfigure, &QAction::triggered, settingDialog, &MainWindow::show);
    connect(ui->actionClear, &QAction::triggered, console, &Console::clear);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}
