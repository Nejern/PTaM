#include "exercicewindow.h"

#include <QRandomGenerator>
#include <qstringliteral.h>
#include <random>

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
    case 4: {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(5, 15);

      int vertexesNum = dis(gen);
      QList<int> prueferCode;

      for (int num = 1; num <= vertexesNum; num++){
        prueferCode.append(num);
      }
      std::shuffle(prueferCode.begin(), prueferCode.end(), gen);
      prueferCode.removeLast();
      prueferCode.removeLast();

      QString prueferCodeData;
      prueferCodeData = QString::number(vertexesNum) + " ";

      for (int value : prueferCode){
        prueferCodeData += QString::number(value) + " ";
      }

      prueferCodeData.chop(1);
      excerciseRawData = prueferCodeData;
      ui->excerciseText->setText("Декодируйте код Прюффера");
      ui->excerciseData->setText(prueferCodeData.trimmed() + ", \n где первое число - количество вершин, а после идут номера вершин через пробел. \nОтвет запишите в формате \"x y, z w, ... \" ");
    }break;
    case 5: {
      ui->excerciseText->setText("5");
    }break;
  }
}

void ExerciceWindow::onAnswerButtonClick() {
  QString answer = ui->answerLineEdit->text();
  client->checkExercise(excerciseId, answer, excerciseRawData);
}