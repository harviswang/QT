#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>

QT_USE_NAMESPACE

namespace Ui {
class SettingsDialog;
}

class QIntValidator;

class SettingDialog : public QDialog
{
    Q_OBJECT
    
public:
    struct Setting {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };
    
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

    Setting getSetting() const;
    enum SettingsDialogBaudrate {
        Baudrate0 = 0,
        Baudrate50 = 50,
        Baudrate75 = 75,
        Baudrate110 = 110,
        Baudrate134 = 134,
        Baudrate150 = 150,
        Baudrate200 = 200,
        Baudrate300 = 300,
        Baudrate600 = 600,
        Baudrate1200 = 1200,
        Baudrate1800 = 1800,
        Baudrate2400 = 2400,
        Baudrate4800 = 4800,
        Baudrate9600 = 9600,
        Baudrate19200 = 19200,
        Baudrate38400 = 38400,
        Baudrate57600 = 57600,
        Baudrate115200 = 115200,
        Baudrate230400 = 230400,
        Baudrate460800 = 460800,
        Baudrate500000 = 500000,
        Baudrate576000 = 576000,
        Baudrate921600 = 921600,
        Baudrate1000000 = 1000000,
        Baudrate1152000 = 1152000,
        Baudrate1500000 = 1500000,
        Baudrate2000000 = 2000000,
        Baudrate2500000 = 2500000,
        Baudrate3000000 = 3000000,
        Baudrate3500000 = 3500000,
        Baudrate4000000 = 4000000,
    };
    Q_ENUM(SettingsDialogBaudrate);

private slots:
    void showPortInfo(int idx);
    void apply();
    void checkCustomBaudRatePolicy(int idx);
    void checkCustomDevicePathPolicy(int idx);
    
private:
    void fillSerialPortParameters();
    void fillSerialPortInfo();
    void updateSetting();
    
private:
    Ui::SettingsDialog *ui;
    Setting currentSetting;
    QIntValidator *intValidator;
};
#endif // SETTINGSDIALOG_H
