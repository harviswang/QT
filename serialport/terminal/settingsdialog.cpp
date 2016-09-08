#include <QtSerialPort/QSerialPortInfo>
#include <QIntValidator>
#include <QLineEdit>

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

QT_USE_NAMESPACE

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

SettingDialog::SettingDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    
    intValidator = new QIntValidator(0, 4000000, this);
    
    ui->baudRateBox->setInsertPolicy(QComboBox::NoInsert);
    
    connect(ui->applyButton, &QPushButton::clicked,
            this, &SettingDialog::apply);
    connect(ui->serialPortInfoListBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &SettingDialog::showPortInfo);
    connect(ui->baudRateBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &SettingDialog::checkCustomBaudRatePolicy);
    connect(ui->serialPortInfoListBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &SettingDialog::checkCustomDevicePathPolicy);

    fillSerialPortParameters();
    fillSerialPortInfo();

    updateSetting();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

SettingDialog::Setting SettingDialog::getSetting() const
{
    return currentSetting;
}

void SettingDialog::showPortInfo(int idx)
{
    if (idx == -1) {
        return ;
    }

    QStringList list = ui->serialPortInfoListBox->itemData(idx).toStringList();
    ui->descriptionLabel->setText(tr("Description: %1").arg(list.count() > 1 ? list.at(1) : tr(blankString)));
    ui->manufacturerLabel->setText(tr("Manufacturer: %1").arg(list.count() > 2 ? list.at(2) : tr(blankString)));
    ui->serialNumberLabel->setText(tr("Serial number: %1").arg(list.count() > 3 ? list.at(3) : tr(blankString)));
    ui->locationLabel->setText(tr("Location: %1").arg(list.count() > 4 ? list.at(4) : tr(blankString)));
    ui->vidLabel->setText(tr("Vendor Identifier: %1").arg(list.count() > 5 ? list.at(5) : tr(blankString)));
    ui->pidLabel->setText(tr("Productor Identifier: %1").arg(list.count() > 6 ? list.at(6) : tr(blankString)));
}

void SettingDialog::apply()
{
    updateSetting();
    hide();
}

void SettingDialog::checkCustomBaudRatePolicy(int idx)
{
    bool isCustomBaudRate = !ui->baudRateBox->itemData(idx).isValid();
    ui->baudRateBox->setEditable(isCustomBaudRate);
    if (isCustomBaudRate) {
        ui->baudRateBox->clearEditText();
        QLineEdit *edit = ui->baudRateBox->lineEdit();
        edit->setValidator(intValidator);
    }
}

void SettingDialog::checkCustomDevicePathPolicy(int idx)
{
    bool isCustomPath = !ui->serialPortInfoListBox->itemData(idx).isValid();
    ui->serialPortInfoListBox->setEditable(isCustomPath);
    if (isCustomPath) {
        ui->serialPortInfoListBox->clearEditText();
    }
}

void SettingDialog::fillSerialPortParameters()
{
    ui->baudRateBox->addItem(QStringLiteral("0"),   SettingDialog::Baudrate0);
    ui->baudRateBox->addItem(QStringLiteral("50"),   SettingDialog::Baudrate50);
    ui->baudRateBox->addItem(QStringLiteral("75"),   SettingDialog::Baudrate75);
    ui->baudRateBox->addItem(QStringLiteral("110"),   SettingDialog::Baudrate110);
    ui->baudRateBox->addItem(QStringLiteral("134"),   SettingDialog::Baudrate134);
    ui->baudRateBox->addItem(QStringLiteral("150"),   SettingDialog::Baudrate150);
    ui->baudRateBox->addItem(QStringLiteral("200"),   SettingDialog::Baudrate200);
    ui->baudRateBox->addItem(QStringLiteral("300"),   SettingDialog::Baudrate300);
    ui->baudRateBox->addItem(QStringLiteral("600"),   SettingDialog::Baudrate600);
    ui->baudRateBox->addItem(QStringLiteral("1200"),   SettingDialog::Baudrate1200);
    ui->baudRateBox->addItem(QStringLiteral("1800"),   SettingDialog::Baudrate1800);
    ui->baudRateBox->addItem(QStringLiteral("2400"),   SettingDialog::Baudrate2400);
    ui->baudRateBox->addItem(QStringLiteral("4800"),   SettingDialog::Baudrate4800);
    ui->baudRateBox->addItem(QStringLiteral("9600"),   SettingDialog::Baudrate9600);
    ui->baudRateBox->addItem(QStringLiteral("19200"),   SettingDialog::Baudrate19200);
    ui->baudRateBox->addItem(QStringLiteral("38400"),   SettingDialog::Baudrate38400);
    ui->baudRateBox->addItem(QStringLiteral("57600"),   SettingDialog::Baudrate57600);
    ui->baudRateBox->addItem(QStringLiteral("115200"),   SettingDialog::Baudrate115200);
    ui->baudRateBox->addItem(QStringLiteral("230400"),   SettingDialog::Baudrate230400);
    ui->baudRateBox->addItem(QStringLiteral("460800"),   SettingDialog::Baudrate460800);
    ui->baudRateBox->addItem(QStringLiteral("500000"),   SettingDialog::Baudrate500000);
    ui->baudRateBox->addItem(QStringLiteral("576000"),   SettingDialog::Baudrate576000);
    ui->baudRateBox->addItem(QStringLiteral("921600"),   SettingDialog::Baudrate921600);
    ui->baudRateBox->addItem(QStringLiteral("1000000"),   SettingDialog::Baudrate1000000);
    ui->baudRateBox->addItem(QStringLiteral("1152000"),   SettingDialog::Baudrate1152000);
    ui->baudRateBox->addItem(QStringLiteral("1500000"),   SettingDialog::Baudrate1500000);
    ui->baudRateBox->addItem(QStringLiteral("2000000"),   SettingDialog::Baudrate2000000);
    ui->baudRateBox->addItem(QStringLiteral("2500000"),   SettingDialog::Baudrate2500000);
    ui->baudRateBox->addItem(QStringLiteral("3000000"),   SettingDialog::Baudrate3000000);
    ui->baudRateBox->addItem(QStringLiteral("3500000"),   SettingDialog::Baudrate3500000);
    ui->baudRateBox->addItem(QStringLiteral("4000000"),   SettingDialog::Baudrate4000000);
    ui->baudRateBox->addItem(tr("Custom"));

    ui->dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->dataBitsBox->setCurrentIndex(3);

    ui->parityBox->addItem(tr("None"),  QSerialPort::NoParity);
    ui->parityBox->addItem(tr("Even"),  QSerialPort::EvenParity);
    ui->parityBox->addItem(tr("Odd"),   QSerialPort::OddParity);
    ui->parityBox->addItem(tr("Mark"),  QSerialPort::MarkParity);
    ui->parityBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    ui->stopBitsBox->addItem(QStringLiteral("1"),   QSerialPort::OneStop);
#ifdef Q_OS_WIN
    ui->stopBitsBox->addItem(QStringLiteral("1.5"), QSerialPort::OneAndHalfStop);
#endif
    ui->stopBitsBox->addItem(QStringLiteral("2"),   QSerialPort::TwoStop);

    ui->flowControlBox->addItem(tr("None"),     QSerialPort::NoFlowControl);
    ui->flowControlBox->addItem(tr("RTS/CTS"),  QSerialPort::HardwareControl);
    ui->flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

void SettingDialog::fillSerialPortInfo()
{
    ui->serialPortInfoListBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    for (QList<QSerialPortInfo>::const_iterator info = infos.begin(); info != infos.end(); info++) {
        QStringList list;
        description  = info->description();
        manufacturer = info->manufacturer();
        serialNumber = info->serialNumber();
        list << info->portName()
             << (!description.isEmpty()  ? description  : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info->systemLocation()
             << (info->vendorIdentifier() ? QString::number(info->vendorIdentifier(),  16) : blankString)
             << (info->productIdentifier()? QString::number(info->productIdentifier(), 16) : blankString);

        ui->serialPortInfoListBox->addItem(list.first(), list);
    }

    ui->serialPortInfoListBox->addItem(tr("Custom"));
}

void SettingDialog::updateSetting()
{
    currentSetting.name = ui->serialPortInfoListBox->currentText();

    if (ui->baudRateBox->currentIndex() == 4) {
        currentSetting.baudRate = ui->baudRateBox->currentText().toInt();
    } else {
        currentSetting.baudRate = static_cast<QSerialPort::BaudRate>(
                ui->baudRateBox->itemData(ui->baudRateBox->currentIndex()).toInt());
    }
    currentSetting.stringBaudRate = QString::number(currentSetting.baudRate);

    currentSetting.dataBits = static_cast<QSerialPort::DataBits>(
            ui->dataBitsBox->itemData(ui->dataBitsBox->currentIndex()).toInt());
    currentSetting.stringDataBits = ui->dataBitsBox->currentText();

    currentSetting.parity = static_cast<QSerialPort::Parity>(
            ui->parityBox->itemData(ui->parityBox->currentIndex()).toInt());
    currentSetting.stringParity = ui->parityBox->currentText();

    currentSetting.stopBits = static_cast<QSerialPort::StopBits>(
            ui->stopBitsBox->itemData(ui->stopBitsBox->currentIndex()).toInt());
    currentSetting.stringStopBits = ui->stopBitsBox->currentText();

    currentSetting.flowControl = static_cast<QSerialPort::FlowControl>(
            ui->flowControlBox->itemData(ui->flowControlBox->currentIndex()).toInt());
    currentSetting.stringFlowControl = ui->flowControlBox->currentText();

    currentSetting.localEchoEnabled = ui->localEchoCheckBox->isChecked();
}
