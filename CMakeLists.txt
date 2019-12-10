cmake_minimum_required(VERSION 3.5)
project(Babel)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_PREFIX_PATH "C:\\Qt\\5.12.5\\msvc2017\\")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Multimedia CONFIG REQUIRED)
include_directories(${CMAKE_INCLUDE_PATH})

file(GLOB_RECURSE CLIENT_SRCS "./src/*.cpp")
add_executable(babel_client WIN32 ${CLIENT_SRCS})
include_directories(${CMAKE_INCLUDE_PATH} src/Network src src/Audio src/Graphic src/Graphic/Layout src/Graphic/ContactList src/Graphic/ContactList/Contact src/Graphic/Chat)
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui Qt5::Multimedia)

set(CMAKE_AUTOMOC OFF)

file(GLOB_RECURSE SOURCES_SERVER "./server/*.cpp")
add_executable(babel_server ${SOURCES_SERVER})
target_link_libraries(babel_server ${CONAN_LIBS})

if (UNIX)
    add_custom_command(TARGET babel_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:babel_server> $(CMAKE_SOURCE_DIR))
    add_custom_command(TARGET babel_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:babel_client> $(CMAKE_SOURCE_DIR))
endif (UNIX)
