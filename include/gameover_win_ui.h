#pragma once
#include <QDialog>

class GameOverWinUI final : public QDialog {
public:
    GameOverWinUI(int time, QWidget *parent);
};
