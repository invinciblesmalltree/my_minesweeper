#include "main_menu.h"
#include "gameover_win_ui.h"

#include <QApplication>
#include <QFontDatabase>
#include <QPushButton>
#include <iostream>

using namespace Qt;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 设置全局预设样式
    a.setStyleSheet(uR"(
        QLineEdit {
            color: #333;
            border: 2px solid #333;
            border-radius: 5px;
            padding: 5px;
            text-align: center;
        }
        QLabel {
            color: #333;
            qproperty-alignment: AlignCenter;
        }
        QPushButton {
            background-color: #A5DBC6;
            border: none;
            border-radius: 5px;
            color: white;
            padding: 5px;
            width: 100px;
        }
        QPushButton:hover { background-color: #8EBDAA; }
        QPushButton:pressed { background-color: #7BA393; }
        QPushButton:disabled { background-color: #D3D3D3; }
    )"_s);
    // 加载本地字体文件
    if (const int fontId = QFontDatabase::addApplicationFont(u":/fonts/原神字体.ttf"_s); fontId == -1)
        qWarning("字体加载失败");
    else
        QApplication::setFont(QFont(QFontDatabase::applicationFontFamilies(fontId).at(0)));

    (new MainMenu(nullptr))->show();

    return QApplication::exec();
}
