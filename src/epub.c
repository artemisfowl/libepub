/**
 * @file epub.c
 * @brief implementation of the epub library
 */

#include "../inc/epub.h"
#include <string.h>

/* internal functions - not to be exposed to the user */
static long int _get_fsize(struct zip *z, const char *fname)
{
        struct zip_stat zs;
        for (int i = 0; i < zip_get_num_entries(z, ZIP_FL_UNCHANGED); i++) {
                if (zip_stat_index(z, i, 0, &zs) == 0)
                        if (strncmp(zs.name, fname,
                                                strlen(fname)) == 0)
                                return zs.size;
        }
        return 0;
}

static char *_parse_data(char *sstr, char *container_dat, char delim,
                char *search_term)
{
        /* if container data is not present, return NULL immediately */
        if (!container_dat)
                return NULL;

        /* increment till the part where the index is pointing to the last of
         * the search pattern - ROOT_FILE */
        char *index = strstr(container_dat, search_term);
        for (unsigned long c = 0; c < strlen(search_term); c++, index++);

        /* ascertain the number of bytes to be read */
        unsigned long i = strlen(search_term);
        for (; index[i] != delim; i++);
        sstr = calloc(i + 1, sizeof(char));

        /* now process the substring */
        strncpy(sstr, index, i);

        /* return the value */
        return sstr;
}

static char *_read_zfile(struct zip *z, const char *fname)
{
        /* this function will read the contents of the fname and pass the data
         * to the calling function */
        return NULL;
}

/*
 * @brief get the desired node from the xml data passed
 */
xmlNodePtr get_node(struct epub_t *epub_str, const char *node_name)
{
        xmlNodePtr cur = NULL;
        xmlDocPtr doc = NULL;

        /* first read the XML data from the zip file */
        long int fsize = _get_fsize(epub_str->zipfile, epub_str->rfpath);
        printf("Size of root file : %ld\n", fsize);

        /* free the document before returning */
        xmlFreeDoc(doc);
        return cur;
}

/*
 * @brief init function for the epub module
 */
int epub_init(struct epub_t *epub_str, const char* filepath)
{
        /* open the zip file in RD_ONLY mode */
        int err;
        epub_str->zipfile = zip_open(filepath, ZIP_RDONLY, &err);
        epub_str->cbuf = NULL;
        epub_str->rfpath = NULL;
        return epub_str->zipfile ? 1 : 0;
}

/**
 * @brief get the fullpath of the root file
 */
char *get_root_file(struct epub_t *epub_str)
{
        struct zip_file *zfile = zip_fopen(epub_str->zipfile, CONTAINER,
                        ZIP_FL_UNCHANGED);

        /* get the size of the container file */
        long container_fsize = _get_fsize(epub_str->zipfile, CONTAINER);

        /* create the buffer to be returned */
        epub_str->cbuf = calloc(container_fsize + 1, sizeof(char));

        /* read the contents of the container file */
        if (zip_fread(zfile, epub_str->cbuf, container_fsize) == EOF)
                fprintf(stderr, "Error while reading the file : %s\n",
                                CONTAINER);

        /* now get the specified substring */
        epub_str->rfpath = _parse_data(epub_str->rfpath, epub_str->cbuf,
                        '"', ROOT_FILE);

        if (zfile)
                zip_fclose(zfile);

        return epub_str->rfpath;
}

/*
 * @brief destroy the resources used for parsing the epub file
 */
void epub_destroy(struct epub_t *epub_str)
{
        if (epub_str->zipfile)
                zip_close(epub_str->zipfile);
        free(epub_str->rfpath);
        free(epub_str->cbuf);
}
