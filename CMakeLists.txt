cmake_minimum_required(VERSION 3.16)

project(HelloQt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)
find_package(jsoncpp CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBAVFORMAT REQUIRED IMPORTED_TARGET libavformat)
pkg_check_modules(LIBAVCODEC REQUIRED IMPORTED_TARGET libavcodec)
pkg_check_modules(LIBAVUTIL REQUIRED IMPORTED_TARGET libavutil)
pkg_check_modules(LIBSWSCALE IMPORTED_TARGET libswscale)
pkg_check_modules(LIBSWRESAMPLE IMPORTED_TARGET libswresample)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)

qt_standard_project_setup()

qt_add_executable(HelloQt
    main.cpp
    mainwindow.h
    mainwindow.cpp
    entrypage.h
    entrypage.cpp
    entrypage.ui
    catalogpage.h
    catalogpage.cpp
    catalogpage.ui
    tcpclient.h
    tcpclient.cpp
)

target_link_libraries(HelloQt PRIVATE
    Qt6::Widgets
    Qt6::Network
    JsonCpp::JsonCpp
    PkgConfig::LIBAVFORMAT
    PkgConfig::LIBAVCODEC
    PkgConfig::LIBAVUTIL
    PkgConfig::SDL2
)

if(TARGET PkgConfig::LIBSWSCALE)
    target_link_libraries(HelloQt PRIVATE PkgConfig::LIBSWSCALE)
endif()

if(TARGET PkgConfig::LIBSWRESAMPLE)
    target_link_libraries(HelloQt PRIVATE PkgConfig::LIBSWRESAMPLE)
endif()