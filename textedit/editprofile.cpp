#include "editprofile.h"

editProfile::editProfile(QWidget *parent)
{
    setWindowTitle("User Profile editor");
    username = new QLabel(tr("&Username: "));
    nickname = new QLabel(tr("&Nickname: "));
    usernameEdit = new QLineEdit();
    nickEdit = new QLineEdit();
    profilePic = new QPixmap();
    username->setBuddy(usernameEdit);
    nickname->setBuddy(usernameEdit);
    save = new QPushButton(tr("&Save"));
    discard= new QPushButton(tr("&Discard"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(save, QDialogButtonBox::ApplyRole);
    buttonBox->addButton(discard, QDialogButtonBox::RejectRole);
    setModal(true);

    if(QFileInfo::exists("settings.profile")){
        QFile settings("settings.profile");
        settings.open(QIODevice::ReadWrite);
    }
}

void edit(){

}
