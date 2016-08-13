#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QtSerialPort/QSerialPortInfo>

#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , transactionCount(0)
    , serialPortLabel(new QLabel(tr("Serial Port:")))
    , serialPortComboBox(new QComboBox())
    , waitRequestLabel(new QLabel(tr("Wait rquest, msec:")))
    , waitRequestSpinBox(new QSpinBox())
    , responseLabel(new QLabel(tr("Response:")))
    , responseLineEdit(new QLineEdit(tr("Hello, I'm Slave.")))
    , trafficLabel(new QLabel(tr("No traffic.")))
    , statusLabel(new QLabel(tr("Status: Not running.")))
    , runButton(new QPushButton(tr("Start")))
{
    waitRequestSpinBox->setRange(0, 10000);
    waitRequestSpinBox->setValue(10000);
    
    const QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    for (QList<QSerialPortInfo>::const_iterator info = infos.begin(); info != infos.end(); info++) {
        serialPortComboBox->addItem(info->portName());
    }
    
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(serialPortLabel, 0, 0);
    mainLayout->addWidget(serialPortComboBox, 0, 1);
    mainLayout->addWidget(waitRequestLabel, 1, 0);
    mainLayout->addWidget(waitRequestSpinBox, 1, 1);
    mainLayout->addWidget(runButton, 0, 2, 2, 1);
    mainLayout->addWidget(responseLabel, 2, 0);
    mainLayout->addWidget(responseLineEdit, 2, 1, 1, 3);
    mainLayout->addWidget(trafficLabel, 3, 0, 1, 4);
    mainLayout->addWidget(statusLabel, 4, 0, 1, 5);
    setLayout(mainLayout);
    
    setWindowTitle(tr("Blocking Slave"));
    serialPortComboBox->setFocus();
    
    connect(runButton, &QPushButton::clicked, this, &Dialog::startSlave);
    connect(&thread, &SlaveThread::request, this,  &Dialog::showRequest);
    connect(&thread, &SlaveThread::error, this, &Dialog::processError);
    connect(&thread, &SlaveThread::timeout, this, &Dialog::processTimeout);
    
    connect(serialPortComboBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), this, &Dialog::activateRunButton);
    connect(waitRequestSpinBox, static_cast<void (QSpinBox::*)(const QString &)>(&QSpinBox::valueChanged), this, &Dialog::activateRunButton);
    connect(responseLineEdit, &QLineEdit::textChanged, this, &Dialog::activateRunButton);
}

Dialog::~Dialog()
{
}

void Dialog::startSlave()
{
    runButton->setEnabled(false);
    statusLabel->setText(tr("Status: Running, connected to port %1.")
                         .arg(serialPortComboBox->currentText()));
    thread.startSlave(serialPortComboBox->currentText(),
                      waitRequestSpinBox->value(),
                      responseLineEdit->text());
}

void Dialog::showRequest(const QString &s)
{
    trafficLabel->setText(tr("Traffic, transaction #%1:"
                             "\n\r-request: %2"
                             "\n\r-response: %3")
                          .arg(++transactionCount).arg(s).arg(responseLineEdit->text()));
}

void Dialog::processError(const QString &s)
{
    activateRunButton();
    statusLabel->setText(tr("Status: Not running, %1.").arg(s));
    trafficLabel->setText(tr("No traffic."));
}

void Dialog::processTimeout(const QString &s)
{
    statusLabel->setText(tr("Status: Running, %1.").arg(s));
    trafficLabel->setText(tr("No traffic."));
}

void Dialog::activateRunButton()
{
    runButton->setEnabled(true);
}
