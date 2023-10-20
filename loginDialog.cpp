#include "loginDialog.h"
#include "ui_loginDialog.h"
#include <QMessageBox>
#include <QDateTime>
#include <QKeyEvent>

#include <unordered_map>

// 上次每个按键的时间点
std::unordered_map<int, TimeUtils::timestamp_t> lastPressedMap;

// 上次在密码框按任意键的时间点
TimeUtils::timestamp_t lastPasswordKeyPressTime = 0;

LoginDialog::LoginDialog(QWidget *parent) :
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
        this, &LoginDialog::onUserKeyPressEvent
        );

    // 接收Password的按键按下事件
    connect(
        lineEditPassword, &LineEdit::onKeyPressEvent,
        this, &LoginDialog::onPwdKeyPressEvent
        );

    // 接收Username的按键弹起事件
    connect(
        lineEditUsername, &LineEdit::onKeyReleaseEvent,
        this, &LoginDialog::onUserKeyReleaseEvent
        );

    // 接收Password的按键弹起事件
    connect(
        lineEditPassword, &LineEdit::onKeyReleaseEvent,
        this, &LoginDialog::onPwdKeyReleaseEvent
        );

    // 把两个输入框分别放在对应布局中
    ui->userLayout->addWidget(lineEditUsername);
    ui->pwdLayout->addWidget(lineEditPassword);

}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::on_exitButton_clicked()
{

}

void LoginDialog::on_loginButton_clicked()
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

void LoginDialog::reportKeyDown(QKeyEvent* event)
{
    qDebug() << "按键" << event->key()
             << " 于" << TimeUtils::getCurrentTimeFormatted()
             << " 被按下";
}

void LoginDialog::reportKeyUp(QKeyEvent* event, TimeUtils::timestamp_t lastPressed)
{
    auto nano = TimeUtils::getCurrentNanoSinceEpoch() - lastPressed;
    qDebug() << "按键" << event->key()
             << " 于" << TimeUtils::getCurrentTimeFormatted()
             << " 被松开。"
             << " 总共按了"
             << nano << "ns，也就是"
             << (nano / 1000) << "us";
}

void LoginDialog::onUserKeyPressEvent(QKeyEvent* event)
{
    reportKeyDown(event);
    lastPressedMap[event->key()] = TimeUtils::getCurrentNanoSinceEpoch();
}

void LoginDialog::onUserKeyReleaseEvent(QKeyEvent* event)
{
    auto lastPressed = lastPressedMap[event->key()];
    reportKeyUp(event, lastPressed);
}

void LoginDialog::onPwdKeyPressEvent(QKeyEvent* event)
{
    reportKeyDown(event);
    lastPressedMap[event->key()] = TimeUtils::getCurrentNanoSinceEpoch();
    if (lastPasswordKeyPressTime != 0)
    {
        auto nano = TimeUtils::getCurrentNanoSinceEpoch()
                    - lastPasswordKeyPressTime;
        qDebug() << "距离上次按键经过了"
            << nano << " ns，也就是"
            << (nano / 1000) << " us";
    }
}

void LoginDialog::onPwdKeyReleaseEvent(QKeyEvent* event)
{
    quint64 lastPressed = lastPressedMap[event->key()];
    reportKeyUp(event, lastPressed);
    lastPasswordKeyPressTime = TimeUtils::getCurrentNanoSinceEpoch();
}
