#include <QPushButton>
#include "QPushButton_test.h"

QPushButton_test::QPushButton_test(QWidget *parent)
    : QWidget(parent)
{   
    // Create the button, make "this" the parent
    testPushButton = new QPushButton("QPushButton", this);

    // Set size and location of the button
    testPushButton->setGeometry(QRect(QPoint(100, 100), QSize(100, 50)));
    
    // Connect button signal to appropriate slot
    connect(testPushButton, SIGNAL(released()), this, SLOT(handleButton()));
    connect(testPushButton, SIGNAL(pressed()),  this, SLOT(handleButtonPressed()));
}

QPushButton_test::~QPushButton_test()
{
    if (testPushButton) {
        delete testPushButton;
    }
}

void QPushButton_test::handleButton()
{
    // Change the text
    testPushButton->setText("QPushButton Released");
    // Resize button
    testPushButton->resize(150, 50);
}

void QPushButton_test::handleButtonPressed()
{
    testPushButton->setText("QPushButton Pressed");
    testPushButton->resize(140, 50);
}
