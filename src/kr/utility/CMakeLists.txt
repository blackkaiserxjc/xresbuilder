set(kr_app_utility_SRCS
    utility.h
    utility.cpp
)

add_library(kr_app_utility
    ${kr_app_utility_SRCS}
)

set_target_properties(kr_app_utility PROPERTIES FOLDER App)