find_package(ANTLR REQUIRED)
find_package(Boost COMPONENTS program_options system thread REQUIRED)
find_package(Fmt CONFIG REQUIRED)
find_package(Threads)

include_directories(${ANTLR4_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${MSGPACK_INCLUDE_DIRS})
include_directories(${FMT_INCLUDE_DIRS})

# 源码
set(kr_app_builder_SRCS
    main.cpp
)
add_executable(kr_app_builder
    ${kr_app_builder_SRCS}
)

target_link_libraries(kr_app_builder
    kr_app_core
    kr_app_utility
    antlr4_static
	${FMT_LIBRARYS}
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
)