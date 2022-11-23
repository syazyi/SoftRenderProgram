file(GLOB_RECURSE EXT_HEADER "*.h")
set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/ext/glad/glad.c")
set(EXT_NAME thirdPart)
set(LIB_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${EXT_HEADER} ${GLAD_SOURCE})

add_library(${EXT_NAME} STATIC ${EXT_HEADER} ${GLAD_SOURCE})
target_link_directories(${EXT_NAME} PUBLIC ${LIB_DIRECTORY})
target_link_libraries(${EXT_NAME} PUBLIC glfw3.lib)

find_package(OpenGL REQUIRED)
target_link_libraries(${EXT_NAME} PUBLIC opengl32)

target_include_directories(${EXT_NAME} PUBLIC ext)
