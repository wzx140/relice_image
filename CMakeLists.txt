cmake_minimum_required(VERSION 3.12)
project(slice_image)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

aux_source_directory(src SOURCE_FILES)
set(HEAD_FILES include/ImageInteractionCallback.h include/ImageRender.h)

#set root
set(VTK_ROOT /opt/VTK/DEBUG)
#set(GTEST_ROOT /opt/GTest)

#vtk
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

#gtest
if (GTEST_ROOT)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    set(TEST_FILES test/ImageInteractionCallbackTest.cpp test/ImageRenderTest.cpp)
endif ()


add_executable(${PROJECT_NAME} ${HEAD_FILES} ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
if (GTEST_FOUND)
    target_link_libraries(${PROJECT_NAME} GTest::GTest)
endif ()