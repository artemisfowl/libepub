/**
 * @file main.c
 * @brief test code for the epub library main code
 */

#include <stdio.h>
#include "../inc/epub.h"
#include <assert.h>

int main(void)
{
        printf("libepub-dev testing\n");

        /* first create a copy of the epub library structure */
        struct epub_t epub;

        /* initialise the epub library */
        assert(epub_init(&epub, "../test/1.epub"));

        /* now read the container file and get the root file location/name */
        assert(get_root_file(&epub));

        /* check the output of the getnode function */
        (void)get_node(&epub, "rootfile");

        /* destroy the epub library instance */
        epub_destroy(&epub);
        return 0;
}
