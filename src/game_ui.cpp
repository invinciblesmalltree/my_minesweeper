#include "game_ui.h"
#include "gameover_win_ui.h"
#include "mineButton.h"
#include "restart_ui.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <queue>
#include <random>
#include <vector>

using namespace std;
using namespace Qt;

GameUI::GameUI(const int w, const int h, const int n, QWidget *parent) :
    QWidget(parent), width(w), height(h), mines(n), minesLeft(n), minefield(h, vector(w, 0)), flags(h, vector(w, 0)),
    timer(new QTimer(this)), timeCountLabel(new QLabel(u"0"_s)),
    minesCountLabel(new QLabel(QString::number(minesLeft))) {
    setWindowTitle(u"挖地雷"_s);
    setFixedSize(30 * w, 30 * h + 30);

    auto titleLabel = make_unique<QHBoxLayout>();
    auto gridLayout = make_unique<QGridLayout>();
    auto layout = make_unique<QVBoxLayout>(this);

    setStyleSheet("QLabel { font-size: 20px; }");

    connect(&timer, &QTimer::timeout, [this] {
        time++;
        timeCountLabel->setText(QString::number(time));
    });

    setStyleSheet(uR"(
        MineButton {
            background-color: #C0C0C0;
            border-bottom: 3px solid #808080;
            border-left: 3px solid white;
            border-radius: 0px;
            border-right: 3px solid #808080;
            border-top: 3px solid white;
            font-weight: bold;
        }
        MineButton:checked {
            background-color: #BEBEBE;
            border: 2px solid #A6A6A6;
        }
    )"_s);
    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            auto button = make_unique<MineButton>();
            button->setFixedSize(30, 30);
            button->setCheckable(true);
            connect(button.get(), &MineButton::clicked, [this, i, j] {
                if (flags[j][i] == 0)
                    clickAt(i, j);
            });
            connect(button.get(), &MineButton::rightClicked, [this, i, j] { rightClickAt(i, j); });
            connect(button.get(), &MineButton::leftRightClicked, [this, i, j] { leftRightClickAt(i, j); });
            gridLayout->addWidget(button.release(), j, i);
        }

    titleLabel->addWidget(new QLabel(u"剩余:"_s));
    titleLabel->addWidget(minesCountLabel);
    titleLabel->addStretch();
    titleLabel->addWidget(new QLabel(u"时间:"_s));
    titleLabel->addWidget(timeCountLabel);
    layout->addLayout(titleLabel.release());
    layout->addLayout(gridLayout.release());
    setLayout(layout.release());
}

void GameUI::clickAt(const int clickI, const int clickJ) {
    if (!gameStarted) {
        gameStarted = true;
        startGame(clickI, clickJ);
    }
    const auto gridLayout = findChild<QGridLayout *>();
    queue<pair<int, int>> queue; // 使用队列维护所有需要翻开的格子
    vector visited(height, vector(width, 0)); // 标记格子是否已在队列中
    queue.emplace(clickI, clickJ);
    visited[clickJ][clickI] = 1;
    while (!queue.empty()) {
        auto [i, j] = queue.front();
        const auto button = dynamic_cast<MineButton *>(gridLayout->itemAtPosition(j, i)->widget());
        button->setChecked(true); // 设置按下状态
        if (minefield[j][i] > 0) {
            button->setText(QString::number(minefield[j][i]));
            button->setStyleSheet(
                    QString(("color: " + numberColor[minefield[j][i] - 1] + "; font-size: 18px;").data()));
        }
        if (minefield[j][i] == -1) {
            // 点到雷，游戏结束
            button->setStyleSheet(u"background-color: red;"_s);
            gameOver(0);
            return;
        }
        if (minefield[j][i] == 0)
            // 当前格子为空，将周围的格子加入队列
            for (int x = i - 1; x <= i + 1; x++)
                for (int y = j - 1; y <= j + 1; y++)
                    // 已翻开的格子不加入队列
                    if (x >= 0 && x < width && y >= 0 && y < height && visited[y][x] == 0 && flags[y][x] == 0)
                        queue.emplace(x, y), visited[y][x] = 1;
        flags[j][i] = -1; // 标记为已翻开
        openedCount++;
        queue.pop();
    }

    if (openedCount + mines == width * height)
        // 所有非雷格子都已翻开，游戏胜利
        gameOver(1);
}

void GameUI::rightClickAt(const int clickI, const int clickJ) {
    const auto gridLayout = findChild<QGridLayout *>();
    const auto button = dynamic_cast<MineButton *>(gridLayout->itemAtPosition(clickJ, clickI)->widget());
    if (flags[clickJ][clickI] == 0) {
        flags[clickJ][clickI] = 1;
        button->setText(u"🚩"_s);
        minesLeft--;
    } else if (flags[clickJ][clickI] == 1) {
        flags[clickJ][clickI] = 2;
        button->setText(u"❓"_s);
        minesLeft++;
    } else if (flags[clickJ][clickI] == 2) {
        flags[clickJ][clickI] = 0;
        button->setText(u""_s);
    }
    minesCountLabel->setText(QString::number(minesLeft));
}

void GameUI::leftRightClickAt(const int clickI, const int clickJ) {
    if (flags[clickJ][clickI] == -1) {
        int count = 0;
        for (int x = clickI - 1; x <= clickI + 1; x++)
            for (int y = clickJ - 1; y <= clickJ + 1; y++)
                if (x >= 0 && x < width && y >= 0 && y < height)
                    if (flags[y][x] == 1)
                        count++;
                    else if (flags[y][x] == 2) // 有待定直接返回
                        return;
        if (count == minefield[clickJ][clickI])
            for (int x = clickI - 1; x <= clickI + 1; x++)
                for (int y = clickJ - 1; y <= clickJ + 1; y++)
                    if (x >= 0 && x < width && y >= 0 && y < height && flags[y][x] == 0)
                        clickAt(x, y);
    }
}

void GameUI::startGame(const int i, const int j) {
    timer.start(1000);
    createMinefield(i, j);
}

void GameUI::gameOver(int type) {
    timer.stop();
    isGameOver = true;
    // 锁定所有按钮
    const auto gridLayout = findChild<QGridLayout *>();
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            dynamic_cast<MineButton *>(gridLayout->itemAtPosition(j, i)->widget())->setDisabled(true);
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            if (minefield[y][x] == -1) {
                const auto mineButton = dynamic_cast<MineButton *>(gridLayout->itemAtPosition(y, x)->widget());
                mineButton->setText(u""_s);
                mineButton->setIcon(QIcon(u":/images/地雷.png"_s));
                mineButton->setIconSize(QSize(28, 28));
            }

    QTimer::singleShot(1000, this, [this, type] {
        if (type == 1)
            // 胜利
            GameOverWinUI(timeCountLabel->text().toInt(), this).exec();
        else {
            // 失败
            RestartUI(0, this).exec();
        }
    });
}

void GameUI::createMinefield(const int clickI, const int clickJ) {
    random_device rd; // 随机数生成器
    mt19937 gen(rd()); // 用随机数生成器作为种子
    uniform_int_distribution<> dis(0, height * width - 1);
    for (int i = 0; i < mines; i++) {
        int row, col;
        do {
            const int index = dis(gen);
            row = index / width;
            col = index % width;
        } while (minefield[row][col] == -1 || (clickJ - row) * (clickJ - row) + (clickI - col) * (clickI - col) <= 2);
        minefield[row][col] = -1;
    }
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (minefield[j][i] != -1)
                for (int x = max(0, i - 1); x < min(width, i + 2); x++)
                    for (int y = max(0, j - 1); y < min(height, j + 2); y++)
                        if (minefield[y][x] == -1)
                            minefield[j][i]++;
}
