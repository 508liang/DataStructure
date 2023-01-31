#include "window.h"

#include <QApplication>

// 使用Qt Creator创建project后自生成main代码，执行后，运行应用程序
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window w;
    w.show();
    return a.exec();
}
