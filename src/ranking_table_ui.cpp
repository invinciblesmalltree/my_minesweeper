#include "ranking_table_ui.h"
#include "record_dao.h"

#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

using namespace std;
using namespace Qt;

RankingTableUI::RankingTableUI(QWidget *parent) : QDialog(parent) { // 排行榜页
    setWindowTitle(u"排行榜"_s);
    setFixedSize(600, 500);

    auto table = make_unique<QTableWidget>(this);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({u"名字"_s, u"时间"_s, u""_s});

    // 全局不可点击
    table->setEditTriggers(QFlags(QAbstractItemView::NoEditTriggers));
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setCornerButtonEnabled(false);
    table->horizontalHeader()->setSectionsClickable(false);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    table->setStyleSheet(uR"(
        QTableView::item:focus { border: none; }
        QTableView {
            font-size: 32px;
            outline: none;
        }
        QHeaderView::section {
            height: 60px;
            font-size: 32px;
        }
        QPushButton {
            background-color: transparent;
            border: none;
            outline: none;
        }
        QPushButton:pressed { background-color: transparent; }
        QPushButton:focus { outline: none; }
    )"_s);
    table->verticalHeader()->setDefaultSectionSize(60); // 行高
    table->setFixedHeight(364);

    auto bottomLayout = make_unique<QHBoxLayout>();
    auto frontButton = make_unique<QPushButton>(u"上一页"_s);
    frontButton->setFixedWidth(80);
    auto currentPageLabel = make_unique<QLabel>(u"1"_s);
    currentPageLabel->setAlignment(AlignCenter);
    currentPageLabel->setFixedWidth(80);
    auto nextButton = make_unique<QPushButton>(u"下一页"_s);
    nextButton->setFixedWidth(80);

    // 配置 Object Name ，确保 refresh 函数能找到这两个按钮
    frontButton->setObjectName("frontButton");
    nextButton->setObjectName("nextButton");

    // 配置上下页
    currentPageNum = 1;
    connect(frontButton.get(), &QPushButton::clicked, [this] { refresh(--currentPageNum); });
    connect(nextButton.get(), &QPushButton::clicked, [this] { refresh(++currentPageNum); });

    bottomLayout->addWidget(frontButton.release());
    bottomLayout->addWidget(currentPageLabel.release());
    bottomLayout->addWidget(nextButton.release());

    auto layout = make_unique<QVBoxLayout>(this);
    layout->addWidget(table.release());
    layout->addLayout(bottomLayout.release());
    setLayout(layout.release());

    refresh(1);
}

void RankingTableUI::refresh(const int page) {
    const auto table = findChild<QTableWidget *>();
    const auto result = record_db::getInstance()->search(page - 1);
    table->setRowCount(static_cast<int>(result.size()));
    for (int i = 0; i < result.size(); ++i) {
        auto [id, name, time] = result[i];
        table->setItem(i, 0, new QTableWidgetItem(QString(name.c_str())));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(time)));
        auto deleteButton = make_unique<QPushButton>(u"×"_s);
        deleteButton->setFixedWidth(60);
        deleteButton->setProperty("id", QVariant(id));
        connect(deleteButton.get(), &QPushButton::clicked, [this, deleteButton = deleteButton.get(), page] {
            record_db::getInstance()->remove(deleteButton->property("id").toInt());
            if (page * 5 - 5 >= record_db::getInstance()->get_count())
                currentPageNum--;
            if (currentPageNum < 1)
                currentPageNum = 1;
            refresh(currentPageNum);
        });
        table->setCellWidget(i, 2, deleteButton.release());
        table->item(i, 0)->setTextAlignment(AlignCenter);
        table->item(i, 1)->setTextAlignment(AlignCenter);
    }
    const auto currentPageLabel = findChild<QLabel *>();
    currentPageLabel->setText(QString::number(page));
    const auto frontButton = findChild<QPushButton *>("frontButton");
    frontButton->setEnabled(page != 1);
    const auto nextButton = findChild<QPushButton *>("nextButton");
    nextButton->setEnabled(page * 5 < record_db::getInstance()->get_count());
}
