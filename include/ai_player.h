#pragma once
#include "game_ui.h"

#include <random>

class AIPlayer {
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
    int height, width;
    GameUI *gameUI;
    QTimer *timer;

public:
    explicit AIPlayer(GameUI *gameUI);
    ~AIPlayer() = default;
    void auto_play();
};
