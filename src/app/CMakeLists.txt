find_package(Boost REQUIRED)
find_package(Fmt REQUIRED)
find_package(ANTLR REQUIRED)
find_package(msgpack REQUIRED)

include_directories(${ANTLR4_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

# 源码
set(kr_app_builder_SRCS
    main.cpp
)
add_executable(kr_app_builder
    ${kr_app_builder_SRCS}
)

target_link_libraries(kr_app_builder
    kr_app_core
    antlr4_static
)