#include "editprofile.h"

editProfile::editProfile(QWidget *parent)
{
    if(!QDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/").exists()){
        QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/");
    }
    setWindowTitle("User Profile editor");
    username = new QLabel(tr("&Username: "));
    nickname = new QLabel(tr("&Nickname: "));
    usernameEdit = new QLineEdit();
    usernameEdit->setEnabled(false);
    nickEdit = new QLineEdit();
    userPic = new ClickableLabel();
    userPic->setBackgroundRole(QPalette::Dark);
    userPic->setScaledContents(false);
    profilePic = new QPixmap();
    profilePic->load(rsrc+"/profile-empty-pic.png");
    userPic->setPixmap(*profilePic);
    username->setBuddy(usernameEdit);
    nickname->setBuddy(usernameEdit);

    if(QFileInfo::exists(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile")){
        QFile settings(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile");
        settings.open(QIODevice::ReadOnly);
        QString proPicName = settings.readLine();
        QString usernameData = settings.readLine();
        QString nicknameData = settings.readLine();
        proPicName.resize(proPicName.size() - 2);
        usernameData.resize(usernameData.size() - 2);
        nicknameData.resize(nicknameData.size() - 2);
        settings.close();
        usernameEdit->setText(usernameData);
        usernameEdit->setEnabled(false);

        if(!nicknameData.isEmpty()){
            nickEdit->setText(nicknameData);
        }else{
            nickEdit->setStyleSheet("QLineEdit {color: #636363;}");
            nickEdit->setText(tr("(Optional)"));
        }
        profilePic->load(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/"+proPicName);
        QPixmap scaled = profilePic->scaled(147, 200, Qt::AspectRatioMode::KeepAspectRatio);
        userPic->setPixmap(scaled);
    }

    save = new QPushButton(tr("&Save"));
    discard= new QPushButton(tr("&Discard"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(save, QDialogButtonBox::ApplyRole);
    buttonBox->addButton(discard, QDialogButtonBox::RejectRole);
    setModal(true);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(userPic);
    layout->setAlignment(userPic,Qt::AlignCenter);
    layout->setSpacing(15);
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(username, usernameEdit);
    formLayout->addRow(nickname, nickEdit);
    layout->addLayout(formLayout);
    layout->addWidget(buttonBox);
    layout->setAlignment(buttonBox, Qt::AlignCenter);
    setLayout(layout);
    setMinimumSize(200, 300);

    connect(discard, SIGNAL(clicked()), this, SLOT(discardPressed()));
    connect(save, SIGNAL(clicked()), this, SLOT(savePressed()));
    connect(userPic, SIGNAL(clicked()), this, SLOT(selectImagePressed()));
    connect(nickEdit, SIGNAL(textEdited(const QString &)), this, SLOT(changedNick(const QString &)));
    connect(userPic, SIGNAL(hovered()), this, SLOT(imageHovered()));
    connect(userPic, SIGNAL(unHovered()), this, SLOT(imageUnhovered()));


}

void editProfile::changedNick(const QString &){

   QString nick = nickEdit ->text();
   nickEdit->setStyleSheet("QLineEdit {color: #000000;}");
   if(!nick.isEmpty()){
        if(QFile(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile.temp").exists()){

                QFile settings(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile.temp");
                settings.open(QIODevice::ReadWrite | QIODevice::Text);
                QString imageName = settings.readLine();
                QString username = settings.readLine();
                settings.resize(0);
                QTextStream out(&settings);
                out << imageName;
                out << username;
                out << nick << endl;
                settings.close();
                nickEdit->setText(nick);

            }else{
                QFile settings(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile.temp");
                settings.open(QIODevice::WriteOnly | QIODevice::Text);
                QTextStream out(&settings);
                out << "" << endl;
                out << "" << endl;
                out << nick << endl;
                settings.close();
                nickEdit->setText(nick);
            }
    }
}

void editProfile::savePressed(){
    QFile settingsOld(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile");
    QFile settings(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile.temp");
    settingsOld.open(QIODevice::ReadWrite | QIODevice::Text);
    settings.open(QIODevice::ReadOnly | QIODevice::Text);
    QString picOld = settingsOld.readLine();
    QString usOld = settingsOld.readLine();
    QString nickOld = settingsOld.readLine();
    picOld.resize(picOld.size() - 1);
    usOld.resize(usOld.size() - 1);
    nickOld.resize(nickOld.size() - 1);

    QString picNew = settings.readLine();
    QString usNew = settings.readLine();
    QString nickNew = settings.readLine();
    picNew.resize(picNew.size() - 1);
    usNew.resize(usNew.size() - 1);
    nickNew.resize(nickNew.size() - 1);
    settingsOld.resize(0);

    QTextStream out(&settingsOld);
    if(!(picOld.compare(picNew) == 0) && (picNew.compare("")!=0))
        out << picNew << endl;
    else
        out << picOld << endl;

    if(!(usOld.compare(usNew) == 0) && (usNew.compare("")!=0))
        out << usNew << endl;
    else
        out << usOld << endl;

    if(!(nickOld.compare(nickNew) == 0) && (nickNew.compare("")!=0))
        out << nickNew << endl;
    else
        out << nickOld << endl;

    settingsOld.close();
    settings.close();

    QFile::remove(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile.temp");
    close();
}

void editProfile::discardPressed(){
    QFile::remove(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile.temp");
    close();
}

void editProfile::selectImagePressed(){
    QUrl imageUrl = QFileDialog::getOpenFileUrl(this, tr("Open Image"), QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), tr("Image Files (*.png *.jpg *.bmp)"));
    QString imagePath = imageUrl.path();
    imagePath.remove(0,1);
    QString imageName = imageUrl.fileName();
    if(!imagePath.isEmpty() || !imagePath.isNull()){
        if(QDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/").exists()){
            QFile::copy(imagePath, QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/"+imageName);
        }else{
            QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/");
            QFile::copy(imagePath, QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/"+imageName);
        }
        if(QFile(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile.temp").exists()){

            QFile settings(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile.temp");
            settings.open(QIODevice::ReadWrite | QIODevice::Text);
            settings.readLine();
            QString username = settings.readLine();
            QString nickname = settings.readLine();
            settings.resize(0);
            QTextStream out(&settings);
            out << imageName << endl;
            out << username << endl;
            out << nickname << endl;
            settings.close();

        }else{
            QFile settings(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile.temp");
            settings.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&settings);
            out << imageName << endl;
            out << "" << endl;
            out << "" << endl;
            settings.close();
        }

        profilePic->load(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/"+imageName);
        QPixmap scaled = profilePic->scaled(147, 200, Qt::AspectRatioMode::KeepAspectRatio);
        userPic->setPixmap(scaled);
    }
}

void editProfile::imageHovered(){
    profilePic->load(rsrc+"/add-profile-image.png");
    //QPixmap scaled = profilePic->scaled(120, 200, Qt::AspectRatioMode::KeepAspectRatio);
    userPic->setPixmap(*profilePic);
}

void editProfile::imageUnhovered(){
    QFile settings(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/settings.profile");
    settings.open(QIODevice::ReadOnly);
    QString proPicName = settings.readLine();
    proPicName.resize(proPicName.size() - 2);
    settings.close();
    profilePic->load(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/CollaborativeEditor/usrData/"+proPicName);
    QPixmap scaled = profilePic->scaled(147, 200, Qt::AspectRatioMode::KeepAspectRatio);
    userPic->setPixmap(scaled);

}
