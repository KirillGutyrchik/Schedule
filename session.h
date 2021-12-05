#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QDebug>

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QString username,
                     QString user_type,
                     size_t  foreign_id,
                     QObject *parent = nullptr);
    ~Session();

signals:


private:
    QString username;
    QString user_type;
    size_t  foreign_id;
};

#endif // SESSION_H
