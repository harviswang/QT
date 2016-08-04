#include <QApplication>
#include "QPushButton_test.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPushButton_test button;
    button.showNormal();

    return app.exec();
}
