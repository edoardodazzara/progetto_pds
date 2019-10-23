QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

TEMPLATE        = app
TARGET          = textedit

HEADERS         = textedit.h \
    clickablelabel.h \
    editprofile.h \
    loginDialog.h
SOURCES         = textedit.cpp \
                  clickablelabel.cpp \
                  editprofile.cpp \
                  loginDialog.cpp \
                  main.cpp

RESOURCES += textedit.qrc
build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

EXAMPLE_FILES = textedit.qdoc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/richtext/textedit
INSTALLS += target
