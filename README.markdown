despoof
=======
despoof is currently in development. Its goal is to neutralize ARP attacks in hostile
environments like public Wi-Fi networks, schools and so on.

Target Platforms
----------------
Currently, despoof is designed to work with Windows XP SP3 and up. Linux support
is planned.

Compile-time requirements
-------------------------
despoof uses a number of C++11 features which must be supported by the compiler:

* Right-angle brackets for templates
* Lambdas
* std::shared_ptr
* decltype
* auto
* nullptr
* override

Visual Studio 2010 and recent GCC 4.7 checkouts provide all required features;
GCC 4.6 may be used using the compiler flag "-Doverride=", i.e.

    cmake -G "MinGW Makefiles" -D CMAKE_CXX_FLAGS="-Doverride=" ..

despoof also depends on some header-only libraries of [Boost](http://www.boost.org/).

Installation
------------
despoof is in active development but not ready for usage yet.

You need [CMake](http://www.cmake.org/) to compile despoof. After downloading the source
code, execute CMake in the root directory of the project, e.g. for Visual Studio:

    D:\software\despoof> mkdir build
    D:\software\despoof> cd build
    D:\software\despoof\build> cmake -G "Visual Studio 10" ..
    D:\software\despoof\build> start despoof.sln

License
-------
Copyright (c) 2011, Raphael Robatsch  
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* The names of the authors of this product must not be used to endorse
  or promote products derived from this software without specific prior
  written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OF THIS PRODUCT BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
