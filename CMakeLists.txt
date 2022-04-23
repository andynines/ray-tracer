cmake_minimum_required(VERSION 3.10)
project(cs636-course-project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG -g)
set(CMAKE_CXX_FLAGS_RELEASE -O3)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(ray-tracer
		${CMAKE_SOURCE_DIR}/main.cpp
		${SRC_DIR}/htmlBuilder.cpp
		${SRC_DIR}/image.cpp
		${SRC_DIR}/math.cpp
		${SRC_DIR}/scene.cpp
		${SRC_DIR}/sceneDescrParser.cpp
		${SRC_DIR}/smfModel.cpp
		${SRC_DIR}/sphere.cpp
		)
target_compile_definitions(ray-tracer PUBLIC -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=0)
target_include_directories(ray-tracer PUBLIC ${INCLUDE_DIR} /usr/include/ImageMagick-6 /usr/include/x86_64-linux-gnu/ImageMagick-6)
target_link_libraries(ray-tracer stdc++fs pthread /usr/lib/x86_64-linux-gnu/libMagick++-6.Q16.so /usr/lib/x86_64-linux-gnu/libMagickCore-6.Q16.so /usr/lib/x86_64-linux-gnu/libMagickWand-6.Q16.so)
