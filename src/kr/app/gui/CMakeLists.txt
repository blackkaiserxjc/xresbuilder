find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Toml REQUIRED)

include_directories(${TOML_INCLUDE_DIRS})
include_directories(framelesswindow)


set(kr_app_builder_gui_CONFIGS
    config.ini
)
set(kr_app_builder_gui_OUTPUT_CONFIGS)
foreach(cfgFile ${kr_app_builder_gui_CONFIGS})
    list(APPEND kr_app_builder_gui_OUTPUT_CONFIGS "${CMAKE_CURRENT_BINARY_DIR}/${cfgFile}")
    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${cfgFile}"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${cfgFile}" "${CMAKE_CURRENT_BINARY_DIR}/${cfgFile}"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${cfgFile}
        COMMENT "Generaton Config ${cfgFile}"
    )
endforeach() 
source_group("Output Files" FILES ${kr_app_builder_gui_OUTPUT_CONFIGS})
source_group("Config Files" FILES ${kr_app_builder_gui_CONFIGS})


set(kr_app_builder_gui_SRCS
    dark_style.h
    dark_style.cpp
    fsmodel.h
    fsmodel.cpp
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

add_executable(kr_app_builder_gui
    ${kr_app_builder_gui_SRCS}
	${kr_app_builder_gui_detail_SRCS}
	${kr_app_builder_gui_forms_SRCS}
    ${kr_app_builder_gui_CONFIGS}
    ${kr_app_builder_gui_OUTPUT_CONFIGS}
)

set_target_properties(kr_app_builder_gui
    PROPERTIES
    OUTPUT_NAME xresbuilder-gui
    FOLDER App
)

target_link_libraries(kr_app_builder_gui Qt5::Widgets Qt5::Core)
