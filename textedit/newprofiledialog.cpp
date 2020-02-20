#include "newprofiledialog.h"

newProfileDialog::newProfileDialog(QWidget *parent)
{
    username = new QLabel(tr("Username: "));
    userEdit = new QLineEdit();
    username->setBuddy(userEdit);

    password = new QLabel(tr("Password: "));
    passEdit = new QLineEdit();
    passEdit->setEchoMode(QLineEdit::Password);
    password->setBuddy(passEdit);

    repeatPassword = new QLabel(tr("Repeat Password: "));
    repPassEdit = new QLineEdit();
    repPassEdit->setEchoMode(QLineEdit::Password);
    password->setBuddy(repPassEdit);

    registerUser = new QPushButton(tr("Register"));
    registerUser->setEnabled(false);
    abort = new QPushButton(tr("Cancel"));

    err = new QLabel("");

    QDialogButtonBox *buttonBox = new QDialogButtonBox();
    buttonBox->addButton(registerUser, QDialogButtonBox::ActionRole);
    buttonBox->addButton(abort, QDialogButtonBox::ActionRole);

    QVBoxLayout *layout = new QVBoxLayout();
    QFormLayout *formLayout = new QFormLayout();

    connect(registerUser, SIGNAL(clicked()), this, SLOT(registerPressed()));
    connect(abort, SIGNAL(clicked()), this, SLOT(abortPressed()));
    connect(passEdit, SIGNAL(textEdited(const QString &)), this, SLOT(comparePasswords()));
    connect(repPassEdit, SIGNAL(textEdited(const QString &)), this, SLOT(comparePasswords()));

    formLayout->addRow(username, userEdit);
    formLayout->setSpacing(15);
    formLayout->addRow(password, passEdit);
    formLayout->setSpacing(15);
    formLayout->addRow(repeatPassword, repPassEdit);
    layout->addItem(formLayout);
    layout->addSpacing(5);
    layout->addWidget(err);
    layout->setSpacing(10);
    layout->addWidget(buttonBox);
    setLayout(layout);
    setFixedSize(sizeHint());
    setModal(true);
}

void newProfileDialog::abortPressed(){
    close();
}

//TODO: SEND DATA TO SERVER
void newProfileDialog::registerPressed(){
    QString user = userEdit->text();
    QString pass = passEdit->text();
    if(user.isNull() || user.isEmpty()){
        err->setText("Username cannot be empty");
        err->setStyleSheet("QLabel {color: #FF0000}");
        return;
    }else{
        QFile settings(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile");
        settings.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&settings);
        out << "" << endl;
        out << user << endl;
        settings.close();
        close();
    }
}

void newProfileDialog::comparePasswords(){
    QString pass = passEdit->text();
    QString repPass = repPassEdit->text();

    if(repPass.isNull() || repPass.isEmpty())
        return;
    else{
        if(pass.compare(repPass)!= 0){
            err->setText("Passwords must match");
            err->setStyleSheet("QLabel {color: #FF0000}");
            this->repaint();
        }
        else{
            err->setText("");
            this->repaint();
            registerUser->setEnabled(true);
        }
    }

}
