cmake_minimum_required(VERSION 3.26)

project(spark_engine VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
include(cmake/Dependencies.cmake)
include(cmake/CMakeRC.cmake)

include_directories(spark/include)
include_directories(vendor/glad/include)
include_directories(vendor/stb)

add_compile_definitions(SPARK_VERSION="${PROJECT_VERSION}")

add_library(glad STATIC
        vendor/glad/include/glad/glad.h
        vendor/glad/include/KHR/khrplatform.h
        vendor/glad/src/glad.c
        vendor/stb/stb_image.h
)

add_subdirectory(spark)
add_subdirectory(spark_editor)
add_subdirectory(example)
add_subdirectory(${CMAKE_BINARY_DIR}/_deps/sqlitecpp-src)

#add_executable(mono_test main.cpp)

#target_compile_definitions(mono_test PUBLIC MONO_LIB_PATH="${CMAKE_SOURCE_DIR}/vendor/mono/bin")
#set_property(TARGET mono_test PROPERTY ENABLE_EXPORTS ON)
#target_link_libraries(mono_test ${Mono_LIBRARIES}  spark::rc)
#target_compile_options(mono_test PRIVATE ${Mono_CFLAGS})
#target_link_options(mono_test PRIVATE ${Mono_STATIC_LDFLAGS})
#target_include_directories(mono_test PRIVATE ./cmake-build-debug/_cmrc/include)