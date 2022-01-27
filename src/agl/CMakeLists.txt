cmake_minimum_required(VERSION 2.8)

project (agl)

find_package(OpenGL REQUIRED)

##--------------------------------------------------------
#add_library(glew_static STATIC IMPORTED)
#set_target_properties(glew_static PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../ext/glew-1.13.0/lib/libGLEW.a)
#include_directories(../ext/glew-1.13.0/include)
##--------------------------------------------------------

if ($ENV{PLATFORM_TYPE} MATCHES "web")
else()
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})

    find_package(glfw3 3.3 REQUIRED)

    link_libraries(${GLEW_LIBRARIES} glfw)
endif()

set(EXT_INCLUDE_DIR ../ext)
set(GLM_INCLUDE_DIR ../ext/glm)
set(XML_INCLUDE_DIR ../ext/tinyxml2-master)
set(AGL_PRIMITIVES_INCLUDE_DIR ./primitives)
set(MISC_INCLUDE_DIR ../misc)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(${EXT_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR}/glm/gtx)
include_directories(${XML_INCLUDE_DIR})
include_directories(${AGL_PRIMITIVES_INCLUDE_DIR})
include_directories(${MISC_INCLUDE_DIR})

##------- External libs -----------
add_library(xmlparser STATIC ${XML_INCLUDE_DIR}/tinyxml2.cpp)
add_library(lodepng STATIC ${EXT_INCLUDE_DIR}/lodepng.cpp)

file(GLOB EMGUI_SOURCES "${EXT_INCLUDE_DIR}/imgui-master/*.h" "${EXT_INCLUDE_DIR}/imgui-master/*.cpp")
add_library(imgui STATIC ${EMGUI_SOURCES})

#set(EXT_LIBS glew_static lodepng xmlparser imgui)
set(EXT_LIBS lodepng xmlparser imgui)

if ($ENV{PLATFORM_TYPE} MATCHES "web")
    set(ADD_LIBS)
else()
    set(ADD_LIBS glfw)
endif()

##------- Graphics API sources -----------
file(GLOB COMMON_SOURCES "${MISC_INCLUDE_DIR}/*.h" "${MISC_INCLUDE_DIR}/*.cpp" "${MISC_INCLUDE_DIR}/*.hpp")

file(GLOB AGL_CORE_SOURCES "*.h" "*.cpp")

file(GLOB AGL_PRIMITIVES "${AGL_PRIMITIVES_INCLUDE_DIR}/*.h" "${AGL_PRIMITIVES_INCLUDE_DIR}/*.cpp")

file(GLOB AGL_MISC_SOURCES "*.hpp")

add_library(
	${PROJECT_NAME} 

        ${COMMON_SOURCES}
        ${XML_INCLUDE_DIR}/tinyxml2.cpp
        ${AGL_MISC_SOURCES}
        ${AGL_CORE_SOURCES}
        ${AGL_PRIMITIVES})

target_link_libraries(${PROJECT_NAME} ${EXT_LIBS} ${OPENGL_LIBRARIES} ${ADD_LIBS})
