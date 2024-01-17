cmake_minimum_required(VERSION 3.8)

set(prject_name cmake_opengl)
project(${prject_name})
set(CMAKE_CXX_STANDARD 11)

aux_source_directory(src SRC)
include_directories(include)
include_directories(ext/glad/include)
aux_source_directory(ext/glad/src GLAD_SRC)
aux_source_directory(ext/lua LUA_SRC)
add_subdirectory(ext/glfw)
add_subdirectory(ext/glm)

# include_directories(ext/glfw/include)
# include_directories(ext/glm)
include_directories(ext/lua)
add_executable(${prject_name} ${SRC} ${LUA_SRC} ${GLAD_SRC})

target_link_libraries(${prject_name} glfw)
target_link_libraries(${prject_name} glm)
