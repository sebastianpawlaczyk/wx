cmake_minimum_required(VERSION 3.15)
project(wx)

set(CMAKE_CXX_STANDARD 14)

#find_package(wxWidgets COMPONENTS core base REQUIRED)
find_package(wxWidgets) # using this I'am able to use wxAboutBox
include(${wxWidgets_USE_FILE})

add_executable(wx main.cpp MainApp.cpp MainApp.hpp Window.cpp Window.hpp LogNotebook.cpp LogNotebook.hpp)

target_link_libraries(wx
        ${wxWidgets_LIBRARIES}
        wx_gtk3u_richtext-3.0
        )
