cmake_minimum_required(VERSION 3.2)

add_executable(ip_filter ip_filter.cpp main.cpp)
target_include_directories(ip_filter PUBLIC "../include/" "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/..")

if (MSVC)

    message(STATUS "MSVC")

	set_target_properties(ip_filter PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
      COMPILE_OPTIONS "/permissive-;/Zc:wchar_t"
    )

else()

	set_target_properties(ip_filter PROPERTIES
		  CXX_STANDARD 17
		  CXX_STANDARD_REQUIRED ON
		  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
	)

endif ()


target_link_libraries(ip_filter my_lib)