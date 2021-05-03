cmake_minimum_required(VERSION 3.7.0)
project(rasterizer)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

find_package(SDL2 REQUIRED)

set(SRC src/main.cpp
				src/rasterizer.cpp)

include_directories(include/)

add_executable(rasterizer
	${SRC})

target_link_libraries(rasterizer mingw32 SDL2main SDL2)