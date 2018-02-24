QT += qml quickcontrols2 network

CONFIG += c++17
CONFIG += object_parallel_to_source
CONFIG += resources_big
CONFIG += no_batch

INCLUDEPATH += include/
TARGET = DNAI

CONFIG(release, debug|release) {
win32:RC_FILE = dnai.rc
unix:ICON = DNAI_icon.icns
}


#INSTALLS += settingsfolderconf

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS QNANO_USE_RENDERNODE
DEFINES += QPM_INIT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#CORE
SOURCES += \
    src/main.cpp \
    src/dnai/baseio.cpp \
    src/dnai/link.cpp \
    src/dnai/eventutilities.cpp \
    src/dnai/focusmanager.cpp \
    src/dnai/baselinkable.cpp \
    src/dnai/manager.cpp \
    src/dnai/project.cpp \
    src/dnai/app.cpp \
    src/dnai/settings.cpp \
    src/dnai/processmanager.cpp \
    src/dnai/entitiesfactory.cpp \
    src/dnai/commands/entitydeclare.cpp \
    src/dnai/appcontext.cpp \
    src/dnai/session.cpp \
    src/dnai/models/property.cpp \
    src/dnai/models/entity.cpp \
    src/dnai/controllers/propertypanel.cpp \
    src/dnai/commands/openpropertypanel.cpp \
    src/dnai/viewshandler.cpp


#COMMANDS
SOURCES += \
    src/dnai/commands/movecommand.cpp \
    src/dnai/commands/movenodecommand.cpp \
    src/dnai/commands/movecanvascommand.cpp \
    src/dnai/commands/zoomcanvascommand.cpp

#VIEWS
SOURCES += \
    src/dnai/views/beziercurve.cpp \
    src/dnai/views/customshape.cpp \
    src/dnai/views/flow.cpp \
    src/dnai/views/genericnode.cpp \
    src/dnai/views/input.cpp \
    src/dnai/views/io.cpp \
    src/dnai/views/line.cpp \
    src/dnai/views/linkablebezieritem.cpp \
    src/dnai/views/output.cpp \
    src/dnai/views/roundedrectangle.cpp \
    src/dnai/views/console.cpp \
    src/dnai/views/class.cpp \
    src/dnai/views/declarationview.cpp \
    src/dnai/views/declarationcanvas.cpp \
    src/dnai/views/contextview.cpp \
    src/dnai/views/appview.cpp \
    src/dnai/views/instructionview.cpp \
    src/dnai/views/canvasnode.cpp \
    src/dnai/views/layout.cpp

#COMMANDS
SOURCES += \
    src/dnai/commands/commanddecorator.cpp \
    src/dnai/commands/commandmanager.cpp \
    src/dnai/commands/debugdecorator.cpp \
    src/dnai/commands/command.cpp \


#CONTROLLERS
SOURCES += \
    src/dnai/controllers/inputcontroller.cpp \
    src/dnai/controllers/outputcontroller.cpp \
    src/dnai/controllers/consolecontroller.cpp \
    src/dnai/controllers/clientcontroller.cpp \
    src/dnai/controllers/icontroller.cpp \
    src/dnai/controllers/contextcontroller.cpp


#MODELS
SOURCES += src/dnai/models/class.cpp \
    src/dnai/models/common.cpp \
    src/dnai/models/context.cpp \
    src/dnai/models/flow.cpp \
    src/dnai/models/function.cpp \
    src/dnai/models/identity.cpp \
    src/dnai/models/input.cpp \
    src/dnai/models/node.cpp \
    src/dnai/models/output.cpp \
    src/dnai/models/variable.cpp \
    src/dnai/models/position.cpp \
    src/dnai/models/user.cpp \
    src/dnai/models/declarationmodel.cpp \
    src/dnai/models/basicnodemodel.cpp \
    src/dnai/models/treemodel.cpp \
    src/dnai/models/treeitem.cpp \
    src/dnai/models/namespacebarmodel.cpp \
    src/dnai/models/namespacebaritem.cpp \
    src/dnai/models/settingsmodel.cpp \
    src/dnai/models/listnode.cpp
#HTTP
SOURCES += \
    src/dnai/http/url.cpp \
    src/dnai/http/service.cpp \
    src/dnai/http/observable.cpp \
    src/dnai/http/response.cpp

#API
SOURCES += src/dnai/api/api.cpp

#QMLRESOURCES
SOURCES += src/dnai/qmlresources/qcstandardpaths.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /usr/local/bin/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

FORMS += \
    resources/Forms/BasePanelForm.ui

#GENERAL HEADER
HEADERS += \
    include/views.h \
    include/api.h \
    include/models.h \
    include/qmlresources.h \
    include/controllers.h \
    include/commands.h \
    include/http.h \
    include/dnai/app.h \
    include/dnai/settings.h \
    include/dnai/entitiesfactory.h \
    include/dnai/iloadingclass.h \
    include/dnai/iobservable.h \
    include/dnai/commands/entitydeclare.h \
    include/dnai/appcontext.h \
    include/dnai/models/property.h \
    include/dnai/controllers/propertypanel.h \
    include/dnai/commands/openpropertypanel.h \
    include/dnai/session.h \
    include/dnai/models/entity.h \
    include/dnai/ifactory.h \
    include/dnai/viewshandler.h


#DNAI
HEADERS += \
    include/dnai/baseio.h \
    include/dnai/baselinkable.h \
    include/dnai/eventutilities.h \
    include/dnai/focusmanager.h \
    include/dnai/ilinkable.h \
    include/dnai/link.h \
    include/dnai/linkabletype.h \
    include/dnai/manager.h \
    include/dnai/project.h \
    include/dnai/processmanager.h \

#VIEWS
HEADERS += \
    include/dnai/views/beziercurve.h \
    include/dnai/views/customshape.h \
    include/dnai/views/flow.h \
    include/dnai/views/genericnode.h \
    include/dnai/views/input.h \
    include/dnai/views/io.h \
    include/dnai/views/iscalable.h \
    include/dnai/views/line.h \
    include/dnai/views/linkablebezieritem.h \
    include/dnai/views/output.h \
    include/dnai/views/roundedrectangle.h \
    include/dnai/views/console.h \
    include/dnai/views/class.h \
    include/dnai/views/declarationview.h \
    include/dnai/views/declarationcanvas.h \
    include/dnai/views/contextview.h \
    include/dnai/views/appview.h \
    include/dnai/views/instructionview.h \
    include/dnai/views/layout.h \
    include/dnai/views/canvasnode.h \

#COMMANDS
HEADERS += \
    include/dnai/commands/commanddecorator.h \
    include/dnai/commands/commandmanager.h \
    include/dnai/commands/debugdecorator.h \
    include/dnai/commands/icommand.h \
    include/dnai/commands/command.h \
    include/dnai/commands/movenodecommand.h \
    include/dnai/commands/movecommand.h \


#CONTROLLERS
HEADERS += \
    include/dnai/controllers/inputcontroller.h \
    include/dnai/controllers/outputcontroller.h \
    include/dnai/controllers/consolecontroller.h \
    include/dnai/controllers/clientcontroller.h \
    include/dnai/controllers/icontroller.h \
    include/dnai/controllers/contextcontroller.h \

#MODELS
HEADERS += \
    include/dnai/models/common.h \
    include/dnai/models/context.h \
    include/dnai/models/class.h \
    include/dnai/models/node.h \
    include/dnai/models/variable.h \
    include/dnai/models/input.h \
    include/dnai/models/output.h \
    include/dnai/models/flow.h \
    include/dnai/models/function.h \
    include/dnai/models/identity.h \
    include/dnai/models/imodel.h \
    include/dnai/models/iclone.h \
    include/dnai/models/position.h \
    include/dnai/models/user.h \
    include/dnai/models/treemodel.h \
    include/dnai/models/treeitem.h \
    include/dnai/models/namespacebarmodel.h \
    include/dnai/models/namespacebaritem.h \
    include/dnai/models/declarationmodel.h \
    include/dnai/models/basicnodemodel.h \
    include/dnai/models/settingsmodel.h \
    include/dnai/models/listnode.h \

#QMLRESOURCES
HEADERS += \
    include/dnai/qmlresources/instructionid.h \
    include/dnai/qmlresources/declarationtype.h \
    include/dnai/qmlresources/flowtype.h \
    include/dnai/qmlresources/iotype.h \
    include/dnai/qmlresources/qcstandardpaths.h \

#HTTP
HEADERS += \
    include/dnai/http/url.h \
    include/dnai/http/service.h \
    include/dnai/http/config.h \
    include/dnai/http/observable.h \
    include/dnai/http/response.h \
    include/dnai/http/types.h

#API
HEADERS += \
    include/dnai/api/api.h

#TEST
HEADERS += \
    include/testconnection.h \

#LIB
DEPENDPATH += $${PWD}/../lib/event_client/
INCLUDEPATH += $${PWD}/../lib/event_client/

INCLUDEPATH += $${PWD}/../lib/DataComEvent/Shared_include/

#begin library network
LIBS += -L$${PWD}/../lib/ -lEventClient -lDataComEvent

#CONFIG(release, debug|release) {
#unix:LIBS += -L$${PWD}/../lib/DataComEvent/Library/ -lprotobuf
#win32:LIBS += -L$${PWD}/../lib/DataComEvent/Library/ -llibprotobuf
#}
#CONFIG(debug, debug|release) {
#unix:LIBS += -L$${PWD}/../lib/DataComEvent/Library/ -lprotobuf
#win32:LIBS += -L$${PWD}/../lib/DataComEvent/Library/ -llibprotobufd
#}

#end library Data Event

win32:settingsfolder.path = $${OUT_PWD}/settings
unix:settingsfolder.path = /usr/local/bin/$${TARGET}/bin/$${TARGET}.app/Contents/MacOS/settings
settingsfolder.files = settings/*

#settingsfolderconf.path = $${OUT_PWD}/settings/conf
#settingsfolderconf.files = settings/conf/*/*

INSTALLS += settingsfolder
