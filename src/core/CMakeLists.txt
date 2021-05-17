find_package(ANTLR REQUIRED)
find_package(Boost REQUIRED)

set(ANTLR_OUTPUT_DIRS ${PROJECT_SOURCE_DIR}/libs/)
antlr_target(FieldGrammarParser IDL.g4 VISITOR OUTPUT_DIRECTORY ${ANTLR_OUTPUT_DIRS})

include_directories(${ANTLR4_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${ANTLR_OUTPUT_DIRS})

set(kr_app_core_SRCS
    idl.h
    idl.cpp
    ${ANTLR_FieldGrammarParser_CXX_OUTPUTS}
)

add_library(kr_app_core
    ${kr_app_core_SRCS}
)

add_dependencies(kr_app_core
    antlr4_static
)


