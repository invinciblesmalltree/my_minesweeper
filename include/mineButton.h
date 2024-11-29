#pragma once

#include <QMouseEvent>
#include <QPushButton>

class MineButton final : public QPushButton {
    Q_OBJECT

public:
    explicit MineButton(QWidget *parent = nullptr) : QPushButton(parent) {}

signals:
    void rightClicked();
    void leftRightClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->buttons() == (Qt::LeftButton | Qt::RightButton))
            emit leftRightClicked();
        // QPushButton::mousePressEvent(event);
    }
    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton)
            emit clicked();
        if (event->button() == Qt::RightButton)
            emit rightClicked();
        // QPushButton::mouseReleaseEvent(event);
    }
};
