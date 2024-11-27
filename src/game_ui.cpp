#include "game_ui.h"

#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>
#include <vector>

using namespace std;
using namespace Qt;

GameUI::GameUI(int w, int h, int n, QWidget *parent) : QWidget(parent), weight(w), height(h), mines(n) {
    setWindowTitle(u"挖地雷"_s);
    setFixedSize(30 * w, 30 * h + 30);

    auto minesLabel = make_unique<QLabel>(u"剩余雷数: "_s);
    minesLabel->setStyleSheet("font-size: 20px;");
    auto minesCountLabel = make_unique<QLabel>(QString::number(mines));
    minesCountLabel->setStyleSheet("font-size: 20px;");
    auto timeLabel = make_unique<QLabel>(u"时间: "_s);
    timeLabel->setStyleSheet("font-size: 20px;");
    auto timeCountLabel = make_unique<QLabel>(u"0"_s);
    timeCountLabel->setStyleSheet("font-size: 20px;");

    auto timer = make_unique<QTimer>();
    timer->start(1000);
    connect(timer.release(), &QTimer::timeout, [this, timeCountLabel = timeCountLabel.get()] {
        static int time = 0;
        time++;
        timeCountLabel->setText(QString::number(time));
    });

    auto titleLabel = make_unique<QHBoxLayout>();
    titleLabel->addWidget(minesLabel.release());
    titleLabel->addWidget(minesCountLabel.release());
    titleLabel->addStretch();
    titleLabel->addWidget(timeLabel.release());
    titleLabel->addWidget(timeCountLabel.release());

    auto layout = make_unique<QVBoxLayout>();
    layout->addLayout(titleLabel.release());

    auto gridLayout = make_unique<QGridLayout>();
    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            auto button = make_unique<QPushButton>();
            button->setFixedSize(30, 30);
            button->setStyleSheet("font-size: 20px;");
            button->setCheckable(true);
            button->setAutoExclusive(false);
            gridLayout->addWidget(button.release(), j, i);
        }


    layout->addLayout(gridLayout.release());

    setLayout(layout.release());
}
