#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

class QLabel; 

namespace Ui {
    class MainWindow;
}

class Console;
class SettingDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();
    
    void handleError(QSerialPort::SerialPortError error);
    
private:
    void initActionsConnections();
    
private:
    void showStatusMessage(const QString &message);
    
    Ui::MainWindow *ui;
    QLabel *status;
    Console *console;
    SettingDialog *settingDialog;
    QSerialPort *serialPort;
};


#endif // MAINWINDOW_H
