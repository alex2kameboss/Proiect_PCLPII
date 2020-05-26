cmake_minimum_required(VERSION 3.10)

project(wxCalc)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(wxCalc wxCalc/App.cpp wxCalc/MainFrame.cpp)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})