#include <QDebug>
#include <cstdio>

#define expression_to_string(x) #x
#define PRINT(x) do { qDebug() << expression_to_string(x) << " = " << x;} while(0)

static void fill_test();
static void indexOf_test();
static void insert_test();
static void isEmpty_test();
static void isNull_test();
static void left_test();
static void mid_test();
static void remove_test();
static void replace_test();
static void section_test();
static void setNum_test();

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
            
    qDebug() << "QString test ...";
    fill_test();
    indexOf_test();
    insert_test();
    isEmpty_test();
    isNull_test();
    left_test();
    mid_test();
    remove_test();
    replace_test();
    section_test();
    setNum_test();
    
    return 0;
}

static void fill_test()
{
    QString str = "Berlin";
    str.fill('z');
    PRINT(str);
    
    str.fill('A', 2);
    PRINT(str);
}

static void indexOf_test()
{
    QString x = "sticky question";
    QString y = "sti";
    PRINT(x.indexOf(y));
    PRINT(x.indexOf(y, 1));
    PRINT(x.indexOf(y, 10));
    PRINT(x.indexOf(y, 11));
}

static void insert_test()
{
    QString str = "meta";
    qDebug() << "origional is:" << str;
    str.insert(1, QString("hello"));
    qDebug() << "after insert is:" << str;
}

static void isEmpty_test()
{
    PRINT(QString().isEmpty());
    PRINT(QString("").isEmpty());
    PRINT(QString('A').isEmpty());
    PRINT(QString("sleep").isEmpty());
}

static void isNull_test()
{
    PRINT(QString().isNull());
    //PRINT(QString(0).isNull()); // ambiguous
    //PRINT(QString('\0').isNull()); // ambiguous
    PRINT(QString("").isNull());
}

static void left_test()
{
    QString x = "Pineapple";
    PRINT(x);
    PRINT(x.left(4));
    PRINT(x.left(-1));
}

static void mid_test()
{
    QString y = "Nine pineapples";
    PRINT(y);
    PRINT(y.mid(0, -1));
    PRINT(y.mid(2, -1));
    PRINT(y.mid(5, 4));
    PRINT(y.mid(5));
}

static void remove_test()
{
    QString s = "a thread is the unit of a process";
    PRINT(s);
    PRINT(s.remove(0, -1));
    PRINT(s.remove(0, 2));
}

static void replace_test()
{
    QString x = "Say yes!";
    QString y = "no";
    
    PRINT(x);
    PRINT(y);
    PRINT(x.replace(4, 3, y));
}

static void section_test()
{
    QString csv = "forename,middlename,surname,phone";
    QString path = "/opt/cadence/spb/data/algroIDF_is_env.txt";
    
    PRINT(csv);
    PRINT(path);
    PRINT(csv.section(',', 2, -1));
    PRINT(csv.section(',', 2, 2));
    PRINT(path.section('/', 3, 4));
    PRINT(path.section('/', 3, 4, QString::SectionSkipEmpty));
    
}

static void setNum_test()
{
    QString str = QString();
    PRINT(str);
    PRINT(str.setNum(64, 10));
    PRINT(str.setNum(0x64, 16));
}