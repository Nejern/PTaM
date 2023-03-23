#include "functions.h"


QByteArray log_in(QString username, QString password){
    return QByteArray("Авторизация\n");
}

QByteArray log_out(){
    return QByteArray("Выход\n");
}

QByteArray give_a_role(QString username, QString new_role){
    QString message = "Выдана роль " + new_role + " пользователю " + username + "\n";
    return QByteArray(message.toUtf8());
}

QByteArray change_role(QString username, QString new_role){
    QString message = "Роль пользователя " + username + " изменена на " + new_role + "\n";
    return QByteArray(message.toUtf8());
}

QByteArray change_pass(QString old_pass, QString new_pass1,  QString new_pass2){
    QString message = "Пароль пользователя изменён на " + new_pass1 + "\n";
    return QByteArray(message.toUtf8());
}

QByteArray add_user(QString username, QString new_role){
    QString message = "Пользователь " + username + " добавлен с ролью " + new_role + "\n";
    return QByteArray(message.toUtf8());
}

QByteArray show_pass(QString account){
    QString message = "Пароль от аккаунта " + account + "\n";
    return QByteArray(message.toUtf8());
}
QByteArray invalidRequest(){
    return QByteArray("Неверная команда или неверное количесво параметров.\n");
};


QByteArray parse(QString message){
    QStringList parts = message.left(message.length() - 2).split(" ");

    switch(parts.size()){
        case 1:
            if(parts[0] == "logout")
                return log_out();
        case 2:
            if(parts[0] == "showpass")
                return show_pass(parts[1]);
            break;
        case 3:
            if (parts[0] == "login")
                return log_in(parts[1],parts[2]);
            if (parts[0] == "giverole")
                return give_a_role(parts[1],parts[2]);
            if (parts[0] == "chrole")
                return change_role(parts[1],parts[2]);
            if (parts[0] == "adduser")
                return add_user(parts[1],parts[2]);
            break;
        case 4:
            if (parts[0] == "chpass")
                return change_pass(parts[1],parts[2],parts[3]);
    }
    return invalidRequest();
}