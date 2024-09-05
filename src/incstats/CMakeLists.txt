add_library(incstats SHARED src/incstats.c)
# Don't link math library under windows platforms as it causes an linker 
# error with MSVC.
if(NOT WIN32)
  target_link_libraries(incstats m)
endif()
# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(incstats
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:include>
    PRIVATE
      src
)

# Depend on a library that we (may) defined in the top-level file
# target_link_libraries()

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS incstats EXPORT incstats-export
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR} # This is for Windows
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# this makes the project importable from the install directory
install(EXPORT incstats-export
  FILE
    incstatsConfig.cmake
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/incstats
)
# This makes the project importable from the build directory
export(TARGETS incstats FILE incstatsConfig.cmake)

# Every library has unit tests, of course
add_executable(testincstats test/test_incstats.c)

target_link_libraries(testincstats incstats)
#benchmarkincstats depends on sys/time.h which is not available on Winbdows systems.
if(NOT WIN32)
  add_executable(benchmarkincstats test/benchmark_incstats.c)
  target_link_libraries(benchmarkincstats incstats)
endif()
add_test(testincstats testincstats)

