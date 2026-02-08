# Install script for directory: /home/busoye_tm/Documents/matthew/tests/xtl

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/xtl" TYPE FILE FILES
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xbasic_fixed_string.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xbase64.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xclosure.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xcompare.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xcomplex.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xcomplex_sequence.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xspan.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xspan_impl.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xdynamic_bitset.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xfunctional.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xhalf_float.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xhalf_float_impl.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xhash.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xhierarchy_generator.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xiterator_base.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xjson.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xmasked_value_meta.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xmasked_value.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xmeta_utils.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xmultimethods.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xoptional_meta.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xoptional.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xoptional_sequence.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xplatform.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xproxy_wrapper.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xsequence.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xsystem.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xtl_config.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xtype_traits.hpp"
    "/home/busoye_tm/Documents/matthew/tests/xtl/include/xtl/xvisitor.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/xtl" TYPE FILE FILES
    "/home/busoye_tm/Documents/matthew/tests/build/xtl/xtlConfig.cmake"
    "/home/busoye_tm/Documents/matthew/tests/build/xtl/xtlConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/xtl/xtlTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/xtl/xtlTargets.cmake"
         "/home/busoye_tm/Documents/matthew/tests/build/xtl/CMakeFiles/Export/2fc63ec57839ed115fc15a5438bb5aec/xtlTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/xtl/xtlTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/cmake/xtl/xtlTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/xtl" TYPE FILE FILES "/home/busoye_tm/Documents/matthew/tests/build/xtl/CMakeFiles/Export/2fc63ec57839ed115fc15a5438bb5aec/xtlTargets.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" TYPE FILE FILES "/home/busoye_tm/Documents/matthew/tests/build/xtl/xtl.pc")
endif()

