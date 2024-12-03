#include "difficulty_menu.h"
#include "ai_player.h"
#include "custom_ui.h"
#include "game_ui.h"

#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

using namespace std;
using namespace Qt;

DifficultyMenu::DifficultyMenu(QWidget *parent, bool enable_ai) : QDialog(parent) {
    setWindowTitle(u"选择难度"_s);
    setFixedSize(400, 500);

    auto easyButton = make_unique<QPushButton>(u"简  单"_s);
    auto mediumButton = make_unique<QPushButton>(u"中  等"_s);
    auto hardButton = make_unique<QPushButton>(u"困  难"_s);
    auto customButton = make_unique<QPushButton>(u"自定义"_s);
    auto layout = make_unique<QVBoxLayout>(this);

    for (const auto button: {easyButton.get(), mediumButton.get(), hardButton.get(), customButton.get()})
        button->setStyleSheet(uR"(
            QPushButton {
                background-color: #87CEFA;
                border: 2px solid #70AACF;
                border-radius: 15px;
                font-size: 32px;
                margin: 20 auto;
                padding: 15px;
                width: 250px;
            }
            QPushButton:hover { background-color: #70AACF; }
            QPushButton:pressed { background-color: #6093B3; }
        )"_s);

    connect(easyButton.get(), &QPushButton::clicked, [this, parent, enable_ai] {
        const auto gameUI = new GameUI(9, 9, 10, enable_ai);
        gameUI->show();
        close();
        parent->close();
        if (enable_ai)
            (new AIPlayer(gameUI))->auto_play();
    });
    connect(mediumButton.get(), &QPushButton::clicked, [this, parent, enable_ai] {
        const auto gameUI = new GameUI(16, 16, 40, enable_ai);
        gameUI->show();
        close();
        parent->close();
        if (enable_ai)
            (new AIPlayer(gameUI))->auto_play();
    });
    connect(hardButton.get(), &QPushButton::clicked, [this, parent, enable_ai] {
        const auto gameUI = new GameUI(30, 16, 99, enable_ai);
        gameUI->show();
        close();
        parent->close();
        if (enable_ai)
            (new AIPlayer(gameUI))->auto_play();
    });
    connect(customButton.get(), &QPushButton::clicked, [this, enable_ai] { CustomUI(this, enable_ai).exec(); });

    layout->setAlignment(QFlags(AlignCenter));
    for (const auto button:
         {easyButton.release(), mediumButton.release(), hardButton.release(), customButton.release()})
        layout->addWidget(button);
    setLayout(layout.release());
}
