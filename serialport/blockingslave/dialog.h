#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "slavethread.h"

class QLabel;
class QLineEdit;
class QComboBox;
class QSpinBox;
class QPushButton;

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
    
private slots:
    void startSlave();
    void showRequest(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);
    void activateRunButton();
    
private:
    int transactionCount;
    QLabel *serialPortLabel;
    QComboBox *serialPortComboBox;
    QLabel *waitRequestLabel;
    QSpinBox *waitRequestSpinBox;
    QLabel *responseLabel;
    QLineEdit *responseLineEdit;
    QLabel *trafficLabel;
    QLabel *statusLabel;
    QPushButton *runButton;
    
    SlaveThread thread;
};

#endif // DIALOG_H