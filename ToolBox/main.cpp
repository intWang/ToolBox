#include "ToolBox.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include "ToolBoxLogicMgr.h"
int main(int argc, char *argv[])
{
    TOOLBOXLOGICMGR.Init();
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
