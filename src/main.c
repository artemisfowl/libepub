/**
 * @file main.c
 * @brief test code for the epub library main code
 */

#include <stdio.h>
#include "../inc/epub.h"

int main(void)
{
        printf("Working!!!\n");

        /* initialise the epub library */
        if (epub_init("../test/Wizard - Marc Seifer.epub"))
                printf("Epub file has been opened properly\n");

        /* now read the container file */
        printf("Value obtained : %s\n", get_root_file());
        /* let's rewrite the code for the get_root_file function with that of
         * libxml code */

        /* destroy the epub library instance */
        epub_destroy();
        return 0;
}
