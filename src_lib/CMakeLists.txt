cmake_minimum_required(VERSION 3.2)

add_library(my_lib lib.cpp CLParser.cpp tchar_dummy.cpp)
target_include_directories(my_lib PUBLIC "../include/" "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/.." )

if (MSVC)

    message(STATUS "MSVC")

	set_target_properties(my_lib PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
      COMPILE_OPTIONS "/permissive-;/Zc:wchar_t"
    )

else()

	set_target_properties(my_lib PROPERTIES
		  CXX_STANDARD 17
		  CXX_STANDARD_REQUIRED ON
		  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
	)

endif ()

