#include "session.h"

Session::Session(QString username,
                 QString user_type,
                 size_t  foreign_id,
                 QObject *parent)
: QObject(parent),
  username(username),
  user_type(user_type),
  foreign_id(foreign_id)
{
    qDebug() << "Start session:" << username << user_type << foreign_id;
}

Session::~Session()
{
    qDebug() << "Session end: " << username;
}
