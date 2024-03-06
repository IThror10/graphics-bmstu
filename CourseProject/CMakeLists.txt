cmake_minimum_required(VERSION 3.5)

project(CourseProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES CourseProject_ru_RU.ts)

set(PROJECT_SOURCES
        main.cpp
        programwindow.cpp
        programwindow.h
        programwindow.ui

        Meta/settings.h
        Meta/settings.cpp

        #______Фабрика и элементы интерфейса______
        Interface/abstractFactory.h
        Interface/abstractFactory.cpp
        Interface/QtFactory.h
        Interface/QtFactory.cpp

        #Сцена
        Interface/scene/baseScene.h
        Interface/scene/baseScene.cpp

        #Кнопки
        Interface/button/pushButton.h
        Interface/button/pushButton.cpp
        Interface/button/qtButton.h
        Interface/button/qtButton.cpp

        #Меню
        Interface/menu/canvasMenu.h
        Interface/menu/canvasMenu.cpp
        Interface/menu/qtCanvasMenu.h
        Interface/menu/qtCanvasMenu.cpp

        #Холст
        Interface/canvas/baseCanvas.h
        Interface/canvas/baseCanvas.cpp
        Interface/canvas/qtCanvas.h
        Interface/canvas/qtCanvas.cpp

        #Посредник холста и сцены
        mediator/canvasMediator.h
        mediator/canvasMediator.cpp
        mediator/flatCanvasMediator.h
        mediator/flatCanvasMediator.cpp
        mediator/spaceCanvasMediator.h
        mediator/spaceCanvasMediator.cpp

        #Пользовательские диалоги
        Interface/dialog/user_dialog.h
        Interface/dialog/user_dialog.cpp

        #___Художник___
        Painter/molPainter.h
        Painter/molPainter.cpp
        Painter/PainterImp.h
        Painter/QtPainterImp.h
        Painter/qtPainterImp.cpp

        #Стратегии
        strategy/action/actionStrategy.h
        strategy/action/actionStrategy.cpp
        strategy/action/moveStrategy.h
        strategy/action/moveStrategy.cpp
        strategy/action/removeStrategy.h
        strategy/action/removeStrategy.cpp
        strategy/action/placeFigureAction.h
        strategy/action/placeFigureAction.cpp
        strategy/action/LineAtomAction.h
        strategy/action/lineSwapAction.h
        strategy/action/lineSwapAction.cpp
        strategy/action/placeSelectedAction.h
        strategy/action/placeSelectedAction.cpp

        strategy/select/selectStrategy.h
        strategy/select/selectStrategy.cpp

        #Координаты
        Core/spaceCoords.h
        Core/spaceCoords.cpp
        Core/flatCoords.h
        Core/flatCoords.cpp
        Core/rgbColor.h
        Core/rgbColor.cpp
        Core/node_list.h
        Core/node_list.cpp

        #___Базовые объекты___
        Objects/baseObject.h
        Objects/baseObject.cpp
        Objects/atomObject.h
        Objects/atomObject.cpp
        Objects/lineObject.h
        Objects/lineObject.cpp
        Objects/compositObject.h
        Objects/compositObject.cpp

        #Visitor для объектов
        Objects/baseVisitor.h
        Objects/distanceVisitor.h
        Objects/distanceVisitor.cpp
        Objects/drawVisitor.h
        Objects/drawVisitor.cpp
        Objects/moveVisitor.h
        Objects/moveVisitor.cpp

        ############
        ############
        builder/builder.h
        builder/builder.cpp
        builder/springBuilder.h
        builder/springBuilder.cpp
        builder/director.h
        builder/director.cpp
        ############
        ############
        model/command_main.h
        model/command_main.cpp

        model/myMath/my_math.h
        model/myMath/my_math.cpp

        model/image/image.h
        model/image/image.cpp

        model/inc/atom.h
        model/inc/atom.cpp
        model/inc/connection.h
        model/inc/connection.cpp
        model/inc/status.h
        model/inc/sphere.h
        model/inc/sphere.cpp
        model/inc/camera.h
        model/inc/camera.cpp
        model/inc/matrix4x4.h
        model/inc/matrix4x4.cpp

        model/instruction/moving.h
        model/instruction/moving.cpp
        model/instruction/drawing.h
        model/instruction/drawing.cpp
        model/instruction/scaling.h
        model/instruction/scaling.cpp
        model/instruction/rotating.h
        model/instruction/rotating.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CourseProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(CourseProject SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(CourseProject
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(CourseProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(CourseProject PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CourseProject)
endif()
