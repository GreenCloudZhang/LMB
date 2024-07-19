
file(
    GLOB LMBEXAMPLE_SRC 
    "*.cpp"
)

add_definitions(
    -DDRAW
)


add_executable(
    lmb_example ${LMBEXAMPLE_SRC}
)

file(COPY ${CMAKE_SOURCE_DIR}/third_party/libs/SDL2/SDL2.dll DESTINATION ${EXECUTABLE_OUTPUT_PATH}/SDL2.dll)

target_include_directories(
    lmb_example PUBLIC
    ${PROJECT_SOURCE_DIR}/includes/
    ${PROJECT_SOURCE_DIR}/third_party/includes/
)

find_package(OpenGL REQUIRED)

target_link_libraries(
    lmb_example 
    lmb
    ${CMAKE_SOURCE_DIR}/third_party/libs/SDL2/SDL2.lib
    ${CMAKE_SOURCE_DIR}/third_party/libs/SDL2/SDL2.lib
    ${OPENGL_LIBRARIES}
)