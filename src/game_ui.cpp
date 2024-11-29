#include "game_ui.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <vector>

using namespace std;
using namespace Qt;

GameUI::GameUI(const int w, const int h, const int n, QWidget *parent) : QWidget(parent), weight(w), height(h), mines(n) {
    setWindowTitle(u"挖地雷"_s);
    setFixedSize(30 * w, 30 * h + 30);

    auto minesLabel = make_unique<QLabel>(u"剩余雷数: "_s);
    auto minesCountLabel = make_unique<QLabel>(QString::number(mines));
    auto timeLabel = make_unique<QLabel>(u"时间: "_s);
    auto timeCountLabel = make_unique<QLabel>(u"0"_s);
    auto timer = make_unique<QTimer>();
    auto titleLabel = make_unique<QHBoxLayout>();
    auto layout = make_unique<QVBoxLayout>();
    auto gridLayout = make_unique<QGridLayout>();

    minesLabel->setStyleSheet("font-size: 20px;");
    minesCountLabel->setStyleSheet("font-size: 20px;");
    timeLabel->setStyleSheet("font-size: 20px;");
    timeCountLabel->setStyleSheet("font-size: 20px;");

    timer->start(1000);
    connect(timer.release(), &QTimer::timeout, [this, timeCountLabel = timeCountLabel.get()] {
        static int time = 0;
        time++;
        timeCountLabel->setText(QString::number(time));
    });

    for (int i = 0; i < w; ++i)
        for (int j = 0; j < h; ++j) {
            auto button = make_unique<QPushButton>();
            button->setFixedSize(30, 30);
            button->setStyleSheet(uR"(
                QPushButton {
                    background-color: #C0C0C0;
                    border-bottom: 3px solid #808080;
                    border-left: 3px solid white;
                    border-radius: 0px;
                    border-right: 3px solid #808080;
                    border-top: 3px solid white;
                }
                QPushButton:checked {
                    background-color: #BEBEBE;
                    border: 2px solid #A6A6A6;
                }
            )"_s);
            button->setCheckable(true);
            gridLayout->addWidget(button.release(), j, i);
        }

    titleLabel->addWidget(minesLabel.release());
    titleLabel->addWidget(minesCountLabel.release());
    titleLabel->addStretch();
    titleLabel->addWidget(timeLabel.release());
    titleLabel->addWidget(timeCountLabel.release());
    layout->addLayout(titleLabel.release());
    layout->addLayout(gridLayout.release());
    setLayout(layout.release());
}
