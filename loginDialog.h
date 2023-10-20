#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "lineedit.h"
#include "timeutils.h"

#include <QKeyEvent>
#include <QDialog>

namespace Ui {
class loginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_loginButton_clicked();
    void on_exitButton_clicked();
    void onUserKeyPressEvent(QKeyEvent* event);
    void onUserKeyReleaseEvent(QKeyEvent* event);
    void onPwdKeyPressEvent(QKeyEvent* event);
    void onPwdKeyReleaseEvent(QKeyEvent* event);



private:
    Ui::loginDialog *ui;
    LineEdit* lineEditUsername;
    LineEdit* lineEditPassword;
    void reportKeyDown(QKeyEvent* event);
    void reportKeyUp(QKeyEvent* event, TimeUtils::timestamp_t lastPressed);
};

#endif // LOGINDIALOG_H
