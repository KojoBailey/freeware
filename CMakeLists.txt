cmake_minimum_required(VERSION 3.20)

project(DesktopDefence)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SDL3
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG release-3.2.x
)
FetchContent_MakeAvailable(SDL3)
FetchContent_Declare(SDL3_image
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
	GIT_TAG release-3.2.x
)
FetchContent_MakeAvailable(SDL3_image)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

# Copies assets next to binary on build.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)
