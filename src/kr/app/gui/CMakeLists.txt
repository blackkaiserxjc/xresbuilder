find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(kr_app_builder_gui_SRCS
    dark_style.h
    dark_style.cpp
    filesystem_model.h
    filesystem_model.cpp
    main.cpp
    mainwindow.h
    mainwindow.cpp
)

set(kr_app_builder_gui_forms_SRCS	
	mainwindow.ui
	framelesswindow/framelesswindow.ui
)
source_group("Form Files" FILES ${kr_app_builder_gui_forms_SRCS})

set(kr_app_builder_gui_detail_SRCS	
	framelesswindow/framelesswindow.h
    framelesswindow/framelesswindow.cpp
	framelesswindow/windowdragger.h
    framelesswindow/windowdragger.cpp
)
source_group("Detail Files" FILES ${kr_app_builder_gui_detail_SRCS})
	
set(kr_app_builder_gui_rc_SRCS
	darkstyle.qrc
	framelesswindow.qrc
)
source_group("Resource Files" FILES ${kr_app_builder_gui_rc_SRCS})

qt5_add_resources(kr_app_builder_gui_SRCS darkstyle.qrc framelesswindow.qrc)

add_executable(kr_app_builder_gui WIN32
    ${kr_app_builder_gui_SRCS}
	${kr_app_builder_gui_detail_SRCS}
	${kr_app_builder_gui_forms_SRCS}
)

set_target_properties(kr_app_builder_gui
    PROPERTIES
    OUTPUT_NAME xresbuilder-gui
    FOLDER App
)

target_link_libraries(kr_app_builder_gui Qt5::Widgets Qt5::Core)
