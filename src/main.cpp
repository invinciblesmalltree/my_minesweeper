#include "main.h"
#include "main_menu.h"

#include <QApplication>
#include <QFontDatabase>
#include <QPushButton>
#include <iostream>

using namespace Qt::StringLiterals;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 设置全局预设样式
    a.setStyleSheet(uR"(
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

    MainMenu mainMenu(nullptr);
    mainMenu.show();

    // vector<Record> result = record_db::getInstance()->search(0);
    // for (auto &record: result)
    //     cout << record.name << " " << record.time << endl;

    return QApplication::exec();
}
