# Find msgpack library
# Find the msgpack includes
#
# MSGPACK_INCLUDE_DIRS - where to find msgpack.hpp, etc.
# MSGPACK_LIBRARIES - where to find msgpack, etc.
# MSGPACK_FOUND - True if msgpack found.

find_path(MSGPACK_INCLUDE_DIRS NAMES msgpack.hpp)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(msgpack DEFAULT_MSG MSGPACK_INCLUDE_DIRS)

mark_as_advanced(MSGPACK_INCLUDE_DIRS)