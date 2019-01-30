cmake_minimum_required(VERSION 3.2)

project(custom_tie_tulp VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

configure_file("./include/version.h.in" version.h)

add_subdirectory(src_lib)   
add_subdirectory(src)   
add_subdirectory(src_test)   

install(PROGRAMS src/tie_tulp_cli src_test/test_tie_tulp DESTINATION bin)
install(PROGRAMS googletest-release-1.8.0/googlemock/gtest/libgtest_main.so googletest-release-1.8.0/googlemock/gtest/libgtest.so DESTINATION lib)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT rra.roro@gmail.com)

include(CPack)

enable_testing()
add_test(test_tie_tulp src_test/test_tie_tulp)