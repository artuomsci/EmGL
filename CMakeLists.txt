cmake_minimum_required(VERSION 2.8)

project (EmGL)

set(EXT_INCLUDE_DIR ./src/ext)
set(GLM_INCLUDE_DIR ./src/ext/glm)
set(XML_INCLUDE_DIR ./src/ext/tinyxml2-master)
set(MISC_INCLUDE_DIR ./src/misc)

set(FILESYSTEM_PATH ../filesystem)

if ($ENV{PLATFORM_TYPE} MATCHES "web")
    message("Web platfrom was chosen")
    set(CMAKE_EXECUTABLE_SUFFIX ".js")
else()
    message("Local platfrom was chosen")
endif()

execute_process(COMMAND nproc OUTPUT_VARIABLE CPU_UNITS_COUNT)

set(CMAKE_MAKE_PROGRAM "${CMAKE_MAKE_PROGRAM} -j${CPU_UNITS_COUNT}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(RELEASE_BUILD OFF)

if(RELEASE_BUILD)

    if ($ENV{PLATFORM_TYPE} MATCHES "web")
        set(linkFlags " -O3 -Werror --preload-file ${FILESYSTEM_PATH}")
    endif()

else()

    if ($ENV{PLATFORM_TYPE} MATCHES "web")
        set(linkFlags "-Werror -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2 -s USE_GLFW=3 --preload-file ${FILESYSTEM_PATH}")
    endif()

endif()

include_directories(${EXT_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR}/glm/gtx)
include_directories(${XML_INCLUDE_DIR})
include_directories(${MISC_INCLUDE_DIR})

if(RELEASE_BUILD)
    set(CMAKE_CXX_FLAGS "-std=c++14 -O3 -Werror -Wno-warn-absolute-paths")
else()
    set(CMAKE_CXX_FLAGS "-std=c++14 -Wno-warn-absolute-paths")
endif()

add_subdirectory("./src/agl")

##------- Misc sources -----------
file(GLOB MISC_SOURCES "${MISC_INCLUDE_DIR}/*.h" "${MISC_INCLUDE_DIR}/*.cpp" "${MISC_INCLUDE_DIR}/*.hpp")

add_executable(main
    src/main.cpp
    ${MISC_SOURCES})

target_link_libraries(main agl xmlparser)

set_property(GLOBAL PROPERTY GLOBAL_DEPENDS_NO_CYCLES 1)

set_target_properties(main PROPERTIES LINK_FLAGS "${linkFlags}")

if ($ENV{PLATFORM_TYPE} MATCHES "web")
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "./main.js" ${PROJECT_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy "./main.data" ${PROJECT_SOURCE_DIR})
endif()
