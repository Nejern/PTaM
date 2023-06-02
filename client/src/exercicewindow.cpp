#include "exercicewindow.h"

#include <QPair>
#include <QRandomGenerator>
#include <QVector>
#include <algorithm>

#include "ui_exercicewindow.h"

ExerciceWindow::ExerciceWindow(QWidget* parent, int excerciseNumber)
    : QMainWindow(parent), ui(new Ui::ExerciceWindow) {
  ui->setupUi(this);
  connect(ui->answerButton, SIGNAL(clicked()), this,
          SLOT(onAnswerButtonClick()));
  excerciseId = excerciseNumber;
  client = Client::getInstance();
  setExcercise();
}

ExerciceWindow::~ExerciceWindow() { delete ui; }

void ExerciceWindow::setExcercise() {
  // excerciseText - описание задачи
  // excerciseData - данные для задачи для ui
  // excerciseRawData - данные для задачи для сервера (сюда то что от вашего
  // генератора засунуть надо будет)
  switch (excerciseId) {
    case 1:
      ui->excerciseText->setText("1");
      break;

    case 2:
      ui->excerciseText->setText("2");
      break;
    case 3: {
      // Установка текста задачи
      ui->excerciseText->setText("Составьте код прюффера для графа:");

      // Генерация данных для задачи
      int numNodes = QRandomGenerator::global()->bounded(4, 10);
      QString generatedData = QString::number(numNodes) + " ";

      QList<int> nodes;
      for (int i = 0; i < numNodes; ++i) {
        nodes.append(i);
      }

      std::random_device rd;
      std::mt19937 g(rd());
      std::shuffle(nodes.begin(), nodes.end(), g);

      for (int i = 1; i < numNodes; ++i) {
        int parent = nodes.at(QRandomGenerator::global()->bounded(i));
        int child = nodes.at(i);
        generatedData +=
            QString::number(parent) + " " + QString::number(child) + " ";
      }

      // Сохранение данных для задачи чтобы потом кинуть в сервер
      excerciseRawData = generatedData.trimmed();
      qDebug() << excerciseRawData;

      // Форматирование данных для для ui
      QString formattedExcerciseData;
      QStringList tokens = generatedData.split(' ');
      if (!tokens.isEmpty()) {
        int numNodes = tokens.takeFirst().toInt();
        formattedExcerciseData += QString::number(numNodes) + " ";

        while (tokens.size() >= 2) {
          int node1 = tokens.takeFirst().toInt();
          int node2 = tokens.takeFirst().toInt();
          formattedExcerciseData += "(" + QString::number(node1) + ", " +
                                    QString::number(node2) + "), ";
        }

        if (!formattedExcerciseData.isEmpty()) {
          formattedExcerciseData.chop(2);
        }
      }

      // установка данных для задачи в ui
      ui->excerciseData->setText(formattedExcerciseData.trimmed());
    } break;
    case 4:
      ui->excerciseText->setText("4");
      break;
    case 5:
      ui->excerciseText->setText("Найдите максимальный поток в графе:");
      int numVertices = QRandomGenerator::global()->bounded(
          4, 7);  // Количество вершин в графе
      QVector<int> data;

      // Генерация случайных ребер и их пропускных способностей
      for (int from = 0; from < numVertices; ++from) {
        for (int to = from + 1; to < numVertices; ++to) {
          if (to != numVertices - 1 && from != 0 &&
              QRandomGenerator::global()->bounded(0, 2) == 0)
            continue;  // 50%
          int capacity = QRandomGenerator::global()->bounded(4, 10);
          data.append(from);
          data.append(to);
          data.append(capacity);
        }
      }

      // Формирование строки в требуемом формате
      QString inputString;
      inputString.append(QString::number(numVertices));

      for (int i = 0; i < data.size(); ++i) {
        inputString.append(" ");
        inputString.append(QString::number(data[i]));
      }

      excerciseRawData = inputString;

      QStringList tokens = excerciseRawData.split(' ');

      QString formattedData;
      formattedData = tokens[0] + " ";
      for (int i = 1; i < tokens.size(); i += 3) {
        QString from = tokens[i];
        QString to = tokens[i + 1];
        QString capacity = tokens[i + 2];

        QString edge = "(" + from + ", " + to + ", " + capacity + ")";
        formattedData.append(edge);

        if (i != tokens.size() - 3) {
          formattedData.append(" ");
        }
      }

      ui->excerciseData->setText(formattedData);

      break;
  }
}

void ExerciceWindow::onAnswerButtonClick() {
  QString answer = ui->answerLineEdit->text();
  client->checkExercise(excerciseId, answer, excerciseRawData);
}