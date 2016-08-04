#ifndef QPUSHBUTTON_TEST_H
#define QPUSHBUTTON_TEST_H

#include <QWidget>
class QPushButton;

namespace Ui {
    class QPushButton_test;
}

class QPushButton_test : public QWidget
{
    Q_OBJECT
    
public:
    QPushButton_test(QWidget *parent = 0);
    ~QPushButton_test();
    
private slots:
    void handleButton();
    void handleButtonPressed();

private:
    QPushButton *testPushButton;
};

#endif // QPUSHBUTTON_TEST_H
