
file(
    GLOB LMB_SRC
    "*.cpp"
    "*/*.cpp"
)

add_library(
    lmb STATIC 
    ${LMB_SRC}
)

target_include_directories(
    lmb PUBLIC
    ${PROJECT_SOURCE_DIR}/includes/
    ${PROJECT_SOURCE_DIR}/third_party/includes/
)