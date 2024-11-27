#pragma once
#include <QDialog>

class RankingTableUI final : public QDialog {
    void refresh(int page);
    int currentPageNum = 1;

public:
    explicit RankingTableUI(QWidget *parent);
};
