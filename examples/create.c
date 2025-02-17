#include "dynarr.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void default_create(void);
void explicit_opts_create(void);
void extended_header(void);
void cloning(void);

int main(void)
{
    default_create();
    explicit_opts_create();
    extended_header();
    cloning();

    return 0;
}

void default_create(void)
{
    dynarr_t *dynarr = dynarr_create(.element_size = sizeof(int));

    if (!dynarr)
    {
        perror("dynarr_create");
        abort();
    }

    // ...

    dynarr_destroy(dynarr);
}

void explicit_opts_create(void)
{
    dynarr_t *dynarr = dynarr_create
        (
            .element_size = sizeof(float),
            .initial_cap = 100,
            .grow_factor = 1.5f,
            .grow_threshold = 0.8,
            .shrink_threshold = 0.2
        );

    assert(dynarr && "Buy more RAM!");

    // ...

    dynarr_destroy(dynarr);
}

void extended_header(void)
{
    typedef struct
    {
        size_t meta;
        // ...
        // ...
        // ...
    }
    ext_t;

    dynarr_t *dynarr = dynarr_create
        (
            .ext_header_size = sizeof(ext_t),
            .element_size = sizeof(long)
        );

    // ...

    ext_t *header = dynarr_get_ext_header(dynarr);
    *header = (ext_t) {0};

    // ...

    dynarr_destroy(dynarr);
}

void cloning(void)
{
    dynarr_opts_t opts = {.element_size = sizeof(int)};
    dynarr_t *dynarr = dynarr_create_(&opts);

    dynarr_t *clone = dynarr_clone(dynarr);

    dynarr_destroy(dynarr);
    dynarr_destroy(clone);
}
