#include "widget.h"
#include <QApplication>
#include "servernetwork.h"
#include"serverviewmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    auto vm=new ServerViewModel(new ServerNetwork());

    return a.exec();
}
