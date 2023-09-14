#------------------------------------------------------------------------------#
# Copyright: (c) PINTSCH GmbH
#
# CMakeLists for 
#------------------------------------------------------------------------------#
#--------10--------20--------30--------40--------50--------60--------70--------#
add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} common sci_cc rt)

#------------------------------------------------------------------------------#
# List sources and include dirs for for the library
#------------------------------------------------------------------------------#
target_sources(${PROJECT_NAME} PRIVATE src/mw.c 
                                        src/main.c )

target_include_directories(${PROJECT_NAME} PUBLIC   ${PROJECT_SOURCE_DIR}/sci_cc/include
                                                    ${PROJECT_SOURCE_DIR}/common/include 
                                                    ${PROJECT_SOURCE_DIR}/mw/include )
                                                
target_include_directories(${PROJECT_NAME} PRIVATE src)

#------------------------------------------------------------------------------#
# Additional properties.
#------------------------------------------------------------------------------#
set_property(TARGET ${PROJECT_NAME} PROPERTY COMPILE_WARNING_AS_ERROR ON)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)