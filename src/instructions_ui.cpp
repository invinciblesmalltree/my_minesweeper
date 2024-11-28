#include "instructions_ui.h"

#include <QLabel>
#include <QScrollArea>
#include <QScroller>
#include <QVBoxLayout>

using namespace std;
using namespace Qt;

InstructionsUI::InstructionsUI(QWidget *parent) : QDialog(parent) { // 挖地雷说明页
    setWindowTitle(u"玩法说明"_s);
    setFixedSize(800, 600);

    auto titleLabel = make_unique<QLabel>();
    auto contentLabel = make_unique<QLabel>();
    auto bottomLabel = make_unique<QLabel>();
    auto scrollAreaLayout = make_unique<QVBoxLayout>();
    auto scrollArea = make_unique<QScrollArea>();
    auto layout = make_unique<QVBoxLayout>(this);

    titleLabel->setStyleSheet(uR"(
        color: #44CC86;
        font-size: 48px;
        font-weight: bold;
        qproperty-text: '挖地雷玩法说明'
    )"_s);
    contentLabel->setText(uR"(挖地雷是一款经典的单人游戏，是许多人童年的回忆。

一、游戏目标
      玩家需要在避开所有地雷的同时，尽可能在最短时间内清除棋盘上所有地雷。

二、游戏设置
  1. 棋盘：游戏棋盘由一定数量的格子组成。
 2. 地雷：棋盘上随机分布着一些地雷，每个格子下都有可能有一个地雷。
 3. 数字：没有地雷的格子会显示一个数字。该数字代表着此格周围8格内地雷数目。

三、基本操作
  1. 左键点击：揭开格子内隐藏的内容。
 2. 右键点击：在格子上显示旗帜，标记此格为地雷。如果此格已被标记为地雷，再次点击右键会显示待定，标记此格可能为地雷。
 3. 左右键同时点击：如果一个已被揭开的格子所示地雷数量等于周围已被标记的地雷数量，系统会自动揭示其周围所有未被标记的格子。如果其周围存在待定标记或其所示地雷数量不等于周围已被标记的地雷数量，则不会自动揭示。

四、游戏规则
  1. 揭示地雷：如果玩家点击了一个有地雷的格子，游戏结束。
 2. 揭示数字：如果玩家点击了一个没有地雷的格子，格子会显示其周围的地雷数量。
 3. 揭示空白区域：如果玩家双击一个周围地雷已被标记的空白格子，游戏会自动揭示周围所有未被标记的格子。
 4. 标记旗帜：玩家可以在怀疑有地雷的格子上放置旗帜作为标记。
 5. 胜利条件：玩家正确地标记所有地雷格子及揭开所有空白格子。

五、游戏策略
  1. 逻辑推理：玩家需要根据揭示的数字和已标记的地雷位置，逻辑推理出哪些格子下有地雷。
 2. 概率判断：在没有足够信息的情况下，玩家需要根据概率来判断哪些格子更可能是安全的。

六、难度选择
  1. 初级：9x9的棋盘，10个地雷。
 2. 中级：16x16的棋盘，40个地雷。
 3. 高级：30x16的棋盘，99个地雷。
 4. 自定义：自己规定棋盘大小和地雷数量。

七、排行榜
      排行榜记录玩家完成游戏所需的时间。所用的时间越少排名越前。)"_s);
    contentLabel->setStyleSheet(uR"(
        color: #333;
        font-size: 16px;
        qproperty-alignment: 'AlignLeft';
        qproperty-wordWrap: true;
    )"_s);
    bottomLabel->setStyleSheet(uR"(
        color: #555;
        font-size: 24px;
        font-weight: bold;
        qproperty-text: '以上就是挖地雷游戏的基本玩法说明。祝你游戏愉快，小心地雷！'
    )"_s);
    scrollAreaLayout->addWidget(contentLabel.release());
    scrollAreaLayout->addWidget(bottomLabel.release());
    scrollArea->setWidget(new QWidget(this));
    scrollArea->widget()->setLayout(scrollAreaLayout.release());
    scrollArea->widget()->setStyleSheet(u"background-color: #f5f5f5;"_s);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet(uR"(
        QScrollArea {
            border: none;
            background-color: #f5f5f5;
        }
        QScrollBar:vertical {
            border: none;
            background: #e0e0e0;
            width: 12px;
            margin: 0px 0px 0px 0px;
            border-radius: 6px;
        }
        QScrollBar::handle:vertical {
            background: #8f8f8f;
            min-height: 20px;
            border-radius: 6px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            border: none;
            background: none;
        }
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: none;
        }
    )"_s);
    // 设置支持左键触摸滚动
    QScroller::grabGesture(scrollArea.get(), QScroller::LeftMouseButtonGesture);

    layout->addWidget(titleLabel.release());
    layout->addWidget(scrollArea.release());
    setLayout(layout.release());
}
