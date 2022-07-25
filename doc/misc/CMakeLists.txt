cmake_minimum_required(VERSION 3.11.0)

project(app VERSION 1.0)


### SOURCES ###

FILE(GLOB SOURCES
    src/*.cpp
    src/core/*.cpp
)
include_directories(${PROJECT_NAME} src)
add_executable(${PROJECT_NAME} ${SOURCES})


### CONFIGURATION ###

option(USE_SDL2_NET "Initialize sdl2_net" OFF)
option(USE_SDL2_IMAGE "Initialize sdl2_image" OFF)
option(USE_SDL2_TTF "Initialize sdl2_ttf" OFF)

configure_file(src/core/version.hpp.in
               src/core/version.hpp)
configure_file(src/core/config.hpp.in
               src/core/config.hpp)

target_include_directories( ${PROJECT_NAME} PUBLIC
    "${PROJECT_BINARY_DIR}/src"
)


### CXX FLAGS ###

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

target_compile_options(${PROJECT_NAME} PUBLIC -O2)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror
    #-g
    #-O2
)



### DEPENDENCIES ###
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(FetchContent)

find_package(SDL2 QUIET)
if(NOT SDL2_FOUND)
    FetchContent_Declare(
        SDL
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG 53dea9830964eee8b5c2a7ee0a65d6e268dc78a1 #release-2.0.22
    )
    FetchContent_MakeAvailable(SDL)
endif()

find_package(SDL2_net QUIET)
if(NOT SDL2_NET_FOUND)
    FetchContent_Declare(
        SDL_net
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_net
        GIT_TAG efcc19f533a4203559b134b1882f6a0a5cbe81cf
    )
    FetchContent_MakeAvailable(SDL_net)
endif()

find_package(SDL2_image QUIET)
if(NOT SDL2_IMAGE_FOUND)
    FetchContent_Declare(
        SDL_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
        GIT_TAG 4be5ea2f988106530b7b6e264150dcce886c8d99
    )
    FetchContent_MakeAvailable(SDL_image)
endif()

find_package(SDL2_ttf QUIET)
if(NOT SDL2_TTF_FOUND)
    FetchContent_Declare(
        SDL_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
        GIT_TAG b9fd0e1ed8d7b24329000ef4685096f11c97bd6a
    )
    FetchContent_MakeAvailable(SDL_ttf)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    SDL2_net::SDL2_net
    SDL2_ttf::SDL2_ttf
)

