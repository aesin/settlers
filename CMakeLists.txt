project(settlers)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(settlers_SRCS settlers.cpp objects.cpp main.cpp)
qt4_automoc(${settlers_SRCS})
add_executable(settlers ${settlers_SRCS})
target_link_libraries(settlers ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS settlers RUNTIME DESTINATION bin)
