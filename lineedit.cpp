#include "lineedit.h"

LineEdit::LineEdit(QWidget* parent) : QLineEdit(parent)
{

}

void LineEdit::keyPressEvent(QKeyEvent* event) {
    // 不触发自动重复的事件
    if (event->isAutoRepeat()) {
        return;
    }
    QLineEdit::keyPressEvent(event);
    emit onKeyPressEvent(event);
}

void LineEdit::keyReleaseEvent(QKeyEvent* event) {
    // 不触发自动重复的事件
    if (event->isAutoRepeat()) {
        return;
    }
    QLineEdit::keyReleaseEvent(event);
    emit onKeyReleaseEvent(event);
}
