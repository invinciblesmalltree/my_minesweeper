#include "custom_ui.h"
#include "game_ui.h"

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <qvalidator.h>

using namespace std;
using namespace Qt;

CustomUI::CustomUI(QWidget *parent) : QDialog(parent) {
    setWindowTitle(u"自定义难度"_s);
    setFixedSize(400, 300);

    auto customWidthLabel = make_unique<QLabel>(u"宽   度"_s);
    auto customWidthEdit = make_unique<QLineEdit>();
    auto customHeightLabel = make_unique<QLabel>(u"高   度"_s);
    auto customHeightEdit = make_unique<QLineEdit>();
    auto customMinesLabel = make_unique<QLabel>(u"地雷数"_s);
    auto customMinesEdit = make_unique<QLineEdit>();
    auto customConfirmButton = make_unique<QPushButton>(u"确定"_s);
    auto customWidthLayout = make_unique<QHBoxLayout>();
    auto customHeightLayout = make_unique<QHBoxLayout>();
    auto customMinesLayout = make_unique<QHBoxLayout>();
    auto layout = make_unique<QVBoxLayout>(this);

    for (const auto label: {customWidthLabel.get(), customHeightLabel.get(), customMinesLabel.get()})
        label->setStyleSheet(uR"(
            color: #333;
            font-size: 20px;
            margin: 10 10 10 60;
        )"_s);
    for (const auto edit: {customWidthEdit.get(), customHeightEdit.get(), customMinesEdit.get()})
        edit->setStyleSheet(uR"(
            background-color: #f0f8ff;
            border: 2px solid #333;
            border-radius: 5px;
            color: #333;
            font-size: 20px;
            margin: 10 60 10 10;
            padding: 5px;
        )"_s);
    customConfirmButton->setStyleSheet(uR"(
        QPushButton {
            background-color: #4682B4;
            border-radius: 8px;
            font-size: 20px;
            margin: 10 100;
            padding: 10px;
        }
        QPushButton:hover { background-color: #2E6A8B; }
        QPushButton:pressed { background-color: #1C4D6E; }
    )"_s);

    // 限制只能输入数字
    customWidthEdit->setValidator(new QIntValidator(1, 40, this));
    customHeightEdit->setValidator(new QIntValidator(1, 25, this));
    customMinesEdit->setValidator(new QIntValidator(1, 999, this));

    connect(customConfirmButton.get(), &QPushButton::clicked,
            [this, parent, customWidthEdit = customWidthEdit.get(), customHeightEdit = customHeightEdit.get(),
             customMinesEdit = customMinesEdit.get()] {
                const int customWidth = customWidthEdit->text().toInt();
                const int customHeight = customHeightEdit->text().toInt();
                const int customMines = customMinesEdit->text().toInt();
                if (customWidth < 1 || customWidth > 40 || customHeight < 1 || customHeight > 25 || customMines < 1 ||
                    customMines > 999) {
                    QMessageBox::warning(this, u"错误"_s,
                                         u"输入不合法，长大于0小于40，宽大于0小于25，雷数须小于总格子数！"_s);
                    return;
                }
                if (customWidth * customHeight <= customMines) {
                    QMessageBox::warning(this, u"错误"_s, u"输入不合法，雷数须小于总格子数！"_s);
                    return;
                }
                (new GameUI(customWidth, customHeight, customMines))->show();
                close();
                parent->close();
                qobject_cast<QWidget *>(parent->parent())->close(); // 关闭主菜单
            });

    customWidthLayout->addWidget(customWidthLabel.release());
    customWidthLayout->addWidget(customWidthEdit.release());
    customHeightLayout->addWidget(customHeightLabel.release());
    customHeightLayout->addWidget(customHeightEdit.release());
    customMinesLayout->addWidget(customMinesLabel.release());
    customMinesLayout->addWidget(customMinesEdit.release());
    for (const auto subLayout: {customWidthLayout.release(), customHeightLayout.release(), customMinesLayout.release()})
        layout->addLayout(subLayout);
    layout->addWidget(customConfirmButton.release());
    setLayout(layout.release());
}
