#include <QtWidgets/QApplication>
#include "DwmTool.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DwmTool w;
    w.show();
    return a.exec();
}
