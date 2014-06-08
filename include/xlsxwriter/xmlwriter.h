/*
 * libxlsxwriter
 * 
 * Copyright 2014, John McNamara, jmcnamara@cpan.org. See LICENSE.txt.
 *
 * xmlwriter - A libxlsxwriter library for creating Excel XLSX
 *             XML files.
 *
 * The xmlwriter library is used to create the XML sub-components files
 * in the Excel XLSX file format.
 *
 * This library is used in preference to a more generic XML library to allow
 * for customisation and optimisation for the XLSX file format.
 *
 * The xmlwriter functions are only used internally and do not need to be
 * called directly by the end user.
 *
 */
#ifndef __XMLWRITER_H__
#define __XMLWRITER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "xlsxwriter/third_party/queue.h"

/* Defines. */
#define MAX_ATTRIBUTE_LENGTH 140
#define ATTR_32 32
#define MAX_CELL_NAME_LENGTH 13

 /* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* Attribute used in XML elements. */
struct xml_attribute {
    char key[MAX_ATTRIBUTE_LENGTH];
    char value[MAX_ATTRIBUTE_LENGTH];

    /* Make the struct a queue.h list element. */
    STAILQ_ENTRY (xml_attribute) list_entries;
};

/* Use queue.h macros to define the xml_attribute_list type. */
STAILQ_HEAD(xml_attribute_list, xml_attribute);

/* Create a new attribute struct to add to a xml_attribute_list. */
struct xml_attribute *_new_attribute_str(const char *key, const char *value);
struct xml_attribute *_new_attribute_int(const char *key, uint32_t value);
struct xml_attribute *_new_attribute_dbl(const char *key, double value);

/* Macro to initialise the xml_attribute_list pointers. */
#define _INIT_ATTRIBUTES()                                    \
    STAILQ_INIT(&attributes)

/* Macro to add attribute string elements to xml_attribute_list. */
#define _PUSH_ATTRIBUTES_STR(key, value)                      \
    do {                                                      \
    attribute = _new_attribute_str((key), (value));           \
    STAILQ_INSERT_TAIL(&attributes, attribute, list_entries); \
    } while (0)

/* Macro to add attribute int values to xml_attribute_list. */
#define _PUSH_ATTRIBUTES_INT(key, value)                      \
    do {                                                      \
    attribute = _new_attribute_int((key), (value));           \
    STAILQ_INSERT_TAIL(&attributes, attribute, list_entries); \
    } while (0)

/* Macro to add attribute double values to xml_attribute_list. */
#define _PUSH_ATTRIBUTES_FLT(key, value)                      \
    do {                                                      \
    attribute = _new_attribute_flt((key), (value));           \
    STAILQ_INSERT_TAIL(&attributes, attribute, list_entries); \
    } while (0)

/* Macro to free xml_attribute_list and attribute. */
#define _FREE_ATTRIBUTES()                                    \
    while (!STAILQ_EMPTY(&attributes)) {                      \
        attribute = STAILQ_FIRST(&attributes);                \
        STAILQ_REMOVE_HEAD(&attributes, list_entries);        \
        free(attribute);                                      \
    }

/**
 * Create the XML declaration in an XML file.
 *
 * @param xmlfile A FILE pointer to the output XML file.
 */
void _xml_declaration(FILE * xmlfile);

/**
 * Write an XML start tag with optional attributes.
 *
 * @param xmlfile    A FILE pointer to the output XML file.
 * @param tag        The XML tag to write.
 * @param attributes An optional list of attributes to add to the tag.
 */
void _xml_start_tag(FILE * xmlfile,
                    const char *tag, struct xml_attribute_list *attributes);

/**
 * Write an XML start tag with optional un-encoded attributes.
 * This is a minor optimisation for attributes that don't need encoding.
 *
 * @param xmlfile    A FILE pointer to the output XML file.
 * @param tag        The XML tag to write.
 * @param attributes An optional list of attributes to add to the tag.
 */
void _xml_start_tag_unencoded(FILE * xmlfile,
                              const char *tag,
                              struct xml_attribute_list *attributes);

/**
 * Write an XML end tag.
 *
 * @param xmlfile    A FILE pointer to the output XML file.
 * @param tag        The XML tag to write.
 */
void _xml_end_tag(FILE * xmlfile, const char *tag);

/**
 * Write an XML empty tag with optional attributes.
 *
 * @param xmlfile    A FILE pointer to the output XML file.
 * @param tag        The XML tag to write.
 * @param attributes An optional list of attributes to add to the tag.
 */
void _xml_empty_tag(FILE * xmlfile,
                    const char *tag, struct xml_attribute_list *attributes);

/**
 * Write an XML empty tag with optional un-encoded attributes.
 * This is a minor optimisation for attributes that don't need encoding.
 *
 * @param xmlfile    A FILE pointer to the output XML file.
 * @param tag        The XML tag to write.
 * @param attributes An optional list of attributes to add to the tag.
 */
void _xml_empty_tag_unencoded(FILE * xmlfile,
                              const char *tag,
                              struct xml_attribute_list *attributes);

/**
 * Write an XML element containing data and optional attributes.
 *
 * @param xmlfile    A FILE pointer to the output XML file.
 * @param tag        The XML tag to write.
 * @param data       The data section of the XML element.
 * @param attributes An optional list of attributes to add to the tag.
 */
void _xml_data_element(FILE * xmlfile,
                       const char *tag,
                       const char *data,
                       struct xml_attribute_list *attributes);

/* *INDENT-OFF* */
#ifdef __cplusplus
}
#endif
/* *INDENT-ON* */

#endif /* __XMLWRITER_H__ */