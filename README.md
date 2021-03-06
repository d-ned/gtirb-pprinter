GTIRB Pretty Printer
====================

A pretty printer from the [GTIRB](https://github.com/grammatech/gtirb)
intermediate representation for binary analysis and reverse
engineering to gas-syntax assembly code.


## Building

The pretty-printer uses C++17, and requires a compiler which supports
that standard such as gcc 7, clang 6, or MSVC 2017.

Boost (1.67 or later) and [GTIRB](https://github.com/grammatech/gtirb)
are required.

Use the following options to configure cmake:
- You can tell CMake which compiler to use with
  `-DCMAKE_CXX_COMPILER=<compiler>`.
- Normally CMake will find GTIRB automatically, but if it does not you
  can pass `-Dgtirb_DIR=<path-to-gtirb-build>`.

Once the dependencies are installed, you can configure and build as follows:

```sh
cmake ./ -Bbuild
cd build
make
```


## Usage

Pretty print the GTIRB for a simple hello world executable to an
assembly file named `hello.S`, assemble this file with the GNU
assembler to an object file named `hello.o`, and link this object file
into an executable.

```sh
gtirb-pp hello.gtirb -o hello.S
as hello.S -o hello.o
ld hello.o -o hello
./hello
```


## AuxData Used by the Pretty Printer

Generating assembly depends on a number of additional pieces of information
beyond the symbols and instruction/data bytes in the IR. The pretty printer
expects this information to be available in a number of
[AuxData](https://github.com/GrammaTech/gtirb/blob/master/README.md#auxiliary-data)
objects stored with the IR. We document the expected keys along with the
associated types and contents in this table.

| Key              | Type                                           | Purpose                                                                                                                              |
|------------------|------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------|
| comments         | `std::map<gtirb::Addr, std::string>`           | Per-instruction comments.                                                                                                            |
| functionEntries    | `std::map<gtirb::UUID, std::set<gtirb::UUID>>` | UUIDs of the blocks that are entry points of functions.                                                                                              |
| symbolForwarding | `std::map<gtirb::UUID, gtirb::UUID>`           | Map from symbols to other symbols. This table is used to forward symbols due to relocations or due to the use of plt and got tables. |
| types            | `std::map<gtirb::UUID,std::string>`            | Map from (typed) data objects to the type of the data,  expressed as a std::string containing a C++ type specifier.                  |
