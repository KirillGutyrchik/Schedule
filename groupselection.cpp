#include "groupselection.h"
#include "ui_groupselection.h"

GroupSelection::GroupSelection(QSqlQuery* query, QWidget *parent)
: QWidget(parent),
  ui(new Ui::groupSelection),
  query(query)
{
    ui->setupUi(this);

    query->exec("SELECT name FROM universitys");
    while(query->next())
    {
        ui->comboBox_university->addItem(query->value(0).toString());
    }
    on_comboBox_university_activated(0);

}

GroupSelection::~GroupSelection()
{
    delete ui;
}

QPair<size_t, ushort> GroupSelection::getGroupAndSubGroup()
{
    query->prepare("SELECT groups.id FROM groups "
                   "JOIN universitys ON "
                   "universitys.name = :university "
                   "AND groups.faculty = :faculty "
                   "AND group.course = :course "
                   "AND groups.group_name = :group");
    query->bindValue(":university", ui->comboBox_university->currentText());
    query->bindValue(":faculty", ui->comboBox_faculty->currentText());
    query->bindValue(":course", ui->comboBox_course->currentText());
    query->bindValue(":group", ui->comboBox_group->currentText());
    query->exec();

    if(query->next())
    {
        return QPair<size_t, ushort>(query->value(0).toULongLong(),
                                     ui->comboBox_subGroup->currentText().toUShort());
        qDebug() << query->value(0).toString();
    }
    else
        return QPair<size_t, ushort>();
}

void GroupSelection::comboBoxUpdate(QComboBox *combobox, const QString &item, const QString &requestCondition)
{
    QString request = "SELECT DISTINCT groups.";
    QString request2 = " FROM groups JOIN universitys ON universitys.name = :university ";
    QString requestOrder = "ORDER BY groups.";


    qDebug() << request + item + request2 + requestCondition + requestOrder + item;

    combobox->clear();
    query->prepare(request + item + request2 + requestCondition + requestOrder + item);
    query->bindValue(":university", ui->comboBox_university->currentText());
    query->bindValue(":faculty", ui->comboBox_faculty->currentText());
    query->bindValue(":course", ui->comboBox_course->currentText());
    query->bindValue(":group", ui->comboBox_group->currentText());
    qDebug() << query->exec();
    if(combobox == ui->comboBox_subGroup)
    {
        if(query->next())
        {
            short num_subgroup = query->value(0).toUInt();
            for(short num = 1; num <= num_subgroup; ++num)
                combobox->addItem(QString::number(num));
        }
    }
    while(query->next())
        combobox->addItem(query->value(0).toString());
}

void GroupSelection::on_comboBox_university_activated(int index)
{
    comboBoxUpdate(ui->comboBox_faculty,
                   "faculty", " ");
    on_comboBox_faculty_activated(0);
}


void GroupSelection::on_comboBox_faculty_activated(int index)
{
    comboBoxUpdate(ui->comboBox_course,
                   "course",
                   "AND groups.faculty = :faculty ");
    on_comboBox_course_activated(0);
}


void GroupSelection::on_comboBox_course_activated(int index)
{
    comboBoxUpdate(ui->comboBox_group,
                   "group_name",
                   "AND groups.faculty = :faculty "
                   "AND groups.course = :course ");
    on_comboBox_group_activated(0);
}


void GroupSelection::on_comboBox_group_activated(int index)
{
    comboBoxUpdate(ui->comboBox_subGroup,
                   "num_subgroup",
                   "AND groups.faculty = :faculty "
                   "AND groups.course = :course "
                   "AND groups.group_name = :group ");
}


