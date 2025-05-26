cmake_minimum_required(VERSION 3.0)
project(BVH_render C)

include_directories(include/)

file(GLOB PROJECT_HEADERS include/*.h)
file(GLOB PROJECT_SOURCES src/*.c)

file(GLOB PROJECT_CONFIGS CMakeLists.txt
                            Readme.md
                            .gitattributes
                            .gitignore
                            .gitmodules)

# source groups
source_group("headers" FILES ${PROJECT_HEADERS})
source_group("sources" FILES ${PROJECT_SOURCES})


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                                                  ${PROJECT_CONFIGS})


target_link_libraries(${PROJECT_NAME} PUBLIC "user32.dll")
target_link_libraries(${PROJECT_NAME} PUBLIC "imm32.dll")
target_link_libraries(${PROJECT_NAME} PUBLIC "gdi32.dll")
target_link_libraries(${PROJECT_NAME} PUBLIC "opengl32.dll")