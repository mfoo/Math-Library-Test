cmake_minimum_required(VERSION 2.8)

# Name of the cmake project.
project(MathLibraryTest)

# All libraries are header only.
include_directories(lib/cml-1_0_2)
include_directories(lib/eigen-eigen-13a11181fc5a)
include_directories(lib/glm-0.9.3.B)

# NOTE:
# This next section is copy pasted from the Eigen CMakeLists.txt located in the
# lib folder. I have just set some defaults to ON.

# guard against bad build-type strings

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnon-virtual-dtor -Wno-long-long -ansi -Wundef -Wcast-align -Wchar-subscripts -Wall -W -Wpointer-arith -Wwrite-strings -Wformat-security -fexceptions -fno-check-new -fno-common -fstrict-aliasing")
  set(CMAKE_CXX_FLAGS_DEBUG "-g3")
  set(CMAKE_CXX_FLAGS_RELEASE "-g0 -O2")

  check_cxx_compiler_flag("-Wno-variadic-macros" COMPILER_SUPPORT_WNOVARIADICMACRO)
  if(COMPILER_SUPPORT_WNOVARIADICMACRO)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-variadic-macros")
  endif()

  check_cxx_compiler_flag("-Wextra" COMPILER_SUPPORT_WEXTRA)
  if(COMPILER_SUPPORT_WEXTRA)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
  endif()

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

endif(CMAKE_COMPILER_IS_GNUCXX)

if(ANDROID)
    add_definitions(-D__STDC_INT64__)
    #    set(CMAKE_REQUIRED_INCLUDES 
    #  ${ANDROID_NDK_SYSROOT}/usr 
    #  ${ANDROID_NDK_SYSROOT}/usr/include
    #  ${CMAKE_REQUIRED_INCLUDES})
    #
    #set(CMAKE_PREFIX_PATH
    #        ${ANDROID_NDK_SYSROOT}
    #        ${CMAKE_PREFIX_PATH})
    #
    
    #set(ARM_TARGET "armeabi-v7a")

    # Enable NEON
    option(EIGEN_TEST_NEON "Enable/Disable Neon in tests/examples" ON)
  if(EIGEN_TEST_NEON)
      #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=softfp -mfpu=neon -mcpu=cortex-a8")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=softfp -mfpu=neon")
    message(STATUS "Enabling NEON in tests/examples")
  endif()


    # With Android we build a shared library called MathTest rather than an
    # executable.

    # First overwrite the android-cmake output path.
    #set(LIBRARY_OUTPUT_PATH_ROOT "${PROJECT_SOURCE_DIR}/android/libs/${ARM_TARGET}" CACHE PATH "Output path for JNI libs")
    set(LIBRARY_OUTPUT_PATH_ROOT "${PROJECT_SOURCE_DIR}/android" CACHE PATH
        "library output path")

    message(STATUS "Library output path root is " ${LIBRARY_OUTPUT_PATH_ROOT})
    set(ARM_TARGET "armeabi" CACHE STRING "arm target to use" FORCE)
   message(STATUS ${ARM_TARGET})
   add_library(MathTest SHARED src/Driver.cpp src/mother.cpp src/androidactivity.cpp)
   # add_library(MathTest SHARED src/androidactivity.cpp src/mother.cpp)
else()
  option(EIGEN_TEST_SSE2 "Enable/Disable SSE2 in tests/examples" ON)
  if(EIGEN_TEST_SSE2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
    message(STATUS "Enabling SSE2 in tests/examples")
  endif()

  option(EIGEN_TEST_SSE3 "Enable/Disable SSE3 in tests/examples" ON)
  if(EIGEN_TEST_SSE3)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse3")
    message(STATUS "Enabling SSE3 in tests/examples")
  endif()

  option(EIGEN_TEST_SSSE3 "Enable/Disable SSSE3 in tests/examples" ON)
  if(EIGEN_TEST_SSSE3)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mssse3")
    message(STATUS "Enabling SSSE3 in tests/examples")
  endif()

  option(EIGEN_TEST_SSE4_1 "Enable/Disable SSE4.1 in tests/examples" ON)
  if(EIGEN_TEST_SSE4_1)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1")
    message(STATUS "Enabling SSE4.1 in tests/examples")
  endif()

  option(EIGEN_TEST_SSE4_2 "Enable/Disable SSE4.2 in tests/examples" ON)
  if(EIGEN_TEST_SSE4_2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2")
    message(STATUS "Enabling SSE4.2 in tests/examples")
  endif()

  option(EIGEN_TEST_ALTIVEC "Enable/Disable AltiVec in tests/examples" OFF)
  if(EIGEN_TEST_ALTIVEC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maltivec -mabi=altivec")
    message(STATUS "Enabling AltiVec in tests/examples")
  endif()
  check_cxx_compiler_flag("-fopenmp" COMPILER_SUPPORT_OPENMP)
  if(COMPILER_SUPPORT_OPENMP)
      option(EIGEN_TEST_OPENMP "Enable/Disable OpenMP in tests/examples" ON)
    if(EIGEN_TEST_OPENMP)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
      message(STATUS "Enabling OpenMP in tests/examples")
    endif()
  endif()

    # Add a test program.
add_executable(Main src/mother.c src/Main.cpp src/Driver.cpp)
endif(ANDROID)
