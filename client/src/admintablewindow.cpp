#include "admintablewindow.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardItemModel>

#include "ui_admintablewindow.h"
AdminTableWindow::AdminTableWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AdminTableWindow) {
  ui->setupUi(this);
  client = Client::getInstance();
  connect(client, SIGNAL(handleMessage(QString)), this,
          SLOT(createTable(QString)));
  client->getGrades();
}

AdminTableWindow::~AdminTableWindow() { delete ui; }

void AdminTableWindow::createTable(QString response) {
  QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
  if (jsonDoc.isNull() || !jsonDoc.isArray()) {
    qDebug() << "Invalid table data";
    return;
  }

  QJsonArray jsonArray = jsonDoc.array();
  int rowCount = jsonArray.size();
  int columnCount = 6;  // Предполагается, что таблица будет иметь 6 столбцов

  // Создание модели данных для таблицы
  QStandardItemModel *model =
      new QStandardItemModel(rowCount, columnCount, this);

  // Установка заголовков столбцов
  model->setHeaderData(0, Qt::Horizontal, "Имя");
  model->setHeaderData(1, Qt::Horizontal, "Фамилия");
  model->setHeaderData(2, Qt::Horizontal, "Отчество");
  model->setHeaderData(3, Qt::Horizontal, "Учебная группа");
  model->setHeaderData(4, Qt::Horizontal, "Задание");
  model->setHeaderData(5, Qt::Horizontal, "% корретных ответов");

  // Заполнение модели данными из JSON
  for (int i = 0; i < rowCount; ++i) {
    QJsonObject jsonObject = jsonArray.at(i).toObject();

    QString firstname = jsonObject.value("firstname").toString();
    QString surname = jsonObject.value("surname").toString();
    QString patronymic = jsonObject.value("patronymic").toString();
    QString studyGroup = jsonObject.value("studygroup").toString();
    QString exercise = jsonObject.value("exercise").toString();
    QString grade = jsonObject.value("grade").toString();

    model->setData(model->index(i, 0), firstname);
    model->setData(model->index(i, 1), surname);
    model->setData(model->index(i, 2), patronymic);
    model->setData(model->index(i, 3), studyGroup);
    model->setData(model->index(i, 4), exercise);
    model->setData(model->index(i, 5), grade);
  }

  ui->tableView->setModel(model);
  ui->tableView->resizeColumnsToContents();
}