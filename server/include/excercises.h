#pragma once

#include <QString>

class Excercises {
public:
  /**
   * @brief Проверяет правильность ответа на задание.
   * @param answer QString с ответом пользователя.
   * @param exercise_data QString с данными задания.
   * @return true, задание решено верно, иначе false.
   */

  static bool task1(QString answer, QString exercise_data);

  /**
   * @brief Проверяет правильность ответа на задание.
   * @param answer QString с ответом пользователя.
   * @param exercise_data QString с данными задания.
   * @return true, задание решено верно, иначе false.
   */
  static bool task2(QString answer, QString exercise_data);

  /**
   * @brief Проверяет правильность ответа на задание.
   * @param answer QString с ответом пользователя.
   * @param exercise_data QString с данными задания.
   * @return true, задание решено верно, иначе false.
   */
  static bool task3(QString answer, QString exercise_data);

  /**
   * @brief Проверяет правильность ответа на задание.
   * @param answer QString с ответом пользователя.
   * @param exercise_data QString с данными задания.
   * @return true, задание решено верно, иначе false.
   */
  static bool task4(QString answer, QString exercise_data);

  /**
   * @brief Проверяет правильность ответа на задание.
   * @param answer QString с ответом пользователя.
   * @param exercise_data QString с данными задания.
   * @return true, задание решено верно, иначе false.
   */
  static bool task5(QString answer, QString exercise_data);
};
