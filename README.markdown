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
* Smart Pointers
* decltype
* auto
* nullptr
* override

Develeopment happens on Visual C++ 10.0, although Despoof should also compile under MinGW
with GCC 4.6 provided that the keyword `override` is define'd away by the preprocessor.

despoof also depends on some libraries of [Boost](http://www.boost.org/) (Boost.Locale must
be compiled; the ICU backend is not needed) and on the
[WinPcap Developer's pack](http://www.winpcap.org/devel.htm).

Run-time requirements
---------------------
[WinPcap](http://www.winpcap.org/) is required, along with the
[Visual C++ 2010 Redistributable](http://www.microsoft.com/download/en/details.aspx?id=5555).

Installation
------------
You need [CMake](http://www.cmake.org/) to compile despoof. After downloading the source
code, execute CMake in the root directory of the project, e.g. for Visual Studio:

    D:\software\despoof> mkdir build
    D:\software\despoof> cd build
    D:\software\despoof\build> cmake -G "Visual Studio 10" ..
    D:\software\despoof\build> start despoof.sln

After compiling the projects, despoof is ready for usage.

Running
-------
The `despoof` executable runs despoof as a background process:

    Usage: build\debug\despoof  [-h] [-i <n>] [-o <mod>] [-n <mod>]
    
      -h, --help           Displays this help text
      -i, --interval=<n>   Time of one despoof iteration in milliseconds; Default: 750
      -o, --log=<mod>      Name of the log module, without the "log" prefix; Default: console
      -n, --network=<mod>  Name of the network module, without the "nw" prefix; Default: pcap

All parameters are optional; the only parameter which may need to be changed is the interval.
The shorter the interval is, the smaller is the time window for attackers to send out their
counter-attacks. The downside is that a smaller interval causes more network traffic, however, in
a fast LAN this should be no problem.

Service
-------
Despoof can also be run as service. It can be installed using `despoof-svctool --install`. The
svctool accepts the following parameters:

    Usage: build\debug\despoof-svctool  [-iusth] [-y <auto|manual|disabled>] [-a <args>] [-d [<command>]]
    
      -i, --install        Installs the despoof service
      -u, --uninstall      Removes the despoof service
      -s, --start          Starts the despoof service
      -t, --stop           Stops the despoof service
                           
                           --install specific:
      -y, --start-type=<auto|manual|disabled> Start type of the service; Default: "auto"
      -a, --arguments=<args> Arguments to pass to despoof; see "despoof --help"
      -d, --debug=[<command>] Runs the service in a debugger; Default command is "ntsd -server npipe:pipe=despoof_debug -noio"
      -h, --help           Displays this help text
    
    At least one of --install/uninstall/start/stop must be specified. The following combinations are valid:
      --install
      --start
      --install    --start
      --uninstall
      --stop
      --uninstall  --stop

The `--arguments` parameter is only used if the service is started as part of Windows' startup procedure;
If it is started manually it is not honored. You must use the --args parameter again for the 'start' action,
or use Windows' 'sc' utility: `sc start despoof <args>`.

The service stores its logfiles in `LocalService`'s local AppData folder; Depending on your Windows version this might
be in `%SystemRoot%\ServiceProfiles\LocalService\AppData\Local` or in `(Documents and Settings)\LocalService\Local Settings`.
The log files are in the subdirectory `tape software\Despoof`.

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
