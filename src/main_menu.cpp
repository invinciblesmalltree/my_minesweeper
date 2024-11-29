#include "main_menu.h"
#include "about_ui.h"
#include "difficulty_menu.h"
#include "instructions_ui.h"
#include "ranking_table_ui.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

using namespace std;
using namespace Qt;

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    setWindowTitle(u"挖地雷"_s);
    setFixedSize(1440, 810);

    auto titleLabel = make_unique<QLabel>(u"挖地雷"_s);
    auto startGameButton = make_unique<QPushButton>(u"开始游戏"_s);
    auto AIPlayerButton = make_unique<QPushButton>(u"AI 玩  家"_s);
    auto rankingTableButton = make_unique<QPushButton>(u"排  行  榜"_s);
    auto instructionsButton = make_unique<QPushButton>(u"玩法说明"_s);
    auto aboutButton = make_unique<QPushButton>(u"关       于"_s);
    auto mainLayout = make_unique<QVBoxLayout>();
    auto mainWidget = make_unique<QWidget>();
    auto layout = make_unique<QVBoxLayout>(this);

    titleLabel->setStyleSheet(uR"(
        color: #4682B4;
        font-size: 72px;
        margin: 20 auto;
    )"_s);
    for (const auto button: {startGameButton.get(), AIPlayerButton.get(), rankingTableButton.get(),
                             instructionsButton.get(), aboutButton.get()})
        button->setStyleSheet(uR"(
            QPushButton {
                background-color: #2ECFD4;
                border: 2px solid #28B4B8;
                border-radius: 15px;
                font-size: 32px;
                margin: 20 auto;
                padding: 15px;
                width: 360px;
            }
            QPushButton:hover { background-color: #28B4B8; }
            QPushButton:pressed { background-color: #22989C; }
        )"_s);
    mainWidget->setObjectName(u"mainWidget"_s);
    mainWidget->setStyleSheet(uR"(
        QWidget#mainWidget {
            background-color: rgba(255, 255, 255, 80%);
            margin: 0 400;
            border-radius: 20px;
        }
    )"_s);
    setObjectName(u"mainMenu"_s);
    setStyleSheet(uR"(
        QWidget#mainMenu {
            background-image: url(:/images/扫雷背景.png);
            background-position: center center;
        }
    )"_s);

    connect(startGameButton.get(), &QPushButton::clicked, [this] { DifficultyMenu(this).exec(); });
    connect(AIPlayerButton.get(), &QPushButton::clicked, [this] { DifficultyMenu(this).exec(); });
    connect(rankingTableButton.get(), &QPushButton::clicked, [this] { RankingTableUI(this).exec(); });
    connect(instructionsButton.get(), &QPushButton::clicked, [this] { InstructionsUI(this).exec(); });
    connect(aboutButton.get(), &QPushButton::clicked, [this] { AboutUI(this).exec(); });

    mainLayout->setAlignment(QFlags(AlignCenter));
    mainLayout->addWidget(titleLabel.release());
    for (const auto button: {startGameButton.release(), AIPlayerButton.release(), rankingTableButton.release(),
                             instructionsButton.release(), aboutButton.release()})
        mainLayout->addWidget(button);
    mainWidget->setLayout(mainLayout.release());
    layout->addWidget(mainWidget.release());
    setLayout(layout.release());
}
