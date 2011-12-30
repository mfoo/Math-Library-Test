C++ Math Library Test
=====================

I am in the process of selecting a math library to use for game development in
C++ and this repo contains a small test of several libraries before I make a
decision on which to use. When I have finished my test I will add the results
here.

My requirements are:

* C++
* Matrix operations
* Vector operations
* Complex number support
* Quarternian operations
* Cross-platform, easy to compile on different platforms with different
  compilers.
* Fast. SIMD instruction support is preferred.
* Easy to use and understand.
* Permissive license. Accreditation is acceptable.

At the time of writing, the libraries I will be testing are
[Eigen](http://eigen.tuxfamily.org), [GLM](http://glm.g-truc.net/), and
[CML](http://cmldev.net/). These choices are largely influenced by reading
their over pages and posts at the
[Game Development StackExchange](http://gamedev.stackexchange.com/) site:

* [High Performance Math Library for Vector And Matrix Calculations](http://stackoverflow.com/questions/5935075/high-performance-math-library-for-vector-and-matrix-calculations)
* [Complete Math Library for use in OpenGL ES 2.0 Game?](http://gamedev.stackexchange.com/questions/8234/complete-math-library-for-use-in-opengl-es-2-0-game)

This project will be able to be built and run with CMake when it is finished. I
intend to test each library on Linux, Mac OS X, Windows and Android.

Libraries Overview
==================
This section is to help understand the design choices and advantages and
disadvantages of each library.

Configurable Math Library
-------------------------

Eigen
-----


OpenGL Math Library
-------------------

Running the tests
=================
    git clone git@github.com:mfoo/Math-Library-Test.git MathTest
    cd MathTest
    mkdir build
    cd build
    cmake ..

This will generate build files using the default for your environment.
