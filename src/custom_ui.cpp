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
    setFixedSize(300, 200);

    auto customWidthLabel = make_unique<QLabel>(u"宽度"_s);
    auto customWidthEdit = make_unique<QLineEdit>();
    auto customHeightLabel = make_unique<QLabel>(u"高度"_s);
    auto customHeightEdit = make_unique<QLineEdit>();
    auto customMinesLabel = make_unique<QLabel>(u"地雷数"_s);
    auto customMinesEdit = make_unique<QLineEdit>();
    auto customConfirmButton = make_unique<QPushButton>(u"确定"_s);

    customWidthLabel->setStyleSheet("font-size: 24px;");
    customWidthEdit->setStyleSheet("font-size: 24px;");
    customHeightLabel->setStyleSheet("font-size: 24px;");
    customHeightEdit->setStyleSheet("font-size: 24px;");
    customMinesLabel->setStyleSheet("font-size: 24px;");
    customMinesEdit->setStyleSheet("font-size: 24px;");
    customConfirmButton->setStyleSheet("font-size: 24px;");
    customWidthLabel->setFixedWidth(100);
    customWidthEdit->setFixedWidth(100);
    customHeightLabel->setFixedWidth(100);
    customHeightEdit->setFixedWidth(100);
    customMinesLabel->setFixedWidth(100);
    customMinesEdit->setFixedWidth(100);
    customConfirmButton->setFixedWidth(100);

    // 限制只能输入数字
    customWidthEdit->setValidator(new QIntValidator(1, 50, this));
    customHeightEdit->setValidator(new QIntValidator(1, 30, this));
    customMinesEdit->setValidator(new QIntValidator(1, 1500, this));

    connect(customConfirmButton.get(), &QPushButton::clicked,
            [this, parent, customWidthEdit = customWidthEdit.get(), customHeightEdit = customHeightEdit.get(),
             customMinesEdit = customMinesEdit.get()] {
                int customWidth = customWidthEdit->text().toInt();
                int customHeight = customHeightEdit->text().toInt();
                int customMines = customMinesEdit->text().toInt();
                if (customWidth < 1 || customWidth > 50 || customHeight < 1 || customHeight > 30 || customMines < 1 ||
                    customMines > 1500) {
                    QMessageBox::warning(this, u"错误"_s,
                                         u"输入不合法，长大于0小于50，宽大于0小于30，雷数小于总格子数！"_s);
                    return;
                }
                if (customWidth * customHeight <= customMines) {
                    QMessageBox::warning(this, u"错误"_s, u"雷数小于总格子数！"_s);
                    return;
                }
                const auto gameUI = new GameUI(customWidthEdit->text().toInt(), customHeightEdit->text().toInt(),
                                               customMinesEdit->text().toInt());
                gameUI->show();
                close();
                parent->close();
                qobject_cast<QWidget *>(parent->parent())->close(); // 多了一层，所以要多调用一次
            });

    auto customWidthLayout = make_unique<QHBoxLayout>();
    customWidthLayout->addStretch();
    customWidthLayout->addWidget(customWidthLabel.release());
    customWidthLayout->addWidget(customWidthEdit.release());
    customWidthLayout->addStretch();
    auto customHeightLayout = make_unique<QHBoxLayout>();
    customHeightLayout->addStretch();
    customHeightLayout->addWidget(customHeightLabel.release());
    customHeightLayout->addWidget(customHeightEdit.release());
    customHeightLayout->addStretch();
    auto customMinesLayout = make_unique<QHBoxLayout>();
    customMinesLayout->addStretch();
    customMinesLayout->addWidget(customMinesLabel.release());
    customMinesLayout->addWidget(customMinesEdit.release());
    customMinesLayout->addStretch();
    auto customConfirmButtonLayout = make_unique<QHBoxLayout>();
    customConfirmButtonLayout->addWidget(customConfirmButton.release());
    auto customLayout = make_unique<QVBoxLayout>();
    customLayout->addLayout(customWidthLayout.release());
    customLayout->addLayout(customHeightLayout.release());
    customLayout->addLayout(customMinesLayout.release());
    customLayout->addLayout(customConfirmButtonLayout.release());
    setLayout(customLayout.release());
}
