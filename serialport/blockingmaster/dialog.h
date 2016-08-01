#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "masterthread.h"

class QLabel;
class QLineEdit;
class QSpinBox;
class QPushButton;
class QComboBox;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);

private slots:
    void transaction();
    void showResponse(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);

private:
    void setControlsEnabled(bool enable);

private:
    int transactionCount;

    QLabel *serialPortLabel;
    QComboBox *serialPortComboBox;
    QLabel *waitResponseLabel;
    QSpinBox *waitResponseSpinBox;
    QLabel *requestLabel;
    QLineEdit *requestLineEdit;
    QLabel *trafficLabel;
    QLabel *statusLabel;
    QPushButton *runButton;

    MasterThread thread;
};

#endif // DIALOG_H
