#include "main_menu.h"
#include "about_ui.h"
#include "difficulty_menu.h"
#include "instructions_ui.h"
#include "ranking_table_ui.h"

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>

using namespace std;
using namespace Qt;

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    setWindowTitle(u"挖地雷"_s);
    setFixedSize(600, 800);

    auto layout = make_unique<QVBoxLayout>(this);

    auto startGameButton = make_unique<QPushButton>(u"开始游戏"_s);
    auto AIPlayerButton = make_unique<QPushButton>(u"AI 玩家"_s);
    auto rankingTableButton = make_unique<QPushButton>(u"排行榜"_s);
    auto instructionsButton = make_unique<QPushButton>(u"玩法说明"_s);
    auto aboutButton = make_unique<QPushButton>(u"关于"_s);

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

    startGameButton->setStyleSheet("font-size: 40px;");
    AIPlayerButton->setStyleSheet("font-size: 40px;");
    rankingTableButton->setStyleSheet("font-size: 40px;");
    instructionsButton->setStyleSheet("font-size: 40px;");
    aboutButton->setStyleSheet("font-size: 40px;");

    startGameButton->setFixedWidth(400);
    AIPlayerButton->setFixedWidth(400);
    rankingTableButton->setFixedWidth(190);
    instructionsButton->setFixedWidth(190);
    aboutButton->setFixedWidth(400);

    startGameButton->setFixedHeight(100);
    AIPlayerButton->setFixedHeight(100);
    rankingTableButton->setFixedHeight(100);
    instructionsButton->setFixedHeight(100);
    aboutButton->setFixedHeight(100);

    auto startGameLayout = make_unique<QHBoxLayout>();
    startGameLayout->addWidget(startGameButton.release());
    auto AIPlayerLayout = make_unique<QHBoxLayout>();
    AIPlayerLayout->addWidget(AIPlayerButton.release());
    auto rankingTableAndInstructionsLayout = make_unique<QHBoxLayout>();
    rankingTableAndInstructionsLayout->addStretch();
    rankingTableAndInstructionsLayout->addWidget(rankingTableButton.release());
    rankingTableAndInstructionsLayout->addSpacing(20);
    rankingTableAndInstructionsLayout->addWidget(instructionsButton.release());
    rankingTableAndInstructionsLayout->addStretch();
    auto aboutLayout = make_unique<QHBoxLayout>();
    aboutLayout->addWidget(aboutButton.release());

    layout->addStretch();
    layout->addLayout(startGameLayout.release());
    layout->addStretch();
    layout->addLayout(AIPlayerLayout.release());
    layout->addStretch();
    layout->addLayout(rankingTableAndInstructionsLayout.release());
    layout->addStretch();
    layout->addLayout(aboutLayout.release());
    layout->addStretch();

    setLayout(layout.release());
}
