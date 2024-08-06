#include "dynarr.h"
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 24
#define _STR(x) #x
#define STR(x) _STR(x)

typedef struct name
{
    char data[MAX_NAME_LEN + 1];
}
name_t;

static int print_name(const void *const element, void *const param);

int main(void)
{
    dynarr_t        *dynarr;
    dynarr_status_t status     = DYNARR_SUCCESS;
    name_t          input_name = {0};
    int             entered    = 0;

    dynarr = dynarr_create(.element_size = sizeof(name_t));
    if (!dynarr)
    {
        return DYNARR_ALLOC_ERROR;
    }

    do
    {
        memset(input_name.data, 0, MAX_NAME_LEN + 1);
        entered = scanf("%" STR(MAX_NAME_LEN) "s\n", input_name.data);

        if ('\0' != input_name.data[0])
        {
            status = dynarr_binary_insert(&dynarr,
                    input_name.data,
                    cmp_lex_asc,
                    TMP_REF(int, MAX_NAME_LEN),
                    NULL);
        }

        if (DYNARR_SUCCESS != status)
        {
            dynarr_destroy(dynarr);
            return status;
        }
    }
    while (entered != EOF);

    dynarr_foreach(dynarr, print_name, NULL);
    dynarr_destroy(dynarr);
    return 0; /* normal exit */
}

static int print_name(const void *const element, void *const param)
{
    (void)param;
    printf("%s\n", ((name_t*)element)->data);
    return 0;
}

