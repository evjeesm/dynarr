# Dynarr - generic dynamic array
Is an extension over [vector](https://github.com/evjeesm/vector).

![check](https://github.com/evjeesm/dynarr/actions/workflows/makefile.yml/badge.svg)

Keeps containing data sequential, tracks amount of stored elements
and grows/shrinks on demand.
Resize functionality is parametrized for flexability.

Has variety of common array operation, like append, insert, search, etc ...
Vector API can seamlessly operate on `dynarr_t *`.

Supports further extension.

Compiles to *static* archive and/or *shared* object.

## Supported platforms
- GNU Linux
- crossplatform compatability is not planned yet.

## Dependencies
**Build Tools**:
  - gcc
  - make
  - autotools:
    - automake >= 1.11.2
    - autoconf
    - autoconf-archive - install separately (for valgrind support)
    - libtool
  - check - testing framework
  - valgrind (optionally) - for memory leak checks

**Std Libraries**:
  - stdlib.h
  - string.h
  - math.h

**Subprojects**:
  - [vector](https://github.com/evjeesm/vector)

## Building
- install **Build Tools** dependencies:
  on **debian**:
    ```sh
    $ sudo apt-get install gcc make automake autoconf autoconf-archive libtool check valgrind
    ```
- clone the repository:
  ```sh
  $ git clone https://githib.com/EvgeniSemenov/vector.git dynarr; cd dynarr;
  $ git submodule update --init --recursive;
  ```
- run `./autogen.sh` if you do any changes to `configuration.ac` file.
- run `./configure CFLAGS="<YOUR COMPILATION FLAGS>"` for instance `-Wall -Wextra -O3 -DNDEBUG`
- run `make check`, whole thing will be compiled and tested with *check*

## Usage
link against (`libdynarr_static.a` or `libdynarr.so`) and -lm
If you use vector's API exclusively, then link also with vector library.

### Minimal Example
```c
#include "dynarr.h"
int main(void)
{
    dynarr_t *dynarr = dynarr_create(.element_size = sizeof(int));
    int a = 69;
    dynarr_append(&dynarr, &a);
    dynarr_append(&dynarr, TMP_REF(int, 42));

    dynarr_last(dynarr, &a); // a = 42
    dynarr_destroy(dynarr);
}
```
