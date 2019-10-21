#include <QtWidgets>
#include "loginDialog.h"
#include "textedit.h"

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
    newProfileButton = new QPushButton(tr("&Create a new profile"));
    newProfileButton->setFlat(true);
    newProfileButton->setStyleSheet("QPushButton {color: #0000FF;}");
    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(loginButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::ActionRole);
    setModal(true);

    connect(usernameEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableLoginButton(const QString &)));
    connect(passwordEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableLoginButton(const QString &)));
    connect(loginButton, SIGNAL(clicked()),
            this, SLOT(loginClicked()));
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(cancelClicked()));

    QFormLayout *loginForm = new QFormLayout;
    loginForm->addRow(username, usernameEdit);
    loginForm->addRow(password, passwordEdit);
    loginForm->addWidget(buttonBox);
    loginForm->addWidget(newProfileButton);
    setLayout(loginForm);
    setFixedSize(sizeHint());
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

void loginDialog::loginClicked(){
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    //Implement interface to send data to server
    if(true)
    {
        emit loginSuccessful();
        close();
    }
    else
        return;
}

void loginDialog::cancelClicked(){
    QCoreApplication::quit();
}

void loginDialog::enableLoginButton(const QString &text){
    loginButton->setEnabled(!text.isEmpty());
}

