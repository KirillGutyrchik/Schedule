#include "login.h"
#include "ui_login.h"

Login::Login(QSqlQuery * query, QWidget *parent)
:
    QWidget(parent),
    ui(new Ui::Login),
    query(query)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    QString username, password;

    username = ui->lineEdit_login_username->text();
    password = ui->lineEdit_login_password->text();

    if(username.isEmpty())
        ui->label_login_info->setText("Введите логин");
    else if(password.isEmpty())
        ui->label_login_info->setText("Введите пароль");
    else
    {
        query->prepare("SELECT id FROM users WHERE username = :username AND password = :password");
        query->bindValue(":username", username);
        query->bindValue(":password", password);
        query->exec();
        if(!query->next())
        {
            ui->label_login_info->setText("Неверный логин или пароль");
            ui->lineEdit_login_password->clear();
        }
        else
        {
            size_t id = query->value(0).toULongLong();

            query->prepare("SELECT * FROM students WHERE id = :id");
            query->bindValue(":id", id);
            query->exec();
            if(query->next())
            {
                emit login(query->value(1).toString(), "students" , query->value(3).toULongLong());
                return;
            }

            query->prepare("SELECT * FROM teachers_accounts WHERE id = :id");
            query->bindValue(":id", id);
            query->exec();
            if(query->next())
            {
                emit login(query->value(1).toString(), "teachers" , query->value(3).toULongLong());
                return;
            }

            query->prepare("SELECT * FROM admins WHERE id = :id");
            query->bindValue(":id", id);
            query->exec();
            if(query->next())
            {
                emit login(query->value(1).toString(), "admins" , 0);
                return;
            }
        }
    }
}


void Login::on_pushButton_login_to_register_clicked()
{
    emit loginToRegister();
}


void Login::on_lineEdit_login_username_returnPressed()
{
    ui->lineEdit_login_password->setFocus();
}


void Login::on_lineEdit_login_password_returnPressed()
{
    on_pushButton_login_clicked();
}

