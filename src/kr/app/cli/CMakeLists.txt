find_package(ANTLR REQUIRED)
find_package(Boost COMPONENTS program_options system thread REQUIRED)
find_package(Msgpack REQUIRED)
find_package(Threads REQUIRED)
find_package(fmt REQUIRED)
find_package(Xlnt REQUIRED)


include_directories(${ANTLR4_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${MSGPACK_INCLUDE_DIRS})

# 源码
set(kr_app_builder_SRCS
    main.cpp
)
add_executable(kr_app_builder_cli
    ${kr_app_builder_SRCS}
)

set_target_properties(kr_app_builder_cli
    PROPERTIES
    OUTPUT_NAME xresbuilder-cli
    FOLDER App
)

target_link_libraries(kr_app_builder_cli
    kr_app_core
    kr_app_utility
    antlr4_shared
    fmt::fmt
    xlnt::xlnt
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
)
