#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPixmap>
#include <QFileInfo>
#include <QFile>
#include <QDialogButtonBox>

class editProfile:public QDialog
{
    Q_OBJECT
public:
    editProfile(QWidget *parent = 0);
    void edit();
private slots:
    void savePressed();
    void discardPressed();
    void selectImagePressed();
\

private:
    QLabel *nickname;
    QLabel *username;
    QPixmap *profilePic;
    QLineEdit *usernameEdit;
    QLineEdit *nickEdit;
    QPushButton *save;
    QPushButton *discard;

};

#endif // EDITPROFILE_H
