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
        printf("Value obtained : %s\n", epub.rfpath);

        /* check the output of the getnode function */
        /* before calling the get node, get the contents of the xml file to be
         * read */
        char *content = read_zfile(epub.zipfile, epub.rfpath);
        //printf("Content : \n%s\n", content);

        /* call the get node function */
        prepare_doc(&epub, content);
        xmlNodePtr n = get_node(&epub, content, "manifest");
        if (n)
                printf("Name : %s\n", n->name);
        free(content);
        //assert(get_node(&epub, "rootfile"));

        /* destroy the epub library instance */
        epub_destroy(&epub);
        return 0;
}
