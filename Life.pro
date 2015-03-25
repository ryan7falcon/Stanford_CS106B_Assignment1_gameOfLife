TEMPLATE = app

# Make sure we do not accidentally #include files placed in 'resources'
CONFIG += no_include_pwd
#CONFIG += static
#CONFIG += staticlib

SOURCES = $$PWD/src/*.cpp
SOURCES += $$PWD/lib/StanfordCPPLib/*.cpp
HEADERS = $$PWD/src/*.h
HEADERS += $$PWD/lib/StanfordCPPLib/*.h

QMAKE_CXXFLAGS += -std=c++11
#QMAKE_CXXFLAGS += -lpthread
#QMAKE_LFLAGS += -static
#QMAKE_LFLAGS += -static-libgcc
#QMAKE_LFLAGS += -static-libstdc++

INCLUDEPATH += $$PWD/lib/StanfordCPPLib/

# Copies the given files to the destination directory
defineTest(copyToDestdir) {
    files = $$1

    for(FILE, files) {
        DDIR = $$OUT_PWD

        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        !win32 {
            QMAKE_POST_LINK += cp -r '"'$$FILE'"' '"'$$DDIR'"' $$escape_expand(\\n\\t)
        }
        win32 {
            QMAKE_POST_LINK += xcopy '"'$$FILE'"' '"'$$DDIR'"' /e /y $$escape_expand(\\n\\t)
        }
    }

    export(QMAKE_POST_LINK)
}
!win32 {
    copyToDestdir($$files($$PWD/res/*))
    copyToDestdir($$files($$PWD/lib/*.jar))
}
win32 {
    copyToDestdir($$PWD/res)
    copyToDestdir($$PWD/lib/*.jar)
}

OTHER_FILES += \
    src/simple.txt \
    res/diehard.txt \
    res/dinner-table.txt \
    res/fish.txt \
    res/flower.txt \
    res/glider-explosion.txt \
    res/glider-gun.txt \
    res/glider.txt \
    res/mycolony.txt \
    res/quilt-square.txt \
    res/rpent.txt \
    res/seeds.txt \
    res/simple.txt \
    res/snowflake.txt \
    res/spiral.txt \
    res/stableplateau.txt \
    res/tictactoe.txt
