cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

configure_file("./include/version.h.in" version.h)

add_subdirectory(src_lib)   
add_subdirectory(src)   
add_subdirectory(src_test)   

install(PROGRAMS src/ip_filter src_test/test_ip_filter DESTINATION bin)
install(CODE "
  if (NOT EXISTS \"lib/libgtest_main.so\")
        file(INSTALL ./googletest-release-1.8.0/googlemock/gtest/libgtest_main.so DESTINATION \"lib\")
  endif()
  if (NOT EXISTS \"lib/libgtest.so\")
        file(INSTALL ./googletest-release-1.8.0/googlemock/gtest/libgtest.so DESTINATION \"lib\")
  endif()
 ")

#install(FILES googletest-release-1.8.0/googlemock/gtest/libgtest_main.so googletest-release-1.8.0/googlemock/gtest/libgtest.so DESTINATION lib)
install(FILES data_test/ip_filter.tsv DESTINATION var)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT rra.roro@gmail.com)

include(CPack)

enable_testing()
add_test(test_ip_filter src_test/test_ip_filter)