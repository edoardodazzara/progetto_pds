#ifndef NEWPROFILEDIALOG_H
#define NEWPROFILEDIALOG_H

#include <QObject>
#include <QDialog>
#include <QVBoxLayout>
#include <QtWidgets>
#include <QFormLayout>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>

class QLabel;
class QLineEdit;
class QPushButton;

class newProfileDialog:public QDialog
{
    Q_OBJECT
public:
    newProfileDialog(QWidget *parent = 0);

public slots:
    void registerPressed();
    void abortPressed();
    void comparePasswords();

private:
    QLabel *username;
    QLabel *password;
    QLabel *repeatPassword;
    QPushButton *registerUser;
    QPushButton *abort;
    QLineEdit *userEdit;
    QLineEdit *passEdit;
    QLineEdit *repPassEdit;
    QLabel *err;
};

#endif // NEWPROFILEDIALOG_H
