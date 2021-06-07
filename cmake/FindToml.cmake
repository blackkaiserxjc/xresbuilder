# Find toml library
# Find the toml includes
#
# TOML_INCLUDE_DIRS - where to find toml.hpp, etc.
# TOML_FOUND - True if toml found.

find_path(TOML_INCLUDE_DIRS NAMES cpptoml.h)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(toml DEFAULT_MSG TOML_INCLUDE_DIRS)

mark_as_advanced(TOML_INCLUDE_DIRS)