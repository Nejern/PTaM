#include "excercises.h"

#include <QCoreApplication>
#include <QDebug>
#include <QMap>
#include <QStack>

// построить минимальный каркас графа
bool Excercises::task1(QString answer, QString exercise_data) {
  QStringList inputList = exercise_data.split(' ', Qt::SkipEmptyParts);
  int numNodes = inputList.takeFirst().toInt();

  QList<QPair<int, int>> edges;
  while (!inputList.isEmpty()) {
    int node1 = inputList.takeFirst().toInt();
    int node2 = inputList.takeFirst().toInt();
    edges.append(qMakePair(node1, node2));
  }

  // Сортируем ребра по весу
  std::sort(edges.begin(), edges.end(),
            [](const QPair<int, int> &edge1, const QPair<int, int> &edge2) {
              return edge1.first < edge2.first;
            });

  QList<QPair<int, int>> minimumSpanningTree;
  int numEdges = 0;

  QMap<int, int> vertexSets;
  for (int i = 0; i < numNodes; ++i) {
    vertexSets[i] = i;
  }

  for (const auto &edge : edges) {
    int root1 = vertexSets[edge.first];
    int root2 = vertexSets[edge.second];

    if (root1 != root2) {
      // Ребро не создаст цикл, добавляем его в каркас
      minimumSpanningTree.append(edge);
      numEdges++;

      if (numEdges == numNodes - 1) {
        // Достигли необходимого количества ребер
        break;
      }

      // Объединяем наборы вершин
      for (auto &vertex : vertexSets) {
        if (vertex == root2) {
          vertex = root1;
        }
      }
    }
  }

  // Формируем строку с ребрами каркаса
  QString minimumSpanningTreeStr;
  for (const auto &edge : minimumSpanningTree) {
    minimumSpanningTreeStr.append(
        QString("(%1, %2) ").arg(edge.first).arg(edge.second));
  }
  minimumSpanningTreeStr = minimumSpanningTreeStr.trimmed();
  qDebug() << minimumSpanningTreeStr;

  // Сравниваем результат алгоритма с ответом пользователя
  return minimumSpanningTreeStr == answer;
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

  for (const auto &edge : edges) {
    degrees[edge.first]++;
    degrees[edge.second]++;
  }

  QString prueferCode;

  for (int i = 0; i < numNodes - 2; ++i) {
    int leafNode = -1;
    for (const auto &node : degrees.keys()) {
      if (degrees[node] == 1) {
        leafNode = node;
        break;
      }
    }

    if (leafNode == -1) {
      qWarning() << "Invalid input. Unable to build Pruefer code.";
      return false; // тут может быть баг
    }

    degrees.remove(leafNode);

    for (const auto &edge : edges) {
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
  if (answer == exercise_data) {
    return true;
  }
  return false;
}

bool Excercises::task5(QString answer, QString exercise_data) {
  if (answer == exercise_data) {
    return true;
  }
  return false;
}
