#include "excercises.h"

#include <QCoreApplication>
#include <QDebug>
#include <QMap>
#include <QStack>

bool Excercises::task1(QString answer, QString exercise_data) {
  if (answer == exercise_data) {
    return true;
  }
  return false;
}

bool Excercises::task2(QString answer, QString exercise_data) {
  if (answer == exercise_data) {
    return true;
  }
  return false;
}

bool Excercises::task3(QString answer, QString exercise_data) {
  QStringList inputList = exercise_data.split(' ', Qt::SkipEmptyParts);
  int numNodes = inputList.takeFirst().toInt();

  QList<QPair<int, int>> edges;
  while (!inputList.isEmpty()) {
    int node1 = inputList.takeFirst().toInt();
    int node2 = inputList.takeFirst().toInt();
    edges.append(qMakePair(node1, node2));
  }

  QMap<int, int> degrees;
  for (int i = 0; i < numNodes - 2; ++i) {
    degrees[i] = 0;
  }

  for (const auto& edge : edges) {
    degrees[edge.first]++;
    degrees[edge.second]++;
  }

  QString prueferCode;

  for (int i = 0; i < numNodes - 2; ++i) {
    int leafNode = -1;
    for (const auto& node : degrees.keys()) {
      if (degrees[node] == 1) {
        leafNode = node;
        break;
      }
    }

    if (leafNode == -1) {
      qWarning() << "Invalid input. Unable to build Pruefer code.";
      return false;  // тут может быть баг
    }

    degrees.remove(leafNode);

    for (const auto& edge : edges) {
      if (edge.first == leafNode || edge.second == leafNode) {
        degrees[edge.first]--;
        degrees[edge.second]--;
      }
    }

    prueferCode.append(QString::number(leafNode));
  }
  qDebug() << prueferCode;

  // вот тут надо сравнить результат алгоритма и ответа пользователя
  return prueferCode == answer;
}

bool Excercises::task4(QString answer, QString exercise_data) {
  QStringList prueferCodeSplited = exercise_data.split(" ");
  QList<int> prueferValues;
  QList<int> vertexes;
  QString prueferDecoded;

  for (QString num : prueferCodeSplited){
    int value = num.toInt();
    prueferValues.append(value);
  }

  for (int number = 0; number < prueferValues.size() + 2; number++){
    if (!prueferValues.contains(number)){
      vertexes.append(number);
    }
  }

  for (int vertex_1 : prueferValues){
    int vertex_2 = vertexes.first();
    vertexes.removeAt(0);
    prueferDecoded += QString::number(vertex_1) + " " + QString::number(vertex_2) + ", ";
  }
  prueferDecoded = prueferDecoded.left(-2);
  
  qDebug() << prueferDecoded;
  return prueferDecoded == answer;
}

bool Excercises::task5(QString answer, QString exercise_data) {
  if (answer == exercise_data) {
    return true;
  }
  return false;
}
