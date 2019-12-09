cmake_minimum_required(VERSION 3.10.0)

project(uwp_compat VERSION 0.1.0 LANGUAGES CXX)

add_library(uwp_compat
  include/uwp_compat/dlfcn.h
  include/uwp_compat/encoding.h
  include/uwp_compat/path.h
  include/uwp_compat/random.h
  include/uwp_compat/uwp_compat.h
  src/dlfcn.cpp
  src/encoding.cpp
  src/internal.hpp
  src/path.cpp
  src/process.cpp
  src/random.cpp
)

target_compile_definitions(uwp_compat
  PRIVATE
  $<$<CONFIG:Debug>:DEBUG>
  $<$<CONFIG:RelWithDebInfo>:NDEBUG>
)

target_include_directories(uwp_compat
  PRIVATE
    include/
    src/
  INTERFACE
    $<INSTALL_INTERFACE:include>
)

target_compile_options(uwp_compat
  PRIVATE
    # /ZW
    /EHsc
    /MP
    /std:c++17
)

set_target_properties(uwp_compat PROPERTIES
  OUTPUT_NAME uwp_compat
  OUTPUT_NAME_DEBUG uwp_compatd
  COMPILE_PDB_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
  COMPILE_PDB_NAME uwp_compat
  COMPILE_PDB_NAME_DEBUG uwp_compatd
)

target_link_libraries(uwp_compat
  PRIVATE
    $<$<CONFIG:Debug>:vccorlibd.lib>
    $<$<CONFIG:RelWithDebInfo>:vccorlib.lib>
    $<$<CONFIG:Debug>:msvcrtd.lib>
    $<$<CONFIG:RelWithDebInfo>:msvcrt.lib>
  PUBLIC
    kernel32.lib
)

target_link_options(uwp_compat PRIVATE
  /NODEFAULTLIB:vccorlibd
  /NODEFAULTLIB:msvcrtd
  /NODEFAULTLIB:vccorlib
  /NODEFAULTLIB:msvcrt
  /INCREMENTAL:NO
  /debug:full
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(TARGETS uwp_compat EXPORT ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

install(DIRECTORY
  ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include/
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo/uwp_compat.pdb
  DESTINATION lib
  CONFIGURATIONS RelWithDebInfo
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/Debug/uwp_compatd.pdb
  DESTINATION lib
  CONFIGURATIONS Debug
)

install(EXPORT ${PROJECT_NAME}
  FILE
  ${PROJECT_NAME}.cmake
  NAMESPACE
    ${PROJECT_NAME}::
  DESTINATION
    lib/cmake/${PROJECT_NAME}
)

install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION
    lib/cmake/${PROJECT_NAME}
)

export(TARGETS ${PROJECT_NAME}
  FILE
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  NAMESPACE ${PROJECT_NAME}::
)