#include "QOpenGLTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QOpenGLTest w;
    w.show();
    return a.exec();
}
