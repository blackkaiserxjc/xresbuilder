find_package(ANTLR REQUIRED)
find_package(Boost REQUIRED)
find_package(msgpack REQUIRED)

set(ANTLR_OUTPUT_DIRS ${PROJECT_SOURCE_DIR}/libs/)
antlr_target(IDLGrammarParser IDL.g4 VISITOR OUTPUT_DIRECTORY ${ANTLR_OUTPUT_DIRS})
antlr_target(CellGrammarParser Cell.g4 VISITOR OUTPUT_DIRECTORY ${ANTLR_OUTPUT_DIRS})

include_directories(${ANTLR4_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${ANTLR_OUTPUT_DIRS})

set(kr_app_core_SRCS
    core.h
    core.cpp
    idl.h
    idl.cpp
    ast_builder.h 
    ast_builder.cpp
    code_generator.h
    code_generator.cpp
    rapidcsv.h
    data_set.h
    data_set.cpp
    object_pack.h
    pack.h
    type.h
    ${ANTLR_IDLGrammarParser_CXX_OUTPUTS}
    ${ANTLR_CellGrammarParser_CXX_OUTPUTS}
)

set(kr_app_core_detail_SRCS
    detail/ast_builder.h
    detail/msgpack.h
    detail/object_pack.h
)

set(kr_app_core_impl_SRCS
    impl/idl_gen_json.cpp
    impl/idl_gen_lua.cpp
)

add_library(kr_app_core
    ${kr_app_core_SRCS}
    ${kr_app_core_detail_SRCS}
    ${kr_app_core_impl_SRCS}
)

add_dependencies(kr_app_core
    antlr4_static
)


