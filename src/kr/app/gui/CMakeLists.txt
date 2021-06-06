find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(kr_app_builder_gui
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
)

set_target_properties(kr_app_builder_gui
    PROPERTIES
    OUTPUT_NAME xresbuilder-gui
    FOLDER App
)

target_link_libraries(kr_app_builder_gui Qt5::Widgets)
