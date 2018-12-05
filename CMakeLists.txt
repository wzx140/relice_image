cmake_minimum_required(VERSION 3.12)
project(slice_image)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

aux_source_directory(src SOURCE_FILES)
set(HEAD_FILES include/ImageInteractionCallback.h include/ImageRender.h)

#vtk
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

#copy res to build path
set(RESOURCE_FILES res/brain.mhd res/brain.raw)
file(COPY ${RESOURCE_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)

add_subdirectory(test)


add_executable(${PROJECT_NAME} ${HEAD_FILES} ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})