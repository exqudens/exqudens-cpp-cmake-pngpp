cmake_minimum_required(VERSION 3.17)
project(exqudens_cpp_cmake_pngpp)

# config --------------------------------------------------

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

# 'zlib' part --------------------------------------------------

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
    list(REMOVE_DUPLICATES CMAKE_PREFIX_PATH)
endforeach()
unset(PACKAGES)

# check one 'zlib' type 'QUIET'
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
        COMMAND           ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${PACKAGES_PREFIX}/zlib-1.2.11 -G "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}" -S ${FETCHCONTENT_BASE_DIR}/zlib-1.2.11/src -B ${FETCHCONTENT_BASE_DIR}/zlib-1.2.11/build
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
    list(REMOVE_DUPLICATES CMAKE_PREFIX_PATH)
endforeach()
unset(PACKAGES)

# check two 'zlib' type 'REQUIRED'
find_package(ZLIB REQUIRED)

# 'libpng' part --------------------------------------------------

# check one 'libpng' type 'QUIET'
find_package(PNG QUIET)

# build if not found 'libpng'
if(NOT PNG_FOUND)
    message_status("--- download 'libpng' (start) ---")
    download(
        "${DOWNLOADS_PREFIX}/libpng-1.6.37"
        "archive.zip"
        "https://github.com/glennrp/libpng/archive/v1.6.37.zip"
        "1bbb6b2bcd580d50b82145e827eb3fb4"
    )
    file(READ "${DOWNLOADS_PREFIX}/libpng-1.6.37/archive.zip.md5" project_libpng_URL_MD5)
    message_status("--- download 'libpng' (done) ---")

    message_status("--- extract 'libpng' (start) ---")
    FetchContent_Declare(project_libpng
        URL          "file://${DOWNLOADS_PREFIX}/libpng-1.6.37/archive.zip"
        URL_MD5      "${project_libpng_URL_MD5}"
        SOURCE_DIR   "${FETCHCONTENT_BASE_DIR}/libpng-1.6.37/src"
        BINARY_DIR   "${FETCHCONTENT_BASE_DIR}/libpng-1.6.37/build"
        SUBBUILD_DIR "${FETCHCONTENT_BASE_DIR}/libpng-1.6.37/subbuild"
    )
    FetchContent_GetProperties(project_libpng)
    if(NOT project_libpng_POPULATED)
        FetchContent_Populate(project_libpng)
    endif()

    if(NOT project_libpng_POPULATED)
        message_fatal_error("project_libpng STILL NOT POPULATED !!!")
    endif()
    message_status("--- extract 'libpng' (done) ---")

    message_status("--- config 'libpng' (start) ---")
    execute_process(
        COMMAND           ${CMAKE_COMMAND} -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_INSTALL_PREFIX=${PACKAGES_PREFIX}/libpng-1.6.37 -G "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}" -S ${FETCHCONTENT_BASE_DIR}/libpng-1.6.37/src -B ${FETCHCONTENT_BASE_DIR}/libpng-1.6.37/build
        WORKING_DIRECTORY "${FETCHCONTENT_BASE_DIR}/libpng-1.6.37"
        RESULT_VARIABLE   project_libpng_CONFIG_RESULT
    )

    if(NOT project_libpng_CONFIG_RESULT EQUAL 0)
        message_fatal_error("project_libpng config exit code ${project_libpng_CONFIG_RESULT}")
    endif()
    message_status("--- config 'libpng' (done) ---")

    message_status("--- build 'libpng' (start) ---")
    execute_process(
        COMMAND           ${CMAKE_COMMAND} -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DCMAKE_INSTALL_PREFIX=${PACKAGES_PREFIX}/libpng-1.6.37 --build ${FETCHCONTENT_BASE_DIR}/libpng-1.6.37/build
        WORKING_DIRECTORY "${FETCHCONTENT_BASE_DIR}/libpng-1.6.37"
        RESULT_VARIABLE   project_libpng_BUILD_RESULT
    )

    if(NOT project_libpng_BUILD_RESULT EQUAL 0)
        message_fatal_error("project_libpng build exit code ${project_libpng_BUILD_RESULT}")
    endif()
    message_status("--- build 'libpng' (done) ---")

    message_status("--- install 'libpng' (start) ---")
    execute_process(
        COMMAND           ${CMAKE_MAKE_PROGRAM} install
        WORKING_DIRECTORY "${FETCHCONTENT_BASE_DIR}/libpng-1.6.37/build"
        RESULT_VARIABLE   project_libpng_INSTALL_RESULT
    )

    if(NOT project_libpng_INSTALL_RESULT EQUAL 0)
        message_fatal_error("project_libpng install exit code ${project_libpng_INSTALL_RESULT}")
    endif()
    message_status("--- install 'libpng' (done) ---")
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
    list(REMOVE_DUPLICATES CMAKE_PREFIX_PATH)
endforeach()
unset(PACKAGES)

# check two 'libpng' type 'REQUIRED'
find_package(PNG REQUIRED)

# 'pngpp' part --------------------------------------------------

# check one 'pngpp-0.2.9'
if(NOT "${PACKAGES_PREFIX}/pngpp-0.2.9" IN_LIST CMAKE_PREFIX_PATH)
    message_status("--- download 'pngpp' (start) ---")
    download(
        "${DOWNLOADS_PREFIX}/pngpp-0.2.9"
        "archive.tar.gz"
        "http://download.savannah.nongnu.org/releases/pngpp/png++-0.2.9.tar.gz"
        "92863df3bee625d707cebc0e749c10df"
    )
    file(READ "${DOWNLOADS_PREFIX}/pngpp-0.2.9/archive.tar.gz.md5" project_pngpp_URL_MD5)
    message_status("--- download 'pngpp' (done) ---")

    message_status("--- extract 'pngpp' (start) ---")
    FetchContent_Declare(project_pngpp
        URL          "file://${DOWNLOADS_PREFIX}/pngpp-0.2.9/archive.tar.gz"
        URL_MD5      "${project_pngpp_URL_MD5}"
        SOURCE_DIR   "${FETCHCONTENT_BASE_DIR}/pngpp-0.2.9/src"
        BINARY_DIR   "${FETCHCONTENT_BASE_DIR}/pngpp-0.2.9/build"
        SUBBUILD_DIR "${FETCHCONTENT_BASE_DIR}/pngpp-0.2.9/subbuild"
    )
    FetchContent_GetProperties(project_pngpp)
    if(NOT project_pngpp_POPULATED)
        FetchContent_Populate(project_pngpp)
    endif()

    if(NOT project_pngpp_POPULATED)
        message_fatal_error("project_pngpp STILL NOT POPULATED !!!")
    endif()
    message_status("--- extract 'pngpp' (done) ---")

    message_status("--- install 'pngpp' (start) ---")
    file(GLOB "pngpp_FILES" "${project_pngpp_SOURCE_DIR}/*.hpp")
    if(NOT EXISTS "${PACKAGES_PREFIX}/pngpp-0.2.9")
        file(MAKE_DIRECTORY "${PACKAGES_PREFIX}/pngpp-0.2.9")
        file(MAKE_DIRECTORY "${PACKAGES_PREFIX}/pngpp-0.2.9/include")
        file(MAKE_DIRECTORY "${PACKAGES_PREFIX}/pngpp-0.2.9/include/png++")
        file(COPY ${pngpp_FILES} DESTINATION "${PACKAGES_PREFIX}/pngpp-0.2.9/include/png++")
        if(EXISTS "${PACKAGES_PREFIX}/pngpp-0.2.9/include/png++/png.hpp")
            set(project_pngpp_INSTALL_RESULT 0)
        else()
            set(project_pngpp_INSTALL_RESULT 1)
        endif()
    endif()

    if(NOT project_pngpp_INSTALL_RESULT EQUAL 0)
        message_fatal_error("project_pngpp install exit code ${project_pngpp_INSTALL_RESULT}")
    endif()
    message_status("--- install 'pngpp' (done) ---")
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
    list(REMOVE_DUPLICATES CMAKE_PREFIX_PATH)
endforeach()
unset(PACKAGES)

# check two 'pngpp-0.2.9' type 'REQUIRED'
if(NOT "${PACKAGES_PREFIX}/pngpp-0.2.9" IN_LIST CMAKE_PREFIX_PATH)
    message_fatal_error("Can't find PNGPP in 'CMAKE_PREFIX_PATH': ${CMAKE_PREFIX_PATH}")
endif()

if(ZLIB_FOUND AND PNG_FOUND AND "${PACKAGES_PREFIX}/pngpp-0.2.9" IN_LIST CMAKE_PREFIX_PATH)
    message_status("aaa: OK")
endif()

# project --------------------------------------------------

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}_tests)
target_sources(${PROJECT_NAME}_tests
    PRIVATE
        src/test/cpp/tests.cpp
)
