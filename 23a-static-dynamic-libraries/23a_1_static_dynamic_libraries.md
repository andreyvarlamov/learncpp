# A.1 - Static and dynamic libraries

A **static library** (aka **archive**) consists of routines that are compiled and linked
directly into your program. All the functionality of the static library that your program
uses becomes part of your executable. On windows: .lib extension. On Linux - .a extension
(archive).

A **dynamic library** (aka **shared library**) consists of routine that are loaded into
your application at runtime. Does not become part of your executable. Windows: .dll -
dynamic link library; linux - .so (shared object).

Programs using dynamic libraries must explicitly load and interface with the dynamic
library. To make dynamic libraries easier to use, an import library can be used. On
windows, typically done via a small static library (.lib) of the same name as the dynamic
library (.dll). The static library is linked into the program at compile time, and then
the functionality of the dynamic library can effectively be used as if it were a static
library. On Linux, the shared object (.so) file doubles as both a dynamic library and an
import library. Most linkers can build an import library for a dynamic library when the
dynamic library is created.
