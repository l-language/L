cmake_minimum_required (VERSION 3.8)
project ("L")

set(CMAKE_CXX_STANDARD 17)
set(L_VERSION_MAJOR 0)
set(L_VERSION_MINOR 0)
set(L_VERSION_PATCH 5)

include(InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
  "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${L_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${L_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${L_VERSION_PATCH}")
include(CPack)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/src/L/version.cpp.in" 
  "${CMAKE_CURRENT_SOURCE_DIR}/src/L/version.cpp"
)

add_subdirectory(./lib/gflags)
add_subdirectory(./lib/glog)
include_directories(./lib/glog/src)
include_directories(./lib/gflags/src)
include_directories(${CMAKE_BINARY_DIR}/lib/glog)
include_directories(${CMAKE_BINARY_DIR}/lib/gflags)
include_directories(include)
file(GLOB_RECURSE libL_SOURCES CONFIGURE_DEPENDS src/L/*.cpp)
add_library(libL OBJECT ${libL_SOURCES})
add_executable(L src/L.cpp $<TARGET_OBJECTS:libL>)
target_link_libraries(L glog)
target_link_libraries(L gflags)