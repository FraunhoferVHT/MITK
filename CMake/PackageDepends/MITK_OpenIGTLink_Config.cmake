
find_package(OpenIGTLink REQUIRED)

list(APPEND ALL_LIBRARIES ${OpenIGTLink_LIBRARIES})
list(APPEND ALL_INCLUDE_DIRECTORIES ${OpenIGTLink_INCLUDE_DIRS})
#string(REPLACE " " ";" _igtl_cxx_flags "${OpenIGTLink_REQUIRED_CXX_FLAGS}")
#list(APPEND ALL_COMPILE_OPTIONS ${_igtl_cxx_flags})
