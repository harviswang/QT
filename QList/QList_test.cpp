#include <QDebug>

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    QList<int> list;
    for (int j = 0; j < 10; j++) {
        list.insert(list.end(), j);
    }

    for (QList<int>::iterator i = list.begin(); i != list.end(); i++) {
        qDebug()<< *i;
        *i *= 10;
    }

    for (QList<int>::iterator i = list.begin(); i != list.end(); i++) {
        qDebug()<< *i;
    }
    return(0);
}
