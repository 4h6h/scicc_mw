#------------------------------------------------------------------------------#
# Copyright: (c) PINTSCH GmbH
#
# CMakeLists for 
#------------------------------------------------------------------------------#
#--------10--------20--------30--------40--------50--------60--------70--------#
set(LIB_NAME common)
add_library(${LIB_NAME} INTERFACE)

target_include_directories(${LIB_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/common/include)

target_sources(${LIB_NAME} INTERFACE    include/platform_types.h 
                                        include/std_types.h )   