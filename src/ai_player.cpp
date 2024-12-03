#include "ai_player.h"
#include "game_ui.h"

#include <QApplication>
#include <QTimer>
#include <bits/random.h>

using namespace std;
using namespace Qt;

AIPlayer::AIPlayer(GameUI *gameUI) :
    height(gameUI->minefield.size()), width(gameUI->minefield[0].size()), gameUI(gameUI), timer(new QTimer(gameUI)) {
    random_device rd;
    gen = mt19937(rd());
    dis = uniform_int_distribution(0, height * width - 1);
}

void AIPlayer::auto_play() {
    QApplication::connect(timer, &QTimer::timeout, [this] {
        int row, col;
        do {
            const int index = dis(gen);
            row = index / width;
            col = index % width;
        } while ((gameUI->flags[row][col] != 0 || gameUI->minefield[row][col] == -1) && !gameUI->isGameOver);
        if (gameUI->isGameOver) {
            timer->stop();
            return;
        }
        gameUI->clickAt(col, row);
    });
    timer->start(500);
}
