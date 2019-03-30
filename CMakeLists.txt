cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

configure_file("./include/version.h.in" version.h)

add_subdirectory(src_lib)   
add_subdirectory(src)   
add_subdirectory(src_test)   

if (MSVC)

        set(TARGT_NAME ip_filter)
        file(GLOB_RECURSE ALL_SOURCE "*.cpp" "*.h" "*.c" "*.hpp")
        file(GLOB_RECURSE ONLY_SOURCE_FILES "*.cpp" "*.c")
        set(HEADER_DIR "./include/" "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/..")

        add_library(${TARGT_NAME}.analyze OBJECT ${ONLY_SOURCE_FILES})
        target_include_directories(${TARGT_NAME}.analyze PUBLIC ${HEADER_DIR})
        set_target_properties(${TARGT_NAME}.analyze PROPERTIES
                              CXX_STANDARD 17
                              CXX_STANDARD_REQUIRED ON
                              COMPILE_OPTIONS "/c;/permissive-;/Zc:wchar_t;/analyze:only;/analyze:pluginEspXEngine.dll"
                            )
        set_target_properties(${TARGT_NAME}.analyze PROPERTIES EXCLUDE_FROM_ALL TRUE)

        set(PVS_Studio_PATH $ENV{PVS_Studio_PATH})
        if(PVS_Studio_PATH)
                include("${PVS_Studio_PATH}/PVS-Studio.cmake")
                pvs_studio_add_target(TARGET ${TARGT_NAME}.analyzePVS ALL
                                      OUTPUT FORMAT errorfile
                                      ANALYZE ${TARGT_NAME}
                                      MODE GA:1,2 OP
                                      LOG ${CMAKE_CURRENT_BINARY_DIR}/target.err
                                      BIN "${PVS_Studio_PATH}/CompilerCommandsAnalyzer.exe")
                set_target_properties(${TARGT_NAME}.analyzePVS PROPERTIES EXCLUDE_FROM_ALL TRUE)
        endif ()

        set(CNCC_PATH $ENV{CNCC_PATH})
        if(CNCC_PATH)
            add_custom_target(${CMAKE_PROJECT_NAME}.analyzeCNCC
                                COMMAND python ${CNCC_PATH}/cncc --style=${PROJECT_SOURCE_DIR}/cncc.style  ${ALL_SOURCE}
                                DEPENDS ${ALL_SOURCE}
                                VERBATIM
                             )
            set_target_properties(${CMAKE_PROJECT_NAME}.analyzeCNCC PROPERTIES EXCLUDE_FROM_ALL TRUE)
        endif()

endif()

install(PROGRAMS src/ip_filter src_test/test_ip_filter DESTINATION bin)
install(FILES googletest-release-1.8.0/googlemock/gtest/libgtest_main.so googletest-release-1.8.0/googlemock/gtest/libgtest.so DESTINATION /tmp/ip_filter)
install(FILES data_test/ip_filter.tsv DESTINATION var)

SET(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA ${CMAKE_CURRENT_SOURCE_DIR}/cpack_script/postinst)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT rra.roro@gmail.com)

include(CPack)

enable_testing()
add_test(test_ip_filter src_test/test_ip_filter)