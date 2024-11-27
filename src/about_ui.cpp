#include "about_ui.h"

#include <QLabel>
#include <QVBoxLayout>

using namespace std;
using namespace Qt;

AboutUI::AboutUI(QWidget *parent) : QDialog(parent) { // 关于页
    setWindowTitle(u"关于"_s);
    setFixedSize(600, 400);

    auto label1 = make_unique<QLabel>(this);
    label1->setText(u"挖地雷"_s);
    label1->setStyleSheet(u"font-size: 108px;"_s);
    label1->setAlignment(QFlags(AlignCenter));

    auto label2 = make_unique<QLabel>(this);
    label2->setText(u"此程序是南京邮电大学程序设计实践课程的作品<br>"
                    "Copyright (c) 2024 <a href=\"https://blog.insmtr.cn/\">insmtr</a>, Joe Zhou, cac0ph0NY"_s);
    label2->setOpenExternalLinks(true);
    label2->setTextFormat(RichText);
    label2->setStyleSheet(u"font-size: 20px;"_s);
    label2->setAlignment(QFlags(AlignCenter));

    auto label3 = make_unique<QLabel>(this);
    label3->setText(u"<a href=\"https://github.com/invinciblesmalltree/my_minesweeper\">项目开源地址</a>"_s);
    label3->setOpenExternalLinks(true);
    label3->setTextFormat(RichText);
    label3->setStyleSheet(u"font-size: 20px;"_s);
    label3->setAlignment(QFlags(AlignCenter));

    auto layout = make_unique<QVBoxLayout>(this);
    layout->addStretch();
    layout->addWidget(label1.release());
    layout->addStretch();
    layout->addWidget(label2.release());
    layout->addStretch();
    layout->addWidget(label3.release());
    layout->addStretch();
    setLayout(layout.release());
}
