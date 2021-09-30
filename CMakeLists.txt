cmake_minimum_required(VERSION 3.21)

# MisaMino itself, build as a static library
project(MisaMino)
file(GLOB SOURCE_FILES "src/MisaMinoNET/MisaMinoNET/MisaMino/*.cpp" "src/MisaMinoNET/MisaMinoNET/MisaMino/*.h")
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# MisaMinoJS, wrapping MisaMino functions for JS to call
project(MisaMinoJS)
file(GLOB SOURCE_FILES "src/*.cpp" "src/*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC} ${CMAKE_SOURCE_DIR}/node_modules/node-addon-api)
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} MisaMino)