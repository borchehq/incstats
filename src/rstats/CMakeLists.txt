add_library(rstats SHARED src/rstats.c)
target_link_libraries(rstats m)
# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(rstats
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:include>
    PRIVATE
      src
)

# Depend on a library that we (may) defined in the top-level file
# target_link_libraries()

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS rstats EXPORT rstats-export
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR} # This is for Windows
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# this makes the project importable from the install directory
install(EXPORT rstats-export
  FILE
    rstatsConfig.cmake
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/rstats
)
# This makes the project importable from the build directory
export(TARGETS rstats FILE rstatsConfig.cmake)

# Every library has unit tests, of course
add_executable(testrstats test/test_rstats.c)
add_executable(benchmarkrstats test/benchmark_rstats.c)

target_link_libraries(testrstats rstats)
target_link_libraries(benchmarkrstats rstats)

add_test(testrstats testrstats)

