#------------------------------------------------------------------------------#
# Copyright: (c) PINTSCH GmbH
#
# CMakeLists for 
#------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(sci_cc_comp
#        LANGUAGES C
#        DESCRIPTION 'Build the tcp server for SciCC and connection to ICL' 
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/exec/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib/bin)

#------------------------------------------------------------------------------#
# Disable in-source builds to prevent source tree corruption
#------------------------------------------------------------------------------#
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR '
        FATAL: In-source builds are not allowed.
            You should create a separate directory for build files.
    ')
endif()


#------------------------------------------------------------------------------#
# Include subdirectories
#------------------------------------------------------------------------------#
add_subdirectory(common)
add_subdirectory(sci_cc)
add_subdirectory(mw)
