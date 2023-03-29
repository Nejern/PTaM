#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QByteArray>
#include <QMap>
#include <QString>
#include <QStringList>

QByteArray log_in(QString username, QString password);

QByteArray log_out();

QByteArray give_a_role(QString username, QString new_role);

QByteArray change_role(QString username, QString new_role);

QByteArray change_pass(QString old_pass, QString new_pass1, QString new_pass2);

QByteArray add_user(QString username, QString new_role);

QByteArray show_pass(QString account);

QByteArray invalidRequest();

QByteArray parse(QString message);
#endif
