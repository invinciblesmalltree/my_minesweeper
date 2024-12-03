#pragma once
#include <QLabel>
#include <QTimer>
#include <QWidget>

class GameUI final : public QWidget {
    int width, height, mines, minesLeft, time = 0;
    QTimer timer;
    QLabel *timeCountLabel, *minesCountLabel;
    int openedCount = 0;
    std::string numberColor[8]{
            "#0000F5", "#377E22", "#EA3323", "#00007B", "#75140C", "#377E7F", "#000000", "#808080",
    };
    bool enable_ai;
    void startGame(int i, int j);
    void gameOver(int type); // 1: win, 0: lose
    void createMinefield(int clickI, int clickJ);
    ~GameUI() override = default;

public:
    explicit GameUI(int w, int h, int n, bool enable_ai = false, QWidget *parent = nullptr);
    std::vector<std::vector<int>> minefield; // 0: empty, 1-9: mine, -1: mine
    std::vector<std::vector<int>> flags; // 0: unopened, 1: flag, 2: question mark, -1: opened
    bool gameStarted = false;
    bool isGameOver = false;
    void clickAt(int clickI, int clickJ);
    void rightClickAt(int clickI, int clickJ);
    void leftRightClickAt(int clickI, int clickJ);
};
