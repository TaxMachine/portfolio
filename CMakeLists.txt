cmake_minimum_required(VERSION 3.27)
project(portfolio)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/libs/imgui)
set(STB_DIR ${CMAKE_SOURCE_DIR}/libs/stb)

include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ${STB_DIR})

file(GLOB_RECURSE SOURCES src/**)

add_executable(portfolio
        ${SOURCES}
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_link_libraries(portfolio glfw3 ${OPENGL_LIBRARIES})

if (EMSCRIPTEN)
    message("Building for web")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3 -s USE_WEBGL2=1 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s FETCH=1 --bind")
endif ()

file(COPY ${CMAKE_SOURCE_DIR}/imgui.html DESTINATION ${CMAKE_BINARY_DIR})

add_custom_command(TARGET portfolio POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:portfolio>/assets)