plugin sandbox
==============

his little project is to test plugin loaders written in C++.

task
---
- define the plugin interface as a (pure virtual) C++-class in the host
  application
- implement the plugin interface by creating a derived class in a dynamic
  library
- make this work, even if host and plugin have been compiled with different C++
  compilers (with different ABIs).
- make this work in a "backward compatible" way (see below)

naive approach
---
it's possible to implement plugins as child-classes of a MAIN class, where the
MAIN class is declared/defined in the host application and the child class is
declared/defined in the plugin library.
a template-based plugin-factory (that maps IDs to allocators for the child-class
and does the proper casting to the MAIN class) handles the host part.

however, this only works if the two compilers are ABI compatible (this is: they
are the same).

this is what we call the "legacy" implementation (and is used e.g. in Gem)

the problem
---
the problem comes in, when we want to use different compilers for both host and
plugins.
why would we ever want this?
- on w32 some libraries offer C++ bindings *only*, and via VisualC++ libraries.
  if we want to (auto)compile our host with (e.g.) MinGW (g++), we cannot use
  these libraries.
- some plugins are exceptionally hard to build (with all those undocumented
  dependencies and stuff). it would be great if we would could use older
  binaries, even if we have switched the compiler.

a better approach
---
since the C-ABI is standardized on each platform, we can use it to communicate
between binaries produced by different compilers.
so we want to do:
- wrap a pure-virtual class into a struct containing pointers to C-functions:
e.g. `void plugin::close(void)` maps to a C-function of type 
`typedef void (*pluginC_close_t) (pluginC_t);` which is part of a callback
struct: `struct pluginCallbacks_ { pluginC_close_t close; }`.
we pass this struct (along with the plugin-ID (as string) via a C-function to
the host, which then registers at the plugin-factory.

this requires a change in the constructor: the legacy implementation had a
`void(*ctor)(void)` constructor, whereas now we need `void(*ctor)(id)` (with the
id being a string): this is so, that we can pass a single constructor for
multiple classes to the plugin-factory - namely the wrapper constructor - and
let the ctor decide, which class to construct.

benefits
---
this also allows to write plugins in pure C.

TODO
---
complex datatypes (think std::map) need to be wrapped through C

tests
---
hosts
----
pluginhost
-----
create plugins the new way
 - using the pluginfactory directly (inter-dll inheritance)
 - using the C-wrapper
should be able to instantiate legacy plugins
legacyhost
-----
create plugins the old way (no id to ctor).
need not be able to instantiate new-style plugins

plugins
----

plugins/pluginC_0
-----
C-plugin, that only tests whether we can call a method in the host

plugins/pluginC_1
-----
a plugin written in C, that does some work
`pluginhost` should be able to call the "process" function

plugins/pluginCC_1
-----
a plugin written in C++, that does inter-dll inheritance from the host
`pluginhost` should be able to call the "process" function

plugins/pluginCC_2
-----
a plugin written in C++, that registers via the C-wrapper
`pluginhost` should be able to call the "process" function
`pluginhost` with different ABI should be able to call the "process" function

legacy/pluginC
-----
C-plugin, that only tests whether we can call a method in the host
(no process for any plugin host)

legacy/pluginCC
-----
a plugin written in C++, that does inter-dll inheritance from the host
`pluginhost` should be able to call the "process" function
`legacyhost` should be able to call the "process" function


