# Basic C++

## Compilation Model

Preprocessor: It handles header guards. For header guards, you may have nested header guards and you can use #ifndef B\_H and then you can #define B\_H and then you can endif, or the modern way is using `#pragma once`, this will make sure multiple calls of the same header guard works just fine. The Preprocessor expands all header files and a produces a single translation unit.

Compiler: Lexing -> Parsing -> Semantic Analysis -> IR -> Optimization -> Target Code. Compiler knows nothing about what is happening in another translation unit.

Assembler: Turns assembly into a relocatable object file. Contains machine code and symbols.

Linker: It links cross file function calls or machine object files.If there are multiple definitions of a function, the linker won't know which to link properly.

You can declare multiple times (e.g. int Sum(int a, int b);) but you cant define multiple times. Header files are used for declarations only.

Makefile and CFile take care of automating the source code into executables.

static decl lifetime = program
thread: thraed\_local; one copy per thread
automatic: stack allocated; destroyed at scope exit
dynamic: new / malloc. you decide the lifetime

## Memory Layout

Stack: Grows Downward. Function frames, locals, return addresses. It has a fixed max size.
Memory Mapped: Shared Libraries, mmap'd files
Heap: Grows upward via brk/mmap. It is managed by an allocator like malloc
BSS: Zero-initialiazed statics/globals.
Data: Statically initialized globals. Loaded from the binary
Text: Code and Read only Data

Every type has a sizeof(T) and alignof(T) and variables only sit on the memory locations which are integral multiples of their `alignof(T)`. There is also tail padding which is to be followed by taking into consideration the padding of the struct which can be found of alignof(struct) which in practice happens to be the alignment of the largest member variable.

Empty Base Optimization allows having a class with nothing in it to have 0 bytes of memory. This helps in saving memory for clases inheriting with 1 extra byte and also some alignment savings.

Small Buffer / Small String Optimization: If the string is less than 15 characters, then it is allocated on the stack if not it is allocated on the heap. Note: you can use union{} to keep one member variable hot (this is an efficient data structure}

Stack member variables lifetime is just the scope of the variable. For heap, you have to manage the memory and delete/free it. Stack is typically 1-8MiB. Stack overflow can occur for large arrays but Heap is only bounded by the bound virtual address space. Stack is almost always hot with recently pushed frames almost always on L1 cache. For Heap, it depends on access pattern. Stack is trivially thread local and for heap, the allocator must synchronize or use thread local caches. Stack takes 1 cycle to allocate generally. Heap might take 50ns-microseconds to allocate (because of a potentiall syscall).

## Pointers and References

Pointers are addresses. They store the address of something. Ex: `int *ptr = &x` and you can deference it using `*ptr`

When you equate a2 = \*a1, a copy is created.
