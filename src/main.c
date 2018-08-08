/**
 * @file main.c
 * @brief test code for the epub library main code
 */

#include <stdio.h>
#include "../inc/epub.h"

int main(void)
{
        printf("Working!!!\n");

        /* first create a copy of the epub library structure */
        struct epub_t epub;

        /* initialise the epub library */
        if (epub_init(&epub, "../test/1.epub"))
                printf("Epub file has been opened properly\n");

        /* now read the container file */
        printf("Value obtained : %s\n", get_root_file(&epub));

        /* destroy the epub library instance */
        epub_destroy(&epub);
        return 0;
}
