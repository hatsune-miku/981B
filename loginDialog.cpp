#include "loginDialog.h"
#include "ui_loginDialog.h"
#include <QMessageBox>
#include <QDateTime>
#include <QKeyEvent>

#include <unordered_map>

std::unordered_map<int, quint64> lastPressedMap;
quint64 lastTime = 0;

myDialog::myDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    // 新建Username和Password的输入框
    lineEditUsername = new LineEdit(this);
    lineEditPassword = new LineEdit(this);

    // 接收Username的按键按下事件
    connect(
        lineEditUsername, &LineEdit::onKeyPressEvent,
        this, &myDialog::onUserKeyPressEvent
        );

    // 接收Password的按键按下事件
    connect(
        lineEditPassword, &LineEdit::onKeyPressEvent,
        this, &myDialog::onPwdKeyPressEvent
        );

    // 接收Username的按键弹起事件
    connect(
        lineEditUsername, &LineEdit::onKeyReleaseEvent,
        this, &myDialog::onUserKeyReleaseEvent
        );

    // 接收Password的按键弹起事件
    connect(
        lineEditPassword, &LineEdit::onKeyReleaseEvent,
        this, &myDialog::onPwdKeyReleaseEvent
        );

    // 把两个输入框分别放在对应布局中
    ui->userLayout->addWidget(lineEditUsername);
    ui->pwdLayout->addWidget(lineEditPassword);

}

myDialog::~myDialog()
{
    delete ui;
}


void myDialog::on_exitButton_clicked()
{

}

void myDialog::on_loginButton_clicked()
{

    /* Set userName and password, three conditions.
     * (password only contains numbers): peixiz1 ==> 201991333
     * (password contains numbers and letters): peixiz2 ==> peixiz201991333
     * (password contains numbers, uppercase letters, lowercase letters and symbols): peixiz3 ==> Zpx,19931110
     * Determine whether the password is correct
     */
    if(lineEditUsername->text().trimmed() == tr("peixiz1") && lineEditPassword->text() == tr("201991333"))
        accept();
    else if (lineEditUsername->text().trimmed() == tr("peixiz2") && lineEditPassword->text() == tr("peixiz201991333"))
        accept();
    else if (lineEditUsername->text().trimmed() == tr("peixiz3") && lineEditPassword->text() == tr("Zpx,19931110"))
        accept();

    /* wrong userName or password */
    else
    {
        QMessageBox::warning(this, tr("Warning"), tr("user name or password error!"),QMessageBox::Yes);
        lineEditUsername->clear();
        lineEditPassword->clear();
        lineEditUsername->setFocus();
    }
}
QString myDialog::getCurrentTime()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
}
void myDialog::onUserKeyPressEvent(QKeyEvent* event)
{
    qDebug() << "按键" << event->key()
             << " 于内部时间" << event->timestamp()
             << " 实际时间" << getCurrentTime()
             << " 被按下";
    lastPressedMap[event->key()] = event->timestamp();
}

void myDialog::onUserKeyReleaseEvent(QKeyEvent* event)
{
    quint64 lastPressed = lastPressedMap[event->key()];
    qDebug() << "按键" << event->key()
             << " 于内部时间" << event->timestamp()
             << " 实际时间" << getCurrentTime()
             << " 被松开。"
             << " 总共按了"
             << (event->timestamp() - lastPressed)
             << "毫秒";
}

void myDialog::onPwdKeyPressEvent(QKeyEvent* event)
{
    qDebug() << "按键" << event->key()
             << " 于内部时间" << event->timestamp()
             << " 实际时间" << getCurrentTime()
             << " 被按下";
    lastPressedMap[event->key()] = event->timestamp();
    if (lastTime != 0)
    {
        qDebug() << event->timestamp()-lastTime << " ms";
    }
}

void myDialog::onPwdKeyReleaseEvent(QKeyEvent* event)
{
    quint64 lastPressed = lastPressedMap[event->key()];
    qDebug() << "按键" << event->key()
             << " 于内部时间" << event->timestamp()
             << " 实际时间" << getCurrentTime()
             << " 被松开。"
             << " 总共按了"
             << (event->timestamp() - lastPressed)
             << "毫秒";
    lastTime = event->timestamp();
}
