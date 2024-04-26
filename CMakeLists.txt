# 设置CMake最低版本
cmake_minimum_required(VERSION 3.5)
# 设置项目名称
project(video_upload VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Core5Compat REQUIRED)
# 找到Q6的Network模块
find_package(Qt6 REQUIRED COMPONENTS Network)


set(PROJECT_SOURCES
        main.cpp
        videouploaddialog.cpp
        videouploaddialog.h
        videouploaddialog.ui
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(video_upload
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        mainwindow.h
        mainwindow.cpp
        mainwindow.ui
        common.h common.cpp
        createprojectdialog.h createprojectdialog.cpp createprojectdialog.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET video_upload APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(video_upload SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(video_upload
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(video_upload PUBLIC
    "${PROJECT_SOURCE_DIR}/lib/quazip/include/QuaZip-Qt6-1.4"
    "${PROJECT_SOURCE_DIR}/lib/zlib/include"
)
target_link_directories(video_upload PUBLIC
    "${PROJECT_SOURCE_DIR}/lib/quazip/lib"
    "${PROJECT_SOURCE_DIR}/lib/zlib/lib"
)

target_link_libraries(video_upload PRIVATE Qt${QT_VERSION_MAJOR}::Widgets "z" "quazip1-qt6")
target_link_libraries(video_upload PRIVATE Qt${QT_VERSION_MAJOR}::Network)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.video_upload)
endif()
set_target_properties(video_upload PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS video_upload
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(video_upload)
endif()
