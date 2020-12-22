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

# append 'CMAKE_PREFIX_PATH'
file(GLOB PACKAGES_LS LIST_DIRECTORIES TRUE "${PACKAGES_PREFIX}/*")
set(PACKAGES)
foreach(f ${PACKAGES_LS})
    if(IS_DIRECTORY "${f}")
        list(APPEND PACKAGES "${f}")
    endif()
endforeach()
unset(PACKAGES_LS)
foreach(f ${PACKAGES})
    list(APPEND CMAKE_PREFIX_PATH "${f}")
endforeach()
unset(PACKAGES)

# check one 'zlib' types 'REQUIRED' or 'QUIET'
find_package(ZLIB QUIET)

# build if not found 'zlib'
if(NOT ZLIB_FOUND)
    message_status("--- download 'zlib' (start) ---")
    download(
        "${DOWNLOADS_PREFIX}/zlib-1.2.11"
        "archive.zip"
        "https://github.com/madler/zlib/archive/v1.2.11.zip"
        "9d6a627693163bbbf3f26403a3a0b0b1"
    )
    file(READ "${DOWNLOADS_PREFIX}/zlib-1.2.11/archive.zip.md5" project_zlib_URL_MD5)
    message_status("--- download 'zlib' (done) ---")

    message_status("--- extract 'zlib' (start) ---")
    FetchContent_Declare(project_zlib
        URL          "file://${DOWNLOADS_PREFIX}/zlib-1.2.11/archive.zip"
        URL_MD5      "${project_zlib_URL_MD5}"
        SOURCE_DIR   "${FETCHCONTENT_BASE_DIR}/zlib-1.2.11/src"
        BINARY_DIR   "${FETCHCONTENT_BASE_DIR}/zlib-1.2.11/build"
        SUBBUILD_DIR "${FETCHCONTENT_BASE_DIR}/zlib-1.2.11/subbuild"
    )
    FetchContent_GetProperties(project_zlib)
    if(NOT project_zlib_POPULATED)
        FetchContent_Populate(project_zlib)
    endif()

    if(NOT project_zlib_POPULATED)
        message_fatal_error("project_zlib STILL NOT POPULATED !!!")
    endif()
    message_status("--- extract 'zlib' (done) ---")

    message_status("--- config 'zlib' (start) ---")
    execute_process(
        COMMAND           ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${PACKAGES_PREFIX}/zlib-1.2.11 -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -G "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}" -S ${FETCHCONTENT_BASE_DIR}/zlib-1.2.11/src -B ${FETCHCONTENT_BASE_DIR}/zlib-1.2.11/build
        WORKING_DIRECTORY "${FETCHCONTENT_BASE_DIR}/zlib-1.2.11"
        RESULT_VARIABLE   project_zlib_CONFIG_RESULT
    )

    if(NOT project_zlib_CONFIG_RESULT EQUAL 0)
        message_fatal_error("project_zlib config exit code ${project_zlib_CONFIG_RESULT}")
    endif()
    message_status("--- config 'zlib' (done) ---")

    message_status("--- build 'zlib' (start) ---")
    execute_process(
        COMMAND           ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${PACKAGES_PREFIX}/zlib-1.2.11 --build ${FETCHCONTENT_BASE_DIR}/zlib-1.2.11/build
        WORKING_DIRECTORY "${FETCHCONTENT_BASE_DIR}/zlib-1.2.11"
        RESULT_VARIABLE   project_zlib_BUILD_RESULT
    )

    if(NOT project_zlib_BUILD_RESULT EQUAL 0)
        message_fatal_error("project_zlib build exit code ${project_zlib_BUILD_RESULT}")
    endif()
    message_status("--- build 'zlib' (done) ---")

    message_status("--- install 'zlib' (start) ---")
    execute_process(
        COMMAND           ${CMAKE_MAKE_PROGRAM} install
        WORKING_DIRECTORY "${FETCHCONTENT_BASE_DIR}/zlib-1.2.11/build"
        RESULT_VARIABLE   project_zlib_INSTALL_RESULT
    )

    if(NOT project_zlib_INSTALL_RESULT EQUAL 0)
        message_fatal_error("project_zlib install exit code ${project_zlib_INSTALL_RESULT}")
    endif()
    message_status("--- install 'zlib' (done) ---")
endif()

# append 'CMAKE_PREFIX_PATH'
file(GLOB PACKAGES_LS LIST_DIRECTORIES TRUE "${PACKAGES_PREFIX}/*")
set(PACKAGES)
foreach(f ${PACKAGES_LS})
    if(IS_DIRECTORY "${f}")
        list(APPEND PACKAGES "${f}")
    endif()
endforeach()
unset(PACKAGES_LS)
foreach(f ${PACKAGES})
    list(APPEND CMAKE_PREFIX_PATH "${f}")
endforeach()
unset(PACKAGES)

# check two 'zlib' types 'REQUIRED' or 'QUIET'
find_package(ZLIB REQUIRED)

if("${ZLIB_FOUND}")
    message_status("aaa: OK")
endif()

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}_tests)
target_sources(${PROJECT_NAME}_tests
    PRIVATE
        src/test/cpp/tests.cpp
)
