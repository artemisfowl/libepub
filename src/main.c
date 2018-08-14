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
        xmlNodePtr n = get_root_node(&epub);

        /* get the "manifest" node */
        n = get_node(n, "manifest");
        n = get_node(n, "item");

        /* get the node which corresponds to the required string */
        if (n)
                printf("Name : %s\n", n->name);

        /* check the attribute received */
        while (n) {
                unsigned char *id = get_node_prop(n, "id");
                if (id)
                        printf("Value obtained : %s\n", id);
                free(id);
                unsigned char *href = get_node_prop(n, "href");
                if (href)
                        printf("Value obtained : %s\n", href);
                free(href);
                n = n->next;
        }

        /* free the resources */
        free(content);
        xmlFreeNode(n);

        /* destroy the epub library instance */
        epub_destroy(&epub);
        return 0;
}
