QMAKE_CXXFLAGS += -std=c++11 -Wno-reorder

QT += gui core widgets xml multimedia sql

SOURCES += \
    main.cpp \
    ResourcesManager/XmlParser.cpp \
    ResourcesManager/ResourceManager.cpp \
    QTetrisCore/widget.cpp \
    QTetrisCore/TetrominoDataBase.cpp \
    QTetrisCore/Tetromino.cpp \
    QTetrisCore/SceneObject.cpp \
    QTetrisCore/Scene.cpp \
    QTetrisCore/NextTetrominoWidget.cpp \
    QTetrisCore/mainwindow.cpp \
    QTetrisCore/gameManager.cpp \
    MenuManager/menumanager.cpp \
    MenuManager/Menu.cpp \
    ExtraWidgets/Login.cpp \
    ExtraWidgets/highScores.cpp \
    ExtraWidgets/AudioController.cpp \
    AudioManager/AudioManager.cpp \
    ResourcesManager/Builder.cpp

OTHER_FILES += \
    QTetris.png \
    config.xml

HEADERS += \
    ResourcesManager/XmlParser.h \
    ResourcesManager/ResourceManager.h \
    QTetrisCore/widget.h \
    QTetrisCore/Tetromino.h \
    QTetrisCore/SceneObject.h \
    QTetrisCore/Scene.h \
    QTetrisCore/NextTetrominoWidget.h \
    QTetrisCore/mainwindow.h \
    QTetrisCore/gameManager.h \
    MenuManager/menumanager.h \
    MenuManager/MenuInterface.h \
    MenuManager/Menu.h \
    MenuManager/Launcher.h \
    ExtraWidgets/Login.h \
    ExtraWidgets/highScores.h \
    ExtraWidgets/AudioController.h \
    AudioManager/AudioManager.h \
    ResourcesManager/Builder.h

FORMS += \
    ExtraWidgets/Login.ui \
    ExtraWidgets/highscores.ui

