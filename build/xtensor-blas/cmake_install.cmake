# Install script for directory: /home/busoye_tm/Documents/matthew/tests/xtensor-blas

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/xtensor-blas" TYPE FILE FILES
    "/home/busoye_tm/Documents/matthew/tests/xtensor-blas/include/xtensor-blas/xblas.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtensor-blas/include/xtensor-blas/xblas_utils.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtensor-blas/include/xtensor-blas/xblas_config.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtensor-blas/include/xtensor-blas/xblas_config_cling.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtensor-blas/include/xtensor-blas/xlapack.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtensor-blas/include/xtensor-blas/xlinalg.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/busoye_tm/Documents/matthew/tests/xtensor-blas/include/xflens" REGEX "/[^/]*\\.tgz$" EXCLUDE REGEX "/Makefile$" EXCLUDE REGEX "/dummy\\.in\\.cc$" EXCLUDE REGEX "/filter\\.pm$" EXCLUDE REGEX "/CMakeLists\\.txt$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" TYPE FILE FILES "/home/busoye_tm/Documents/matthew/tests/build/xtensor-blas/xtensor-blas.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/xtensor-blas" TYPE FILE FILES
    "/home/busoye_tm/Documents/matthew/tests/build/xtensor-blas/xtensor-blasConfig.cmake"
    "/home/busoye_tm/Documents/matthew/tests/build/xtensor-blas/xtensor-blasConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/xtensor-blas/xtensor-blasTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/xtensor-blas/xtensor-blasTargets.cmake"
         "/home/busoye_tm/Documents/matthew/tests/build/xtensor-blas/CMakeFiles/Export/167a3f61f1613c1fc94b0ceb55a6cf36/xtensor-blasTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/xtensor-blas/xtensor-blasTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/xtensor-blas/xtensor-blasTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/xtensor-blas" TYPE FILE FILES "/home/busoye_tm/Documents/matthew/tests/build/xtensor-blas/CMakeFiles/Export/167a3f61f1613c1fc94b0ceb55a6cf36/xtensor-blasTargets.cmake")
endif()

