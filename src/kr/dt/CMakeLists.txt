find_package(Boost REQUIRED)

include_directories(${BOOST_INCLUDE_DIRES})

set(kr_app_dt_SRCS
    data_row.h
    data_row.cpp
    data_table.h
    data_table.cpp
    rapidcsv.h
)

add_library(kr_app_dt
    ${kr_app_dt_SRCS}
)

