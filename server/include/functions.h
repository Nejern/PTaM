#pragma once

#include <QJsonDocument>
#include <QJsonObject>

/**
 * @brief Класс ServerFunctions предоставляет функции для обработки команд
 * сервера.
 */
class ServerFunctions {
 public:
  /**
   * @brief Разбирает входящее сообщение и вызывает соответствующую функцию.
   * @param message Входящее сообщение для разбора.
   * @return Результат выполнения команды.
   */
  static QByteArray parse(const QString &message);

 private:
  /**
   * @brief Выбирает команду из JSON и вызывает соответствующую функцию.
   * @param json JSON документ с командой и данными.
   * @return Результат выполнения команды.
   */
  static QByteArray selectCommand(const QJsonDocument &json);

  /**
   * @brief Регистрирует нового пользователя на основе данных JSON.
   * @param json JSON объект с данными нового пользователя.
   * @return Результат выполнения команды регистрации.
   */
  static QByteArray registerUser(const QJsonObject &json);

  /**
   * @brief Аутентифицирует пользователя на основе данных JSON.
   * @param json JSON объект с данными пользователя для входа.
   * @return Результат выполнения команды аутентификации.
   */
  static QByteArray loginUser(const QJsonObject &json);
  static QByteArray getGrades(const QJsonObject &);
  static QByteArray checkExercise(const QJsonObject &json);
};
