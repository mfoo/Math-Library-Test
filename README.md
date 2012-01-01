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
* Permissive license. Accreditation is perfectly fine. Forcing distribution of
  source code isn't.

At the time of writing, the libraries I will be testing are
[Eigen](http://eigen.tuxfamily.org), [GLM](http://glm.g-truc.net/), and
[CML](http://cmldev.net/). These choices are largely influenced by reading
their websites and posts at the [Game Development
StackExchange](http://gamedev.stackexchange.com/) site:

* [Best C Math Library for Game
  Engine?](http://gamedev.stackexchange.com/questions/9924/best-c-math-library-for-game-engine)
* [High Performance Math Library for Vector And Matrix
  Calculations](http://stackoverflow.com/questions/5935075/high-performance-math-library-for-vector-and-matrix-calculations)
* [Complete Math Library for use in OpenGL ES 2.0
  Game?](http://gamedev.stackexchange.com/questions/8234/complete-math-library-for-use-in-opengl-es-2-0-game)

I intend to test each library on Linux, Mac OS X, Windows and Android using
CMake.

Libraries Overview
==================

This section contains my notes to help understand the design choices and
advantages and disadvantages of each library.

Configurable Math Library (CML)
-------------------------------

This is a free library designed for games, graphics, and computational geometry
applications. Listed [features](http://cmldev.net/?page_id=8) include:

* Vector, matrix, and quarternion classes
* Templated headers so can be used for arbitrary types
* Arbitrary sized vectors and matrices (fixed or dynamically resizable)
* Conversions between polar, cylindrical, spherical, and Cartesian coordinates
* A large library of functions for the construction and manipulation of
  transforms in 2D and 3D

CML's [design notes](http://cmldev.net/?page_id=594) state that it is meant to
be cross-platform and portable and therefore doesn't contain any platform
specific optimisations, but it is possible to include them in the future if
there is specific interest.

There's only one header file to include, `cml/cml.h`.

CML contains quite a nice way of creating an abstraction layer between existing
math library objects and CML objects, allowing the use of other math library
data types in CML library functions. See [here](http://cmldev.net/?p=424).

CML only has a few [examples](http://cmldev.net/?p=402). Hasn't been updated in
a while.  Contains useful functions for working with OpenGL or DirectX though,
including replacements for things like gluLookAt().

CML is released under the [Boost Software License](http://cmldev.net/?p=430).
This means that you're allowed to use and profit from the library as long as
when distributing CML or any modifications you have made to CML, you keep the
Boost Software License text in each file.

Eigen
-----

This library has by far the most detailed and descriptive tutorial section with
many code samples. It is also worth noting that it seems to be the most
frequently updated and the most up-to-date (at the time of writing the most
recent release, 3.0.4, was 3.5 weeks ago).

Like GLM, it is very easy to pass the class objects directly to OpenGL,
although in Eigen this is performed by an [unsupported OpenGL
module](http://eigen.tuxfamily.org/dox-devel/unsupported/group__OpenGLSUpport__Module.html)
which provides a few functions such as glTranslate and glRotate.

    // You need to add path_to_eigen/unsupported to your include path.
    #include <Eigen/OpenGLSupport> // ...  Vector3f x, y; Matrix3f rot;
    
    glVertex(y + x * rot);

    Quaternion q; glRotate(q);

Provides a large number of array, matrix, and vector types with [many
operators](http://eigen.tuxfamily.org/dox/QuickRefPage.html#QuickRef_Types). 



Eigen is licensed under the LGPL which is quite restrictive and usually would
exclude a library based on my requirements. However, Eigen has a large
[Licensing FAQ](http://eigen.tuxfamily.org/index.php?title=Licensing_FAQ) which
tries to answer any licensing questions people might have. Their main point is
that as Eigen is a header only library, it does not count as a "Combined Work"
under the LGPL it can be therefore used entirely under Section 3. This states
that to use Eigen you must:

* Give prominent notice with each copy of the object code that the Library is
  used in it and that the Library and its use are covered by this License. The
  Eigen FAQ states that 'the bottom of a README file or of a website would be
  prominent enough for us'.
* Accompany the object code with a copy of the GNU GPL and this license
  document.

This assumes that you're using Eigen unmodified. If you are planning to make
changes to Eigen and release it, then you must also make the modifications
available under the LGPL.

OpenGL Math Library (GLM)
-------------------------
GLM's main design to be very familiar to those who know GLSL as it uses classes
and functions that use the GLSL naming conventions. It also seems to provide
all of the functionality that I might need in the future.

Includes several code samples, more than CML. Many more located in the manual.

Includes features such as:

* Math for splines
* Math for colour spaces
* Random numbers
* Simplex noise generation
* Conversion of Euler angles

There's only one header file to include, `glm/glm.hpp`. `glm/ext.hpp` can be
included to add extended features (non GLSL features).

The design choice to follow GLSL conventions allows the library to be intuitive
and easy to use, especially given that data alignment is compatible with gl
functions. E.g:

    glm::vec4 v(0);
    glm::mat4 m(0);
    glVertex3fv(glm::value_ptr(v))
    glLoadMatrixfv(glm::value_ptr(m));

The manual pdf file link is broken but a slightly out of date version can be
found
[here](https://bitbucket.org/alfonse/gltut/src/6332c7f79903/glm-0.9.0.0/doc/glm-manual.pdf).
I've sent the maintainer an email and hopefully this will be fixed shortly. 

GLM is licensed under the [MIT
License](http://en.wikipedia.org/wiki/MIT_License) (Expat License) which is
very permissive and means GLM is a good candidate for any project requiring a
math library.

Things to test
==============
This is for gaming applications. Features that I can think of that need testing
are:
* Matrix operations - including addition, subtraction, multiplication,
  inversion, transposition, translation, rotation, scale
* Vector operations - cross/dot product, normalisation, zeroing, magnitude,
  length2, scalar operands, normal calculation
* Euler angle + Quarternion operations - rotation, interpolation,
  conversion, inversion, multiplication
* Coordinate system conversion (Cartesian, spherical)
* Random numbers - generator speed, period, [statistical
  randomness](http://en.wikipedia.org/wiki/Diehard_tests)
* Possibly noise generation
* Ease of integration with gl functions like glTranslate()

I have posted a question on the [Game Development Stackexchange](http://gamedev.stackexchange.com/questions/21711/what-should-be-taken-into-consideration-when-choosing-a-math-library-for-games)
site asking if there are other features I'm forgetting.

Running the tests
=================
    git clone git@github.com:mfoo/Math-Library-Test.git MathTest
    cd MathTest
    mkdir build
    cd build
    cmake ..

Results
=======
So far I've tested matrix addition and multiplication. `src/Main.cpp` contains
code that will generate two lists of 10 million 4x4 float matrices for each
library, populate them with random float values, and then add each one from the
first column to the second. It will then do the same for multiplication. It
will repeat this step 10 times and print out how long it took for each library.

My results for addition and subtraction are incredible. Note to self: find out
if I've made a mistake here. I'm using a 2.2ghz early 2011 MacBook Pro.

    Martin-Foots-MacBook-Pro:build martin$ cd release
    Martin-Foots-MacBook-Pro:release martin$ cmake -DCMAKE_BUILD_TYPE=RELEASE ../..
    ...
    Martin-Foots-MacBook-Pro:release martin$ make
    ...
    [100%] Built target Main
    Martin-Foots-MacBook-Pro:release martin$ ./Main 
    Testing Eigen library Matrix4f class.
    Performing additions.
    Took 300 milliseconds.
    Performing multiplications.
    Took 866 milliseconds.
    Testing GLM library Matrix4f class.
    Performing additions.
    Took 753 milliseconds.
    Performing multiplications.
    Took 3906 milliseconds.
    Testing CML library Matrix4f class.
    Performing additions.
    Took 928 milliseconds.
    Performing multiplications.
    Took 5374 milliseconds.
    Martin-Foots-MacBook-Pro:release martin$ cd ../debug/
    Martin-Foots-MacBook-Pro:debug martin$ cmake -DCMAKE_BUILD_TYPE=DEBUG ../..
    ...
    Martin-Foots-MacBook-Pro:debug martin$ make
    ...
    [100%] Built target Main
    Martin-Foots-MacBook-Pro:debug martin$ ./Main 
    Testing Eigen library Matrix4f class.
    Performing additions.
    Took 73905 milliseconds.
    Performing multiplications.
    Took 190271 milliseconds.
    Testing GLM library Matrix4f class.
    Performing additions.
    Took 22578 milliseconds.
    Performing multiplications.
    Took 73164 milliseconds.
    Testing CML library Matrix4f class.
    Performing additions.
    Took 124408 milliseconds.
    Performing multiplications.
    Took 210810 milliseconds.

The results in table form:

            Time (ms) for 10,000,000 operations
            Debug (no optimisations)            Release
            Addition        Multiplication      Addition        Multiplication
    Eigen   73905           190271              300             866
    GLM     22578           73164               753             3906
    CML     124408          210810              928             5374

GLM was by far the fastest without any compiler optimisations. Eigen was
incredibly fast with them turned on.
