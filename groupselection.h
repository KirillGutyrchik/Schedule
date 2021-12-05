#ifndef GROUPSELECTION_H
#define GROUPSELECTION_H

#include <QWidget>
#include <QSqlQuery>
#include <QComboBox>

namespace Ui {
class groupSelection;
}

class GroupSelection : public QWidget
{
    Q_OBJECT

public:
    explicit GroupSelection(QSqlQuery* query, QWidget *parent = nullptr);
    ~GroupSelection();

    QPair<size_t, ushort> getGroupAndSubGroup();

private:
    void comboBoxUpdate(QComboBox* combobox, const QString& item, const QString& condition);

private slots:

    void on_comboBox_university_activated(int index);

    void on_comboBox_faculty_activated(int index);

    void on_comboBox_course_activated(int index);

    void on_comboBox_group_activated(int index);


private:
    Ui::groupSelection *ui;
    QSqlQuery * query;
};

#endif // GROUPSELECTION_H
