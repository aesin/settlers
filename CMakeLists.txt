project(settlers)
#cmake_minimum_required(VERSION 2.6)
cmake_minimum_required(VERSION 2.8.6)
find_package(Qt4 REQUIRED)
set(CMAKE_AUTOMOC TRUE)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(settlers_SRCS trade_widget.cpp ui.cpp network.cpp settlers.cpp objects.cpp main.cpp)
#qt4_automoc(${settlers_SRCS})
add_executable(settlers ${settlers_SRCS})
target_link_libraries(settlers ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS settlers RUNTIME DESTINATION bin)


