cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 11)

# MisaMino itself, build as a static library
project(MisaMino)
file(GLOB SOURCE_FILES "src/MisaMino/MisaMino/*.cpp" "src/MisaMino/MisaMino/*.h")
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
set_property(TARGET MisaMino PROPERTY POSITION_INDEPENDENT_CODE ON)

# MisaMinoJS, wrapping MisaMino functions for JS to call
project(MisaMinoJS)
file(GLOB SOURCE_FILES "src/*.cpp" "src/*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC} ${CMAKE_SOURCE_DIR}/node_modules/node-addon-api)
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} MisaMino)
# set_property(TARGET MisaMinoJS PROPERTY CMAKE_BUILD_TYPE Debug) # For debugging