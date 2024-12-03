#pragma once
#include <QDialog>

class CustomUI final : public QDialog {
public:
    explicit CustomUI(QWidget *parent);
    CustomUI(QWidget *parent, bool enable_ai);
};
