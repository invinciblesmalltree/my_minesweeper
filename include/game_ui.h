#pragma once
#include <QWidget>

class GameUI final : public QWidget {
    int weight, height, mines;

public:
    explicit GameUI(int w, int h, int n, QWidget *parent = nullptr);
};
