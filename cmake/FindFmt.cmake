find_path(FMT_INCLUDE_DIRS NAMES fmt/core.h)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_library(FMT_LIBRARYS NAMES fmtd)
else ()
    find_library(FMT_LIBRARYS NAMES fmt)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(fmt DEFAULT_MSG FMT_INCLUDE_DIRS FMT_LIBRARYS)

mark_as_advanced(FMT_INCLUDE_DIRS FMT_LIBRARYS)