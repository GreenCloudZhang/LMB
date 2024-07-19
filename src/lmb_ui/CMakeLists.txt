
file(
    GLOB LMBUI_SRC 
    "*.cpp"
    "imgui/*.cpp"
)


add_executable(
    lmb_ui 
    ${LMBUI_SRC}
)

file(COPY ${CMAKE_SOURCE_DIR}/third_party/libs/SDL2/SDL2.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH}/SDL2.dll)

target_include_directories(
    lmb_ui PUBLIC
    ${PROJECT_SOURCE_DIR}/includes/
    ${PROJECT_SOURCE_DIR}/third_party/includes/
)

find_package(OpenGL REQUIRED)

target_link_libraries(
    lmb_ui 
    ${CMAKE_SOURCE_DIR}/third_party/libs/SDL2/SDL2.lib
    ${CMAKE_SOURCE_DIR}/third_party/libs/SDL2/SDL2main.lib
    ${OPENGL_LIBRARIES}
    lmb
)