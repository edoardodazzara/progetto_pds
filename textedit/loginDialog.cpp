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
    loginButton->setDefault(true);
    loginButton->setEnabled(false);
    cancelButton = new QPushButton(tr("&Cancel"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(loginButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::ActionRole);

    connect(usernameEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableLoginButton(const QString &)));
    connect(passwordEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableLoginButton(const QString &)));
    connect(loginButton, SIGNAL(clicked()),
            this, SLOT(loginClicked(usernameEdit->text(),passwordEdit->text())));
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(cancelClicked()));

    QFormLayout *loginForm = new QFormLayout;
    loginForm->addRow(username, usernameEdit);
    loginForm->addRow(password, passwordEdit);
    loginForm->addWidget(buttonBox);
    setLayout(loginForm);
    setFixedSize(sizeHint());
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

void loginDialog::loginClicked(QString name, QString pass){
    QString username = name;
    QString password = pass;
    //Implement interface to send data to server
}

void loginDialog::cancelClicked(){
    QCoreApplication::quit();
}

void loginDialog::enableLoginButton(const QString &text){
    loginButton->setEnabled(!text.isEmpty());
}
