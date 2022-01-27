## -Wno-warn-absolute-paths - remove warnings about absolute paths
## -O2 		            - second level of optimizations
## --preload-file	    - preloading files in the following directory
## -v                       - verbose mode for debugging

Emcc strips out most of the debug information
from optimized builds by default. Optimisation
levels -01 and above remove LLVM debug information,
and also disable runtime ASSERTIONS checks.
From optimization level -02 the code is minified
by the Closure Compiler and becomes virtually unreadable.

The emcc -g flag can be used to preserve debug
information in the compiled output. By default,
this option preserves white-space, function
names and variable names.

The flag can also be specified with one
of five levels: -g0, -g1, -g2, -g3, and -g4.
Each level builds on the last to provide
progressively more debug information in
the compiled output. The -g3 flag provides
the same level of debug information as the -g flag.

The -g4 option provides the most debug
information — it generates source maps that allow y
ou to view and debug the C/C++ source code
in your browser’s debugger on Firefox, Chrome or Safari!

The most important settings are:

ASSERTIONS=1 is used to enable runtime checks for
common memory allocation errors (e.g. writing more
memory than was allocated). It also defines how
Emscripten should handle errors in program flow.
The value can be set to ASSERTIONS=2 in order to
run additional tests.

ASSERTIONS=1 is enabled by default. Assertions
are turned off for optimized code (-01 and above).

SAFE_HEAP=1 adds additional memory access checks,
and will give clear errors for problems like
dereferencing 0 and memory alignment issues.
Use SAFE_HEAP=2 in order to check only specific
lines listed in SAFE_HEAP_LINES, and use
SAFE_HEAP=3 to check all the lines except
those specified. This last option is the most common operation.

You can also set SAFE_HEAP_LOG to log SAFE_HEAP operations.

Example:

./emcc -01 -s ASSERTIONS=1 tests/hello_world
