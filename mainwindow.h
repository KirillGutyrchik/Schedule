#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

#include "login.h"
#include "session.h"
#include "registration.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:


private slots:
    void logOut();
    void registration();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery query;

    Login * login_widget{nullptr};
    Registration * registration_widget{nullptr};
    Session * session{nullptr};
};



#endif // MAINWINDOW_H
