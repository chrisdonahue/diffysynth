cmake_minimum_required(VERSION 2.8)

project(diffysynth)

# project attributes
set(PACKAGE "diffysynth")
set(CPACK_PACKAGE_NAME "${PACKAGE}")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
set(CPACK_PACKAGE_VENDOR "christopherdonahue@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PACKAGE} ${PACKAGE_VERSION}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(VERSION "${CPACK_PACKAGE_VERSION}")
set(DIFFYSYNTH_LIBRARY_VERSION ${CPACK_PACKAGE_VERSION})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

# try to find the current Git hash
find_package(Git)
if(GIT_EXECUTABLE)
	execute_process(
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMAND "${GIT_EXECUTABLE}" log -n 1 --pretty=%h
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    set(DIFFYSYNTH_BUILD_HASH ${GIT_HASH})
    message("Git commit hash: ${DIFFYSYNTH_BUILD_HASH}")
endif()

# Options
option(DIFFYSYNTH_BUILD_SHARED "Build shared library" ON)
option(DIFFYSYNTH_BUILD_TESTS "Build the diffysynth test apps" ON)

# fix inline
include(CheckCSourceCompiles)
foreach(KEYWORD "inline" "__inline__" "__inline")
	set(CMAKE_REQUIRED_DEFINITIONS "-DKEYWORD=${KEYWORD}")
	CHECK_C_SOURCE_COMPILES(
		"
		#include <stdio.h>
		KEYWORD void a() {}
		int main(int argc, char **argv) { a(); return 0; }
		" HAVE_${KEYWORD})
endforeach()
if (NOT HAVE_inline)
	if (HAVE___inline__)
		set(inline __inline__)
	elseif(HAVE___inline)
		set(inline __inline)
	endif()
endif()

# So we can include the CMake generated config file only when
# building with CMAKE.
add_definitions(-DCMAKE_BUILD)

# Check system compatibilities
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckTypeSize)

CHECK_FUNCTION_EXISTS(malloc HAVE_MALLOC)
CHECK_FUNCTION_EXISTS(memset HAVE_MEMSET)
CHECK_FUNCTION_EXISTS(realloc HAVE_REALLOC)

CHECK_INCLUDE_FILE(stdlib.h HAVE_STDLIB_H)
CHECK_INCLUDE_FILE(string.h HAVE_STRING_H)

CHECK_INCLUDE_FILES("stdlib.h;stdarg.h;string.h;float.h" STDC_HEADERS)

CHECK_TYPE_SIZE(size_t SIZE_T_SIZE)

if (NOT SIZE_T_SIZE)
	set(size_t "unsigned int")
endif()

if (NOT HAVE_MALLOC)
	set(malloc rpl_malloc)
endif()

if (NOT HAVE_REALLOC)
	set(realloc rpl_realloc)
endif()

# Generate the config.h that includes all the compilation settings.
configure_file(
       "${PROJECT_SOURCE_DIR}/config.h.cmake"
       "${PROJECT_BINARY_DIR}/diffysynth_config.h")
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_BINARY_DIR}")

if (MSVC)
	# Turn off stupid microsoft security warnings.
	#add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE)
endif(MSVC)

set(HEADERS
	src/diffysynth.hpp
	src/define.hpp
	src/exception.hpp
	src/type.hpp
	src/value.hpp
	src/diff_eq.hpp
	src/diff_eq_system.hpp
	src/rng.hpp
	src/primitive/primitive_base.hpp
	src/primitive/constant.hpp
	src/primitive/elementary.hpp
	src/primitive/estimate.hpp
	src/primitive/parameter.hpp
	src/primitive/square_root.hpp
	src/primitive/time.hpp
	src/stepper/stepper_base.hpp
	src/stepper/runge_kutta_4.hpp
	src/gp/population.hpp
	src/gp/selector.hpp
	src/gp/evaluator.hpp
	src/gp/individual.hpp
)

set(HEADERS_
	src/diffysynth.hpp
	src/define.hpp
	src/exception.hpp
	src/type.hpp
	src/value.hpp
	src/diff_eq.hpp
	src/diff_eq_system.hpp
	src/rng.hpp
)

set(HEADERS_PRIMITIVE
	src/primitive/primitive_base.hpp
	src/primitive/constant.hpp
	src/primitive/elementary.hpp
	src/primitive/estimate.hpp
	src/primitive/parameter.hpp
	src/primitive/square_root.hpp
	src/primitive/time.hpp
)

set(HEADERS_STEPPER
	src/stepper/stepper_base.hpp
	src/stepper/runge_kutta_4.hpp
)

set(HEADERS_GP
	src/gp/population.hpp
	src/gp/selector.hpp
	src/gp/evaluator.hpp
	src/gp/individual.hpp
)
	
set(SOURCES
	src/exception.cpp
	src/diff_eq.cpp
	src/diff_eq_system.cpp
	src/rng.cpp
	src/primitive/primitive_base.cpp
	src/primitive/constant.cpp
	src/primitive/elementary.cpp
	src/primitive/estimate.cpp
	src/primitive/parameter.cpp
	src/primitive/square_root.cpp
	src/primitive/time.cpp
	src/stepper/stepper_base.cpp
	src/stepper/runge_kutta_4.cpp
	src/gp/population.cpp
	src/gp/selector.cpp
	src/gp/evaluator.cpp
	src/gp/individual.cpp
)

set(SOURCES_
	src/exception.cpp
	src/diff_eq.cpp
	src/diff_eq_system.cpp
	src/rng.cpp
)

set(SOURCES_PRIMITIVE
	src/primitive/primitive_base.cpp
	src/primitive/constant.cpp
	src/primitive/elementary.cpp
	src/primitive/estimate.cpp
	src/primitive/parameter.cpp
	src/primitive/square_root.cpp
	src/primitive/time.cpp
)

set(SOURCES_STEPPER
	src/stepper/stepper_base.cpp
	src/stepper/runge_kutta_4.cpp
)

set(SOURCES_GP
	src/gp/population.cpp
	src/gp/selector.cpp
	src/gp/evaluator.cpp
	src/gp/individual.cpp
)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    include (CheckCCompilerFlag)
    CHECK_C_COMPILER_FLAG(-fvisibility=hidden HAVE_VISIBILITY)
    if (HAVE_VISIBILITY)
                set(VISIBILITY_FLAG -fvisibility=hidden)
    endif()
    if (UNIX)
		set( CMAKE_C_FLAGS "-Wall -Werror -O3 ${VISIBILITY_FLAG} ${CMAKE_C_FLAGS}" )
    else(UNIX)
		set( CMAKE_C_FLAGS "-Wall -O3 ${VISIBILITY_FLAG} ${CMAKE_C_FLAGS}" )
    endif(UNIX)
endif ()

source_group("src" FILES ${SOURCES_})
source_group("src\\primitive" FILES ${SOURCES_PRIMITIVE})
source_group("src\\stepper" FILES ${SOURCES_STEPPER})
source_group("src\\gp" FILES ${SOURCES_GP})
source_group("inc" FILES ${HEADERS_})
source_group("inc\\primitive" FILES ${HEADERS_PRIMITIVE})
source_group("inc\\stepper" FILES ${HEADERS_STEPPER})
source_group("inc\\gp" FILES ${HEADERS_GP})
add_library(diffysynth STATIC
			${HEADERS}
			${SOURCES})

if (WIN32)
	# On Windows libs have the same file ending (.lib)
	# for both static and shared libraries, so we
	# need a unique name for the static one.
	set_target_properties(diffysynth 
		PROPERTIES
		OUTPUT_NAME diffysynth_static)
endif(WIN32)

# Set the so version of the lib.
# Equivalent to LDFLAGS=-version-info x:x:x
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	foreach(lib diffysynth)
		set_target_properties(${lib} 
			PROPERTIES
			SOVERSION ${SOVERSION})
	endforeach()
endif()

#
# Test applications
#
set(TEST_APP_LIST)
if (DIFFYSYNTH_BUILD_TESTS)
	#
	# Helper function for adding a test app.
	#
	macro(create_test_app TEST_NAME MAIN_SRC)
		
		set(TEST_SRCS ${MAIN_SRC})
		set(TEST_HDR)

		#if (WIN32)
			#list(APPEND TEST_SRCS 
			#	${WIN32_HELPERS_PATH}/getopt.c
			#	${WIN32_HELPERS_PATH}/getopt_long.c
			#	${WIN32_HELPERS_PATH}/gettimeofday.c
			#)

			#list(APPEND TEST_HDR 
			#	${WIN32_HELPERS_PATH}/getopt.h
			#	${WIN32_HELPERS_PATH}/gettimeofday.h
			#)
		#endif(WIN32)

		source_group("Headers Private"   FILES ${TEST_HDR})
		source_group("Sources"   FILES ${TEST_SRCS})
		add_executable(${TEST_NAME} ${TEST_SRCS} ${TEST_HDR})
		
		target_link_libraries(${TEST_NAME} diffysynth)
		add_dependencies(${TEST_NAME} diffysynth)

		# Set test app specific defines.
		set_property(TARGET ${TEST_NAME}
					PROPERTY COMPILE_DEFINITIONS 
						INSTALL_DATADIR="${CMAKE_INSTALL_PREFIX}/share"
					)

		# Prefix the binary names with libdiffysynth.
		set_target_properties(${TEST_NAME} 
			PROPERTIES
			OUTPUT_NAME libdiffysynth-${TEST_NAME})

		# Add to the list of tests.
		list(APPEND TEST_APP_LIST ${TEST_NAME})
	endmacro()

	# test apps
	create_test_app(test_rosetta "test/test_rosetta.cpp")
	create_test_app(test_sin_cos "test/test_sin_cos.cpp")
endif(DIFFYSYNTH_BUILD_TESTS)

if (UNIX)
# Generate and install pkgconfig.
# (This is not indented, because the tabs will be part of the output)
file(WRITE "${PROJECT_BINARY_DIR}/libdiffysynth.pc"
"prefix=\"${CMAKE_INSTALL_PREFIX}\"
exec_prefix=\${prefix}
libdir=\${exec_prefix}/lib${LIB_SUFFIX}
includedir=\${prefix}/include

Name: libdiffysynth
Description: differential equation solver for audio synthesis
Version: ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}

Libs: -L\${libdir} -ldiffysynth
Cflags: -I\${includedir}"
)

	install(FILES "${PROJECT_BINARY_DIR}/libdiffysynth.pc"
		DESTINATION lib${LIB_SUFFIX}/pkgconfig)
endif(UNIX)

#
# Installation preparations.
#

if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR cmake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/libdiffysynth)
endif()

message("---------------------------------------------------------------------")
message("  Settings:  (For more help do cmake -LH <srcpath>")
message("---------------------------------------------------------------------")
message(" DIFFYSYNTH_BUILD_SHARED = ${DIFFYSYNTH_BUILD_SHARED}")
message(" DIFFYSYNTH_DEBUG_INTERNAL = ${DIFFYSYNTH_DEBUG_INTERNAL}")
message(" DIFFYSYNTH_BUILD_TESTS = ${DIFFYSYNTH_BUILD_TESTS}")
message("---------------------------------------------------------------------")

# These will be available to parent projects including libdiffysynth using add_subdirectory()
set(LIBDIFFYSYNTH_LIBRARIES diffysynth CACHE STRING "diffysynth libraries")
set(LIBDIFFYSYNTH_LIBRARIES_STATIC diffysynth CACHE STRING "diffysynth static library")

# This must always be last!
include(CPack)