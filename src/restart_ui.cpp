#include "restart_ui.h"
#include "difficulty_menu.h"
#include "main_menu.h"
#include "ranking_table_ui.h"

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

using namespace std;
using namespace Qt;

RestartUI::RestartUI(int type, QWidget *parent) : QDialog(parent) {
    if (type == 1)
        setWindowTitle(u"你赢了！"_s);
    else if (type == 0)
        setWindowTitle(u"你输了！"_s);
    setFixedSize(600, 800);

    auto titleLabel = make_unique<QLabel>(u""_s);
    if (type == 1) {
        titleLabel->setText(u"你赢了！"_s);
        titleLabel->setStyleSheet(u"color: #18DE41; font-size: 72px; margin: 20 auto;"_s);
    } else if (type == 0) {
        titleLabel->setText(u"你输了！"_s);
        titleLabel->setStyleSheet(u"color: #E01D37; font-size: 72px; margin: 20 auto;"_s);
    }
    auto startGameButton = make_unique<QPushButton>(u"再来一局"_s);
    auto AIPlayerButton = make_unique<QPushButton>(u"再来一局 AI"_s);
    auto mainMenuButton = make_unique<QPushButton>(u"返回主界面"_s);
    auto rankingTableButton = make_unique<QPushButton>(u"排  行  榜"_s);
    auto exitButton = make_unique<QPushButton>(u"退出游戏"_s);
    auto layout = make_unique<QVBoxLayout>(this);

    for (const auto button: {startGameButton.get(), AIPlayerButton.get(), mainMenuButton.get(),
                             rankingTableButton.get(), exitButton.get()})
        button->setStyleSheet(uR"(
            QPushButton {
                background-color: #2ECFD4;
                border: 2px solid #28B4B8;
                border-radius: 15px;
                font-size: 32px;
                margin: 10 auto;
                padding: 15px;
                width: 360px;
            }
            QPushButton:hover { background-color: #28B4B8; }
            QPushButton:pressed { background-color: #22989C; }
        )"_s);

    connect(startGameButton.get(), &QPushButton::clicked, [this, parent] {
        DifficultyMenu(this).exec();
        close();
        parent->close();
    });
    connect(AIPlayerButton.get(), &QPushButton::clicked, [this, parent] {
        DifficultyMenu(this, true).exec();
        close();
        parent->close();
    });
    connect(mainMenuButton.get(), &QPushButton::clicked, [this, parent] {
        (new MainMenu(nullptr))->show();
        close();
        parent->close();
    });
    connect(rankingTableButton.get(), &QPushButton::clicked, [this] { RankingTableUI(this).exec(); });
    connect(exitButton.get(), &QPushButton::clicked, [] { QApplication::exit(); });

    layout->setAlignment(QFlags(AlignCenter));
    layout->addWidget(titleLabel.release());
    for (const auto button: {startGameButton.release(), AIPlayerButton.release(), mainMenuButton.release(),
                             rankingTableButton.release(), exitButton.release()})
        layout->addWidget(button);
    setLayout(layout.release());
}
