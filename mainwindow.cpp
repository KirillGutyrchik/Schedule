#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Schedule");
    db.setPort(5432);
    db.setUserName("postgres");
    db.setPassword("postgres");
    if(!db.open())
    {
        qDebug() << db.lastError() << Qt::endl;
        exit(1);
    } else
    {
        query = db.exec();
        qDebug() << "DB opened" << Qt::endl;
    }


    ui->stackedWidget->setCurrentIndex(1);
    query.exec("SELECT name FROM universitys");
    while (query.next())
    {
        //ui->comboBox_register_university->addItem(query.value(0).toString());
    }

    connect(ui->logout, &QAction::triggered, this, &MainWindow::logOut);

    logOut();
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::logOut()
{
    if(session)
        delete session;

    ui->stackedWidget->setCurrentIndex(0);

    if(login_widget == nullptr)
    {
        login_widget = new Login(&query, this);
        ui->gridLayout_page1->addWidget(login_widget);

        connect(login_widget, &Login::login,
                this, [&](QString username, QString user_type, size_t foreign_id)
                         {
                            session = new Session(username, user_type, foreign_id);
                            ui->stackedWidget->setCurrentIndex(1);
                            delete login_widget;
                            if(registration_widget)
                                delete registration_widget;
                            login_widget = nullptr;
                            registration_widget = nullptr;
                         });

        connect(login_widget, &Login::loginToRegister,
                this,         &MainWindow::registration);
    }
}

void MainWindow::registration()
{
    ui->stackedWidget->setCurrentIndex(1);
    if(registration_widget == nullptr)
    {
        registration_widget = new Registration(&query, this);
        ui->gridLayout_page2->addWidget(registration_widget);

        connect(registration_widget, &Registration::registerToLogin,
                this,                &MainWindow::logOut);
    }
}

