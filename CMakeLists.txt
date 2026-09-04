cmake_minimum_required(VERSION 3.14)
project(AKP VERSION 1.0.0 LANGUAGES C CXX)

# Header-only library target
add_library(akp INTERFACE)
target_include_directories(akp INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Demo targets
add_executable(lab_demo examples/lab_demo.c)
target_link_libraries(lab_demo PRIVATE akp)

add_executable(cpp_demo examples/cpp_demo.cpp)
target_link_libraries(cpp_demo PRIVATE akp)

# CMake Package & Install configuration
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(TARGETS akp EXPORT AKPConfig)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT AKPConfig
    FILE AKPConfig.cmake
    NAMESPACE AKP::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/AKP
)
