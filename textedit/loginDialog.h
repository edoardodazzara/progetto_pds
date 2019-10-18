#ifndef LOGINDIAG_H
#define LOGINDIAG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class loginDialog : public QDialog{
    Q_OBJECT
public:
    loginDialog(QWidget *parent = 0);

private slots:
    void loginClicked(QString name, QString pass);
    void cancelClicked();
    void enableLoginButton(const QString &text);

private:
    QLabel *username;
    QLabel *password;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *cancelButton;

};

#endif //LOGINDIAG_H
