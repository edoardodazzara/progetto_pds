#include <QtWidgets>
#include "loginDialog.h"

loginDialog::loginDialog(QWidget *parent)
    :QDialog(parent){

    this->setWindowTitle("Login");
    username = new QLabel(tr("Username: "));
    usernameEdit = new QLineEdit;
    password = new QLabel(tr("Password: "));
    passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);
    username->setBuddy(usernameEdit);
    password->setBuddy(passwordEdit);
    loginButton = new QPushButton(tr("&Login"));
    cancelButton = new QPushButton(tr("&Cancel"));
}
