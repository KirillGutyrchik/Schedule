#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include <groupselection.h>
#include <QSqlQuery>
#include <QPair>

namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QSqlQuery* query, QWidget *parent = nullptr);
    ~Registration();

signals:
   void registerToLogin();

private slots:
   void on_pushButton_toLogin_clicked();

   void on_pushButton_register_clicked();

   void on_lineEdit_username_returnPressed();

   void on_lineEdit_password_returnPressed();

private:
    Ui::Registration *ui;
    QSqlQuery* query;
    GroupSelection* groupSelection{nullptr};
};

#endif // REGISTRATION_H
