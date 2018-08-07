/**
 * @file epub.h
 * @author sb
 * @brief header file for parsing epub files
 */


#ifndef _EPUB_H
#define _EPUB_H

#include <zip.h>
#include <stdlib.h>
#include <libxml2/libxml/parser.h>

/**
 * @brief first file to be read in order to get the filepath of the root file
 */
#define CONTAINER "META-INF/container.xml"

/**
 * @brief root file search term from the first container file
 */
#define ROOT_FILE "full-path=\""

/**
 * @brief structure holding important information about the epub file
 */
struct epub_t {
        struct zip *zipfile;            /* Epub file to be processed */
        char *cbuf;                     /* container file buffer */
        char *rfpath;                   /* root filepath */
};

/**
 * @brief function to initialise the epub module
 * @params [epub_str] pointer to the structure created
 * @params [filepath] path of the epub file to be opened
 */
int epub_init(struct epub_t *spub_str, const char* filepath);

/**
 * @brief get the fullpath of the root file
 */
char *get_root_file(void);

/**
 * @brief function to clean up the epub module
 */
void epub_destroy(struct epub_t *epub_str);

#endif
