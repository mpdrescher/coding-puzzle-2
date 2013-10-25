cmake_minimum_required(VERSION 2.8)
project(prog1 CXX)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(prog1_SOURCE_TREE ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(Configure)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.53 COMPONENTS system filesystem REQUIRED)
add_definitions(-DBOOST_FILESYSTEM_NO_DEPRECATED)
include_directories(${prog1_SOURCE_TREE} ${Boost_INCLUDE_DIRS})
set(prog1_LINK_TARGETS ${Boost_LIBRARIES})

# Set-up testing.
add_subdirectory(tools)
set(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/tools/gtest)
set(GTEST_INCLUDE_DIR ${GTEST_ROOT}/include)
set(GTEST_LIBRARIES gtest gtest_main)

include_directories(${GTEST_INCLUDE_DIR})

if(MSVC)
	if(MSVC_VERSION EQUAL 1700)
		add_definitions(-D_VARIADIC_MAX=10)
	endif()
endif()

add_executable(tests test.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} ${prog1_LINK_TARGETS})
