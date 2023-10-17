#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "lineedit.h"
#include <QKeyEvent>
#include <QDialog>

namespace Ui {
class loginDialog;
}

class myDialog : public QDialog
{
    Q_OBJECT

public:
    explicit myDialog(QWidget *parent = nullptr);
    ~myDialog();

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
    QString getCurrentTime();
};

#endif // LOGINDIALOG_H
