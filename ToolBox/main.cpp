#include "ToolBox.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    int j, k;
    j = k = 0;
    int i = j = k = 1;

    QApplication a(argc, argv);
    QFile file(":/ToolBox/Resources/ToolBox.qss");
    if (file.open(QFile::ReadOnly))
    {
        qApp->setStyleSheet(file.readAll());
    }
    file.close();

    ToolBox w;
    w.show();
    return a.exec();
}
