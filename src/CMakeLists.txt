cmake_minimum_required(VERSION 3.2)

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.12")
    message(STATUS "CMake version ${CMAKE_VERSION}")
    cmake_policy(SET CMP0074 NEW)
endif ()

if(STATIC_LINK_LIBS)
        message(STATUS "CMake STATIC_LINK_LIBS = ${STATIC_LINK_LIBS}")
        if (MSVC)
            string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
            string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_MINSIZEREL ${CMAKE_CXX_FLAGS_MINSIZEREL})
            string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
            string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
        endif ()
endif ()

SET(TARGT_NAME ip_filter)
SET(ALL_SOURCE ip_filter.cpp main.cpp)
SET(ALL_INCLUDE "../include/" "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/..")
SET(ALL_LIBS my_lib)

add_executable(${TARGT_NAME} ${ALL_SOURCE})
target_include_directories(${TARGT_NAME} PUBLIC ${ALL_INCLUDE})

if (MSVC)

    message(STATUS "MSVC")

    set_target_properties(${TARGT_NAME} PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED ON
      COMPILE_OPTIONS "/permissive-;/Zc:wchar_t"
    )

else()

        set_target_properties(${TARGT_NAME} PROPERTIES
                  CXX_STANDARD 17
                  CXX_STANDARD_REQUIRED ON
                  COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

endif ()


target_link_libraries(${TARGT_NAME} ${ALL_LIBS})
