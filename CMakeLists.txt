cmake_minimum_required(VERSION 3.24)
project(CEN3031-Project)

# mysql
include_directories(${CMAKE_SOURCE_DIR}/mysql-connector-c-6.1.11-winx64/include)
link_directories(${CMAKE_SOURCE_DIR}/mysql-connector-c-6.1.11-winx64/lib)
link_libraries(libmysql)

# head files
include_directories(include)

set(CMAKE_CXX_STANDARD 17)

# Add the executable
add_executable(CEN3031-Project
        imgui/imgui.cpp
        imgui/imgui_impl_dx11.cpp
        imgui/imgui_impl_win32.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_demo.cpp

        src/main.cpp
        src/database.cpp
        src/user_manager.cpp
        src/GUI_Layout.cpp
#        src/mysql_test.cpp
)

# Link DirectX libraries
target_link_libraries(CEN3031-Project d3d11 d3dcompiler dwmapi libmysql)

target_include_directories(CEN3031-Project PRIVATE ${CMAKE_SOURCE_DIR}/imgui)

target_compile_definitions(CEN3031-Project PRIVATE IMGUI_IMPL_API=)