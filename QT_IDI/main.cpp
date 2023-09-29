#include "QT_IDI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QT_IDI w;
    w.show();
    return a.exec();
}
