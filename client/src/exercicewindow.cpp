#include "exercicewindow.h"

#include <QRandomGenerator>

#include "ui_exercicewindow.h"

ExerciceWindow::ExerciceWindow(QWidget *parent, int excerciseNumber)
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

  case 1: {
    // Установка текста задачи
    ui->excerciseText->setText("Постройте минимальный каркас графа.");

    // Генерация данных для задачи
    int numNodes = QRandomGenerator::global()->bounded(4, 10);
    QString generatedData = QString::number(numNodes) + " ";

    QList<QPair<int, int>> edges;
    for (int i = 1; i < numNodes; ++i) {
      int node1 = QRandomGenerator::global()->bounded(i);
      int node2 = i;
      edges.append(qMakePair(node1, node2));
      generatedData +=
          QString::number(node1) + " " + QString::number(node2) + " ";
    }

    // Сохранение данных для задачи чтобы потом кинуть в сервер
    excerciseRawData = generatedData.trimmed();
    qDebug() << excerciseRawData;

    // Форматирование данных для ui
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

    // Установка данных для задачи в ui
    ui->excerciseData->setText(formattedExcerciseData.trimmed());
  } break;

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
    ui->excerciseText->setText("5");
    break;
  }
}

void ExerciceWindow::onAnswerButtonClick() {
  QString answer = ui->answerLineEdit->text();
  client->checkExercise(excerciseId, answer, excerciseRawData);
}
