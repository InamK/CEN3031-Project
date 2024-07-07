cmake_minimum_required(VERSION 3.24)
project(CEN3031-Project)

set(CMAKE_CXX_STANDARD 17)

# Add the executable
add_executable(CEN3031-Project main.cpp
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imconfig.h
        imgui/imgui_impl_dx11.h
        imgui/imgui_impl_dx11.cpp
        imgui/imgui_impl_win32.h
        imgui/imgui_impl_win32.cpp
        imgui/imgui_internal.h
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_demo.cpp
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
        )

# Link DirectX libraries
target_link_libraries(CEN3031-Project d3d11 d3dcompiler dwmapi libd3dx11.a libd3d11.a)

target_include_directories(CEN3031-Project PRIVATE ${CMAKE_SOURCE_DIR}/imgui)

