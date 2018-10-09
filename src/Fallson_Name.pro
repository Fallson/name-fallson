HEADERS=./inc/pfbottomctrlpane.h \
        ./inc/pfleftctrlpane.h \
        ./inc/pfprjctrlpane.h \
        ./inc/PhotoFrame.h \
        ./inc/PfCentPane.h \
        ./inc/PfPhotoEditView.h \
        ./inc/PFPhotoEditScene.h \
        ./inc/PFPhotoEditViewItem.h \
        ./inc/PFPhotoTextViewItem.h \
        ./inc/pfpaper.h \
        ./inc/AppCfg.h\
        ./inc/cnamefilter.h \
        ./inc/cpianpang.h \
        ./inc/cbook.h \
        ./inc/util.h \
        ./cme/cmeBMHPatMatch.h \
        ./cme/cmeKeyword.h \
        ./cme/cmeKeywordMatch.h \
        ./cme/cmeKRRPatMatch.h \
        ./cme/cmeTriePatMatch.h \
        ./cme/cmeErrCodeBasic.h \
        ./cme/cmeInt64Def.h \



SOURCES=./cpp/main.cpp \
        ./cpp/pfbottomctrlpane.cpp \
        ./cpp/pfleftctrlpane.cpp \
        ./cpp/pfprjctrlpane.cpp \
        ./cpp/PhotoFrame.cpp \
        ./cpp/PfCentPane.cpp \
        ./cpp/PfPhotoEditView.cpp \
        ./cpp/PFPhotoEditScene.cpp \
        ./cpp/PFPhotoEditViewItem.cpp \
        ./cpp/PFPhotoTextViewItem.cpp \
        ./cpp/pfpaper.cpp \
        ./cpp/AppCfg.cpp \
        ./cpp/cnamefilter.cpp \
        ./cpp/cpianpang.cpp \
        ./cpp/cbook.cpp \
        ./cpp/util.cpp\
        ./cme/cmeBMHPatMatch.c \
        ./cme/cmeKeyword.c \
        ./cme/cmeKeywordMatch.c \
        ./cme/cmeKRRPatMatch.c \
        ./cme/cmeTriePatMatch.c \

FORMS=./cpp/pfleftctrlpane.ui \
      ./cpp/pfprjctrlpane.ui \
      ./cpp/PhotoFrame.ui

# win32 {
#     SOURCES += hellowin.cpp
# }
# unix {
#     SOURCES += hellounix.cpp
# }
#macx{
#     SOURCES += hellomacx.cpp
# }

MOC_DIR = ./moc_tmps
OBJECTS_DIR = ./obj_tmps
RCC_DIR = ./rcc_tmps
UI_DIR = ./ui_tmps

RESOURCES     = Fallson_Name.qrc
win32:RC_FILE       = Fallson_Name.rc
macx:ICON          = ./res/images/AppIcon.icns

INCLUDEPATH += ./inc ./cme
#win32:LIBS += Winspool.lib User32.lib shell32.lib Dbghelp.lib Gdi32.lib
CONFIG += stl qt console
QT += xml


