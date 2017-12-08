cmake_minimum_required(VERSION 2.8)


project("MagicVR")
set(CMAKE_CXX_STANDARD 14)

include(cmake/enable_cxx_compiler_flag_if_supported.cmake)
#enable_cxx_compiler_flag_if_supported("-Wall")
#enable_cxx_compiler_flag_if_supported("-Wextra")
#enable_cxx_compiler_flag_if_supported("-pedantic")
#enable_cxx_compiler_flag_if_supported("-g")
enable_cxx_compiler_flag_if_supported("-Wno-deprecated-declarations")
enable_cxx_compiler_flag_if_supported("-lGL")
enable_cxx_compiler_flag_if_supported("-fext-numeric-literals")

include(.conan/conanbuildinfo.cmake)
conan_basic_setup()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
include(AddProject)

set(OPENSG_MODULES OSGBase OSGSystem OSGWindow OSGWindowGLUT OSGDrawable OSGUtil OSGGroup OSGFileIO OSGImageFileIO)

set(EXECUTABLE_OUTPUT_PATH ../exe/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../exe/)
add_project(${PROJECT_NAME}_cave
	MAIN_FILE "apps/cave.cpp"
	SOURCE_DIR "sources/"
	HEADER_DIR "includes/"
	CONFIGS "config/mono.csm"
	OPENSG_MODULES ${OPENSG_MODULES}
	CSM_MODULE
	VRPN_MODULE
)
add_project(${PROJECT_NAME}_desktop
	MAIN_FILE "apps/desktop.cpp"
	SOURCE_DIR "sources/"
	HEADER_DIR "includes/"
	CONFIGS "config/mono.csm"
	OPENSG_MODULES ${OPENSG_MODULES}
	CSM_MODULE
	VRPN_MODULE
)
if ("${LEAP_LIB_DIR}" STREQUAL "")
	set(LEAP_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/leap/x64)
	message("LEAP_LIB_DIR is not defined, fallback to default: ${LEAP_LIB_DIR}")
endif ()
target_link_libraries(${PROJECT_NAME}_cave ${LEAP_LIB_DIR}/libLeap.so -Wl,-rpath,${LEAP_LIB_DIR})
target_link_libraries(${PROJECT_NAME}_desktop ${LEAP_LIB_DIR}/libLeap.so -Wl,-rpath,${LEAP_LIB_DIR})
target_link_libraries(${PROJECT_NAME}_cave ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME}_desktop ${CONAN_LIBS})

if(WIN32)
	if("${CMAKE_CONFIGURATION_TYPES}" STREQUAL "Release")
		set(confTypeFolder "rel")
	elseif("${CMAKE_CONFIGURATION_TYPES}" STREQUAL "Debug")
		set(confTypeFolder "debug")
	else()
		 message( FATAL_ERROR "The build type ${CMAKE_CONFIGURATION_TYPES} is not supported")
	endif()
	set(OPENSG_BIN "${CMAKE_CURRENT_LIST_DIR}/../libraries/install/${libPathArchitecture}/opensg/bin/${confTypeFolder}")
	set(GLUT_BIN "${CMAKE_CURRENT_LIST_DIR}/../libraries/install/${libPathArchitecture}/freeglut/bin")
	set(INVRS_BIN "${CMAKE_CURRENT_LIST_DIR}/../libraries/install/${libPathArchitecture}/invrs/bin")
	set(TIFF_BIN "${CMAKE_CURRENT_LIST_DIR}/../libraries/install/${libPathArchitecture}/libtiff/bin")
	set(PNG_BIN "${CMAKE_CURRENT_LIST_DIR}/../libraries/install/${libPathArchitecture}/libpng/bin")
	set(ZLIB_BIN "${CMAKE_CURRENT_LIST_DIR}/../libraries/install/${libPathArchitecture}/zlib/bin")
	set(JPEG_BIN "${CMAKE_CURRENT_LIST_DIR}/../libraries/install/${libPathArchitecture}/libjpeg-turbo/bin")
	
	set(TEXT_OPENSG_CSM "SET opensg_BIN=${CMAKE_CURRENT_LIST_DIR}/../libraries/install/${libPathArchitecture}/opensg/bin/rel\n") # as csm is only compiled in release!
	set(TEXT_OPENSG_OTHER "SET opensg_BIN=${OPENSG_BIN}\n")
	
	set(TEXT_FOR_PATH "SET glut_bin=${GLUT_BIN}\nSET invrs_bin=${INVRS_BIN}\n")
	set(TEXT_FOR_PATH "${TEXT_FOR_PATH}SET tiff_bin=${TIFF_BIN}\nSET png_bin=${PNG_BIN}\nSET zlib_bin=${ZLIB_BIN}\n")
	set(TEXT_FOR_PATH "${TEXT_FOR_PATH}SET jpeg_bin=${JPEG_BIN}\n")	
	set(TEXT_FOR_PATH "${TEXT_FOR_PATH}SET PATH=%opensg_BIN%;%glut_bin%;%invrs_bin%;%tiff_bin%;%png_bin%;%zlib_bin%;%jpeg_bin%;%PATH%;")
	
	
	file(WRITE start_demo_desktop_${CMAKE_CONFIGURATION_TYPES}.bat "${TEXT_OPENSG_OTHER}${TEXT_FOR_PATH} \n.\\exe\\${CMAKE_CONFIGURATION_TYPES}\\${PROJECT_NAME}_desktop.exe" )
	file(WRITE start_demo_cave_mono_${CMAKE_CONFIGURATION_TYPES}.bat "${TEXT_OPENSG_OTHER}${TEXT_FOR_PATH} \n.\\exe\\${CMAKE_CONFIGURATION_TYPES}\\${PROJECT_NAME}_cave.exe -f config/mono.csm" )
	file(WRITE start_demo_cave_${CMAKE_CONFIGURATION_TYPES}.bat "${TEXT_OPENSG_OTHER}${TEXT_FOR_PATH} \n.\\exe\\${CMAKE_CONFIGURATION_TYPES}\\${PROJECT_NAME}_cave.exe -f config/lrz_cave_vrpn.csm" )
	file(WRITE start_csm.bat "${TEXT_OPENSG_CSM}${TEXT_FOR_PATH} \nstart \"front cmd\" \"csmrenderserver.exe\" -a 127.0.0.1 -g 800x600+100+100 -w front" )
else()
	file(WRITE start_demo_desktop_${CMAKE_CONFIGURATION_TYPES} "#!/bin/bash \n export OSG_LOAD_LIBS=OSGFileIO:OSGImageFileIO \n ./exe/${PROJECT_NAME}_desktop" )
	file(WRITE start_demo_cave_mono_${CMAKE_CONFIGURATION_TYPES} "#!/bin/bash \n export OSG_LOAD_LIBS=OSGFileIO:OSGImageFileIO \n ./exe/${PROJECT_NAME}_cave -f ${CMAKE_CURRENT_LIST_DIR}/config/mono.csm" )
	file(WRITE start_demo_cave_${CMAKE_CONFIGURATION_TYPES} "#!/bin/bash \n export OSG_LOAD_LIBS=OSGFileIO:OSGImageFileIO \n ./exe/${PROJECT_NAME}_cave -f /sw/config/opensg/csm/lrz_cave_vrpn.csm" )
	file(WRITE start_csm "#!/bin/bash \n${inVRs_ROOT_DIR}/bin/csmrenderserver -a 127.0.0.1 -g 800x600+100+100 -w front" )
	execute_process(COMMAND "chmod +x start_demo_desktop_${CMAKE_CONFIGURATION_TYPES}")
	execute_process(COMMAND "chmod +x start_demo_cave_mono_${CMAKE_CONFIGURATION_TYPES}")
	execute_process(COMMAND "chmod +x start_demo_cave_${CMAKE_CONFIGURATION_TYPES}")
	execute_process(COMMAND "chmod +x start_csm")
endif()
