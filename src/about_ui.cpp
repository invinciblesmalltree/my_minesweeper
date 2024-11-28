#include "about_ui.h"

#include <QLabel>
#include <QVBoxLayout>

using namespace std;
using namespace Qt;

AboutUI::AboutUI(QWidget *parent) : QDialog(parent) { // 关于页
    setWindowTitle(u"关于"_s);
    setFixedSize(600, 400);

    auto titleLabel = make_unique<QLabel>(this);
    auto contentLabel = make_unique<QLabel>(this);
    auto linkLabel = make_unique<QLabel>(this);
    auto layout = make_unique<QVBoxLayout>(this);

    titleLabel->setStyleSheet(uR"(
        color: #229C4C;
        font-size: 100px;
        margin: 50 auto;
        qproperty-text: '挖地雷';
    )"_s);
    contentLabel->setStyleSheet(uR"(
        color: #666;
        font-size: 20px;
        qproperty-openExternalLinks: true;
        qproperty-text: '此程序是南京邮电大学程序设计实践课程的作品<br>Copyright (c) 2024 <a href=\"https://blog.insmtr.cn/\">insmtr</a>, Joe Zhou, cac0ph0NY';
    )"_s);
    linkLabel->setStyleSheet(uR"(
        font-size: 20px;
        margin: 40 auto;
        qproperty-openExternalLinks: true;
        qproperty-text: '<a href=\"https://github.com/invinciblesmalltree/my_minesweeper\">项目开源地址</a>';
    )"_s);
    layout->setAlignment(QFlags(AlignCenter));
    for (const auto label: {titleLabel.release(), contentLabel.release(), linkLabel.release()})
        layout->addWidget(label);
    setLayout(layout.release());
}
