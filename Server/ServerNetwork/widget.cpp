#include "widget.h"
#include "ui_widget.h"
#include "servernetwork.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//    ServerNetwork *server;
//    server = new ServerNetwork();
}

Widget::~Widget()
{
    delete ui;
}

