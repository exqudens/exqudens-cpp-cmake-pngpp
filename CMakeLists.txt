cmake_minimum_required(VERSION 3.17)
project(exqudens_cpp_cmake_pngpp)

# download 'extension'
if (NOT EXISTS "${CMAKE_SOURCE_DIR}/extension.cmake")
    file(
        DOWNLOAD     "https://raw.githubusercontent.com/exqudens/exqudens-cmake/4.0.0/extension.cmake"
                     "${CMAKE_SOURCE_DIR}/extension.cmake"
        EXPECTED_MD5 "820d9295d302fc665cb6d1318af55e2c"
    )
endif()

# enable extensions
include(extension.cmake)
include(FindPkgConfig)
include(FetchContent)

# config
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/downloads")
    file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/downloads")
endif()
set_downloads_prefix("${CMAKE_SOURCE_DIR}/downloads")
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/libs")
    file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/libs")
endif()
set_packages_prefix("${CMAKE_SOURCE_DIR}/libs")

# AAA
file(GLOB PACKAGES_LS LIST_DIRECTORIES TRUE "${PACKAGES_PREFIX}/*")
set(PACKAGES)
foreach(f ${PACKAGES_LS})
    if(IS_DIRECTORY "${f}")
        list(APPEND PACKAGES "${f}")
    endif()
endforeach()
foreach(f ${PACKAGES})
    list(APPEND CMAKE_PREFIX_PATH "${f}")
endforeach()

# check 'zlib' types 'REQUIRED' or 'QUIET'
find_package(ZLIB QUIET)

if(NOT "${ZLIB_FOUND}")
    message_status("aaa: BUILD ZLIB!")
endif()

if("${ZLIB_FOUND}")
    message_status("aaa: OK")
endif()

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}_tests)
target_sources(${PROJECT_NAME}_tests
    PRIVATE
        src/test/cpp/tests.cpp
)
