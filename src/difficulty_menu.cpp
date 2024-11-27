#include "difficulty_menu.h"
#include "custom_ui.h"
#include "game_ui.h"

#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

using namespace std;
using namespace Qt;

DifficultyMenu::DifficultyMenu(QWidget *parent) : QDialog(parent) {
    setWindowTitle(u"选择难度"_s);
    setFixedSize(600, 800);

    auto easyButton = make_unique<QPushButton>(u"简单"_s);
    auto mediumButton = make_unique<QPushButton>(u"中等"_s);
    auto hardButton = make_unique<QPushButton>(u"困难"_s);
    auto customButton = make_unique<QPushButton>(u"自定义"_s);

    connect(easyButton.get(), &QPushButton::clicked, [this, parent] {
        const auto gameUI = new GameUI(9, 9, 10);
        gameUI->show();
        close();
        parent->close();
    });
    connect(mediumButton.get(), &QPushButton::clicked, [this, parent] {
        const auto gameUI = new GameUI(16, 16, 40);
        gameUI->show();
        close();
        parent->close();
    });
    connect(hardButton.get(), &QPushButton::clicked, [this, parent] {
        const auto gameUI = new GameUI(30, 16, 99);
        gameUI->show();
        close();
        parent->close();
    });
    connect(customButton.get(), &QPushButton::clicked, [this] {
        CustomUI customUI(this);
        customUI.exec();
    });

    easyButton->setStyleSheet("font-size: 40px;");
    mediumButton->setStyleSheet("font-size: 40px;");
    hardButton->setStyleSheet("font-size: 40px;");
    customButton->setStyleSheet("font-size: 40px;");

    easyButton->setFixedWidth(400);
    mediumButton->setFixedWidth(400);
    hardButton->setFixedWidth(400);
    customButton->setFixedWidth(400);

    easyButton->setFixedHeight(100);
    mediumButton->setFixedHeight(100);
    hardButton->setFixedHeight(100);
    customButton->setFixedHeight(100);

    auto easyButtonLayout = make_unique<QHBoxLayout>();
    auto mediumButtonLayout = make_unique<QHBoxLayout>();
    auto hardButtonLayout = make_unique<QHBoxLayout>();
    auto customButtonLayout = make_unique<QHBoxLayout>();

    easyButtonLayout->addWidget(easyButton.release());
    mediumButtonLayout->addWidget(mediumButton.release());
    hardButtonLayout->addWidget(hardButton.release());
    customButtonLayout->addWidget(customButton.release());

    auto layout = make_unique<QVBoxLayout>(this);
    layout->addStretch();
    layout->addLayout(easyButtonLayout.release());
    layout->addStretch();
    layout->addLayout(mediumButtonLayout.release());
    layout->addStretch();
    layout->addLayout(hardButtonLayout.release());
    layout->addStretch();
    layout->addLayout(customButtonLayout.release());
    layout->addStretch();
    setLayout(layout.release());
}
