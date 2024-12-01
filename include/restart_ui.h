#pragma once
#include <QDialog>

class RestartUI final : public QDialog {
public:
    explicit RestartUI(int type, QWidget *parent);
};
