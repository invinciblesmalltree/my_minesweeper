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
    setFixedSize(600, 800);

    auto layout = make_unique<QVBoxLayout>(this);
    layout->setAlignment(QFlags(AlignCenter));
    layout->setSpacing(20);

    auto titleLabel = make_unique<QLabel>(u"挖地雷"_s);
    auto startGameButton = make_unique<QPushButton>(u"开始游戏"_s);
    auto AIPlayerButton = make_unique<QPushButton>(u"AI 玩  家"_s);
    auto rankingTableButton = make_unique<QPushButton>(u"排  行  榜"_s);
    auto instructionsButton = make_unique<QPushButton>(u"玩法说明"_s);
    auto aboutButton = make_unique<QPushButton>(u"关       于"_s);

    titleLabel->setAlignment(QFlags(AlignCenter));
    titleLabel->setStyleSheet(u"font-size: 72px; color: #4682B4; margin: 10 auto;"_s);
    for (const auto button: {startGameButton.get(), AIPlayerButton.get(), rankingTableButton.get(),
                             instructionsButton.get(), aboutButton.get()})
        button->setStyleSheet(uR"(
            QPushButton {
                font-size: 32px;
                padding: 15px;
                width: 300px;
                margin: 10 150;
                border-radius: 15px;
                background-color: #87CEFA;
                color: white;
                border: 2px solid #4682B4;
            }
            QPushButton:hover { background-color: #00BFFF; }
            QPushButton:pressed { background-color: #1E90FF; }
        )"_s);

    connect(startGameButton.get(), &QPushButton::clicked, [this] {
        DifficultyMenu difficultyMenu(this);
        difficultyMenu.exec();
    });
    connect(AIPlayerButton.get(), &QPushButton::clicked, [this] {
        DifficultyMenu difficultyMenu(this);
        difficultyMenu.exec();
    });
    connect(rankingTableButton.get(), &QPushButton::clicked, [this] {
        RankingTableUI ranking_table(this);
        ranking_table.exec();
    });
    connect(instructionsButton.get(), &QPushButton::clicked, [this] {
        InstructionsUI instructions(this);
        instructions.exec();
    });
    connect(aboutButton.get(), &QPushButton::clicked, [this] {
        AboutUI about(this);
        about.exec();
    });

    layout->addWidget(titleLabel.release());
    layout->addWidget(startGameButton.release());
    layout->addWidget(AIPlayerButton.release());
    layout->addWidget(rankingTableButton.release());
    layout->addWidget(instructionsButton.release());
    layout->addWidget(aboutButton.release());

    setLayout(layout.release());
}
