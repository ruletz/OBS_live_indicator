cmake_minimum_required(VERSION 3.10)
project(obs-live-indicator)

set(PROJECT_SRCS src/live_indicator.cpp)

add_library(obs-live-indicator MODULE ${PROJECT_SRCS})
target_compile_definitions(obs-live-indicator PRIVATE)
target_link_libraries(obs-live-indicator PRIVATE Qt5::Widgets libobs)
set_target_properties(obs-live-indicator PROPERTIES PREFIX "")

install(TARGETS obs-live-indicator LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/obs-plugins)