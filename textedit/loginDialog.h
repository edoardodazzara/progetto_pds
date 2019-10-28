#ifndef LOGINDIAG_H
#define LOGINDIAG_H

#include <QDialog>
#include <QVBoxLayout>
#include "newprofiledialog.h"

class QLabel;
class QLineEdit;
class QPushButton;

class loginDialog : public QDialog{
    Q_OBJECT
public:
    loginDialog(QWidget *parent = 0);

private slots:
    void loginClicked();
    void cancelClicked();
    void enableLoginButton(const QString &text);
    void registerClicked();

signals:
    void loginSuccessful();


private:
    QLabel *username;
    QLabel *password;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *cancelButton;
    QPushButton *newProfileButton;
    newProfileDialog *newProfile;

};

#endif //LOGINDIAG_H
