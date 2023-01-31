#include "window.h"
#include "ui_window.h"
#include <QString>

window::window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::window)
{
    ui->setupUi(this);
    if (!seg.loadDict("D:\\Qt\\segmentation\\dict.txt"))
    {
        printf("文件打开失败");
        exit(0);
    }
}

window::~window()
{
    delete ui;
}
void window::on_pushButton_clicked()
{
    string s = ui->plainTextEdit->toPlainText().toStdString();
    string output = seg.cut(s);
    ui->textBrowser->setText(QString::fromStdString(output));
}
