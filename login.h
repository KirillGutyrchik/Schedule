#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtSql>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QSqlQuery * query, QWidget *parent = nullptr);
    ~Login();

signals:
    void login(QString username, QString type, size_t foreign_id);
    void loginToRegister();

private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_login_to_register_clicked();

    void on_lineEdit_login_username_returnPressed();

    void on_lineEdit_login_password_returnPressed();

private:
    Ui::Login * ui;
    QSqlQuery * query;
};

#endif // LOGIN_H
