#include "gameover_win_ui.h"
#include "record_bean.h"
#include "record_dao.h"
#include "restart_ui.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

using namespace std;
using namespace Qt;

GameOverWinUI::GameOverWinUI(int time, QWidget *parent) : QDialog(parent) {
    setWindowTitle(u"你赢了！"_s);
    setFixedSize(300, 200);

    auto titleLabel = make_unique<QLabel>();
    auto nameEdit = make_unique<QLineEdit>();
    auto confirmButton = make_unique<QPushButton>(u"确定"_s);
    auto layout = make_unique<QVBoxLayout>(this);

    titleLabel->setStyleSheet(uR"(
        color: #18DE41;
        font-size: 24px;
        font-weight: bold;
        qproperty-text: '大侠，请留下你的名字！'
    )"_s);
    nameEdit->setStyleSheet(uR"(
        font-size: 18px;
        margin: 10 auto;
        qproperty-placeholderText: '请输入你的名字'
    )"_s);
    confirmButton->setStyleSheet(u"margin: 0 100;"_s);

    connect(confirmButton.get(), &QPushButton::clicked, [this, time, nameEdit = nameEdit.get(), parent] {
        if (nameEdit->text().isEmpty())
            return;
        record_db::getInstance()->insert(Record{-1, nameEdit->text().toStdString(), time});
        accept();
        RestartUI(1, parent).exec();
    });

    layout->addWidget(titleLabel.release());
    layout->addWidget(nameEdit.release());
    layout->addWidget(confirmButton.release());
    layout->setAlignment(QFlags(AlignCenter));
    setLayout(layout.release());
}
