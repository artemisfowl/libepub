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
        xmlDocPtr doc;                  /* xml document */
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
char *get_root_file(struct epub_t *epub_str);

/*
 * @brief function to read a file from the zip file provided and get the
 * contents
 * @params [z] zip file to be read
 * @params [fname] name of the file to be read - file should be present in the
 * zip file
 */
char *read_zfile(struct zip *z, const char *fname);

/**
 * @brief function to get the document for parsing - XML data
 * @params [epub_str] epub_t structure holding the important details
 * @params [content] content to be passed for getting the XML document
 */
void prepare_doc(struct epub_t *epub_str, char *content);

/**
 * @brief function to parse required xml file and load the attributes and
 * filepath pair
 */
xmlNodePtr get_root_node(struct epub_t *epub_str);

/**
 * @brief function to get the desired node
 */
xmlNodePtr get_node(xmlNodePtr cur, const char *node_name);

/**
 * @brief function to clean up the epub module
 */
void epub_destroy(struct epub_t *epub_str);

#endif
