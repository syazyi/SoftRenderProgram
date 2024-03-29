file(GLOB_RECURSE HEADER_NAME "*.h")
file(GLOB_RECURSE SOURCE_NAME "*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_NAME} ${SOURCE_NAME})

add_executable(${PROJECT_NAME} ${HEADER_NAME} ${SOURCE_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE thirdPart)

set(CORE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/core")
set(RUNTIME_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/runtime")
set(CORE_MATH_DIRECTORY "${CORE_DIRECTORY}/math")
set(RUNTIME_GEOMETRY_DIRECTORY "${RUNTIME_DIRECTORY}/geometry")
set(RUNTIME_SHADER_DIRECTORY "${RUNTIME_DIRECTORY}/shader")
set(CORE_UTILITY_DIRECTORY "${CORE_DIRECTORY}/utility")

target_include_directories(${PROJECT_NAME} PUBLIC ${CORE_DIRECTORY}
                            PUBLIC ${CORE_MATH_DIRECTORY}
                            PUBLIC ${RUNTIME_DIRECTORY}
                            PUBLIC ${RUNTIME_GEOMETRY_DIRECTORY}
                            PUBLIC ${RUNTIME_SHADER_DIRECTORY}
                            PUBLIC ${CORE_UTILITY_DIRECTORY}
                                            )
