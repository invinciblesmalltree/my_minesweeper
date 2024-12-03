#pragma once
#include <QDialog>

class DifficultyMenu final : public QDialog {
public:
    explicit DifficultyMenu(QWidget *parent, bool enable_ai = false);
};
