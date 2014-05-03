## Introduction

This project provides a library for the SyscMsg namespace, which contains the Msg class.
The Msg class provides helper methods for log message generation.

There are three constructors for the Msg class.  The Msg constructor
that takes a single character pointer uses sc\_core::sc\_report\_handler::set\_handler()
to extend sc\_core::sc\_report\_handler\_proc with simulation time stamps.

### Use Cases

* Generating messages in C++
* Generating messages in SystemC test benches with simulation time indication

### Unsupported Use Cases

* TBD

### Library

The libsyscmsg library is created by executing "make lib".
Both static and dynamic libraries are built.

### SystemC

The validation test uses the [Accellera](http://www.accellera.org/home/)
implementation of the SystemC classes to provide
a simulation kernel.

The path to the SystemC installation is set in the makefiles using the
variables IPATH and LPATH.

## Validated Environments

Generating messages has been validated in the following environments

| Linux                | libc  | gcc   | SystemC | make | bash   |
|----------------------|-------|-------|---------|------|--------|
| Debian 3.2.0-4-amd64 | 2.13  | 4.7.2 | 2.3.0   | 3.81 | 4.2.37 |

## Installation

1. Make sure you have installed the components shown in the
   "Validated Environments" section
    * Install SystemC from source, since it is unlikely to be
      packaged
1. Modify paths to the SystemC installation, IPATH and LPATH,
   in Makefile
1. execute "make" for hints about available targets

## Issues

* Bug tracker TBD

## Comms

* Mailing list TBD

## License

### License for Code

The code in this project is licensed under the GPLv3

### License for This Project Summary

This work is licensed under the Creative Commons Attribution-ShareAlike 3.0
Unported License. To view a copy of this license, visit
http://creativecommons.org/licenses/by-sa/3.0/. 
