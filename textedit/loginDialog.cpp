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
    hiddenButton = new QPushButton(tr("&Invisible"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(loginButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::ActionRole);

    connect(usernameEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableLoginButton(const QString &)));
    connect(passwordEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableLoginButton(const QString &)));
    connect(loginButton, SIGNAL(clicked()),
            this, SLOT(loginClicked()));
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(cancelClicked()));
    connect(hiddenButton, SIGNAL(clicked()),
            parent, SLOT(successfulLogin()));

    QFormLayout *loginForm = new QFormLayout;
    loginForm->addRow(username, usernameEdit);
    loginForm->addRow(password, passwordEdit);
    loginForm->addWidget(buttonBox);
    setLayout(loginForm);
    setFixedSize(sizeHint());
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}
//TODO
//SET WIDGET PARENT
void loginDialog::loginClicked(){
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    //Implement interface to send data to server
    if(true)
        hiddenButton->clicked(true);
    else
        return;
}

void loginDialog::cancelClicked(){
    QCoreApplication::quit();
}

void loginDialog::enableLoginButton(const QString &text){
    loginButton->setEnabled(!text.isEmpty());
}
