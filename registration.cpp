#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QSqlQuery* query, QWidget *parent)
: QWidget(parent),
  ui(new Ui::Registration),
  query(query),
  groupSelection(new GroupSelection(query, this))
{
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(4, groupSelection, 4);

}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_pushButton_toLogin_clicked()
{
    emit registerToLogin();
}


void Registration::on_pushButton_register_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString confirmPassword = ui->lineEdit_confirmPassword->text();

    if(username.isEmpty())
    {
        ui->label_error->setText("Введите логин");
    }
    else if(password.isEmpty())
    {
        ui->label_error->setText("Введите пароль");
    }else if(confirmPassword.isEmpty())
    {
        ui->label_error->setText("Подтвердите пароль");
    }else if(username.size() < 4 || username.size() > 30)
    {
        ui->label_error->setText("Некорректная длина логина");
    }else if(password.size() < 6 || username.size() > 255)
    {
        ui->label_error->setText("Некорректная длина пароля");
    }else if(password != confirmPassword)
    {
        ui->label_error->setText("Пароли не совпадают");
    }else
    {
        query->prepare("SELECT id FROM students WHERE username = :username");
        query->bindValue(":username", username);
        query->exec();
        if(query->next())
        {
            ui->label_error->setText("Пользователь с таким ником уже существует");
        }else
        {



            QPair<size_t, ushort> groupid_subgroup
                    = groupSelection->getGroupAndSubGroup();

            qDebug() << "new user:" << username << password << groupid_subgroup.first << groupid_subgroup.second;

            query->prepare("INSERT INTO students (username, password, group_id, subgroup) "
                           "VALUES (:username, :password, :group_id, :subgroup)");
            query->bindValue(":username", username);
            query->bindValue(":password", password);
            query->bindValue(":group_id", groupid_subgroup.first);
            query->bindValue(":subgroup", groupid_subgroup.second);
            query->exec();
        }

    }

}


void Registration::on_lineEdit_username_returnPressed()
{
    ui->lineEdit_password->setFocus();
}


void Registration::on_lineEdit_password_returnPressed()
{
    ui->lineEdit_confirmPassword->setFocus();
}

