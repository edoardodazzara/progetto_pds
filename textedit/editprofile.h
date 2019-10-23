#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QFileInfo>
#include <QFile>
#include <QHoverEvent>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDialogButtonBox>
#include <QTextStream>
#include <QMessageBox>

#include "clickablelabel.h"

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
    const QString rsrc = ":/images/win";
    QLabel *nickname;
    QLabel *username;
    ClickableLabel *userPic;
    QPixmap *profilePic;
    QLineEdit *usernameEdit;
    QLineEdit *nickEdit;
    QPushButton *save;
    QPushButton *discard;

};

#endif // EDITPROFILE_H
