# VND project

Danilo Moreira

Kelly Wagemann

## What you need

- Openjdk version "1.8.0_265"
- Python version 3.5 or greater. 
- gcc/g++ versions 4.9 and above.
- OS that supports ns3. This project is being delevoped in Ubuntu 18.04LTS. 
- A copy of this repository in your device. 

### Prerequisites for NS3 

The next steps assume you are working in Ubuntu 18.04 LTS.
For other OS, please refer to the official installation guide at https://www.nsnam.org/wiki/Installation

In order to use NS3, you need to install the following packages beforehand:

- sudo apt-get install g++ python3
- sudo apt-get install g++ python3 python3-dev pkg-config sqlite3
- sudo apt-get install python3-setuptools git
- sudo apt-get install qt5-default mercurial
- sudo apt-get install gir1.2-goocanvas-2.0 python-gi python-gi-cairo python-pygraphviz python3-gi python3-gi-cairo python3-pygraphviz gir1.2-gtk-3.0 ipython ipython3  
- sudo apt-get install openmpi-bin openmpi-common openmpi-doc libopenmpi-dev
- sudo apt-get install autoconf cvs bzr unrar
- sudo apt-get install gdb valgrind 
- sudo apt-get install uncrustify
- sudo apt-get install doxygen graphviz imagemagick
- sudo apt-get install texlive texlive-extra-utils texlive-latex-extra texlive-font-utils dvipng latexmk
- sudo apt-get install python3-sphinx dia
- sudo apt-get install gsl-bin libgsl-dev libgsl23 libgslcblas0
- sudo apt-get install tcpdump
- sudo apt-get install sqlite sqlite3 libsqlite3-dev
- sudo apt-get install libxml2 libxml2-dev
- sudo apt-get install cmake libc6-dev libc6-dev-i386 libclang-6.0-dev llvm-6.0-dev automake pip
- python3 -m pip install --user cxxfilt
- sudo apt-get install libgtk-3-dev
- sudo apt-get install vtun lxc uml-utilities
- sudo apt-get install libboost-signals-dev libboost-filesystem-dev

### Prerequisites for NetAnim 

In case you want to use the NetAnim animator, you need to install the following packages beforehand:

- sudo apt-get install mercurial
- sudo apt-get install qt4-dev-tools

## Setup 

To run files, we'll use waf. You can find it in the ns-allinone-3.31/ns-3.31 folder. 

First, you need to configure waf. Execute the following command: 
- CXXFLAGS="-O3" ./waf configure 

There are many options you can provide to waf configuration. 

In order to be able to run files from the ns-allinone-3.31/ns-3.31/examples folder, execute the following command: 
- ./waf --enable-examples configure 

In order to be able to run the waf test suite, execute the following command: 
- ./waf --enable-tests configure 

To see all waf options, execute: 
- ./waf --help

## Validating 

To check everything has gone ok so far, enable the examples and the test options in waf configuration: 
- ./waf --enable-examples --enable-tests configure

Then run :
- ./test.py

## How to run

In order to run .cc files, execute the following command: 
- ./waf --run path/to/file (without the .cc extension)

In order to run .py files, execute the following command:
- ./waf --pyrun path/to/file.py

For more information about NS3, please refer to the official NS3 site https://www.nsnam.org/

For more information about NS3 installation and configuration, please refer to the official NS3 installation site https://www.nsnam.org/wiki/Installation

## Using NetAnim

Using NetAnim is a two-step process.
1) Generate the animation XML trace file during simulation using "ns3::AnimationInterface" in the ns-3 code base
2) Load the XML trace file generated in Step 1 with the offline animator (NetAnim). 

NOTE: A node must have an associated mobility model in-order to be displayed on the animation. This applies for both stationary and mobile nodes.

### Mandatory

1) Ensure that your wscript includes the "netanim" module. Example as in: src/netanim/examples/wscript. 
2) Also include the header [#include "ns3/netanim-module.h"] in your test program
3) Add the statement "AnimationInterface anim ("animation.xml");" before Simulator::Run()
 
### Launch

To launch NetAnim, go to the ns-allinone-3.31/netanim folder and type ./NetAnim

For more information about NetAnim, please refer to the official NetAnim documentation resources at https://www.nsnam.org/wiki/NetAnim_3.105 


## References

https://www.nsnam.org/

https://www.nsnam.org/wiki/Installation

https://www.nsnam.org/wiki/NetAnim_3.105