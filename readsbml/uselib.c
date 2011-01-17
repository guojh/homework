/*
 *      from an example of libxml2
 */
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>

/*
 *To compile this file using gcc you can type
 *gcc `xml2-config --cflags --libs` -o xmlexample libxml2-example.c
 */

char *list[]={
  "compartment",
  "species",
  "parameter",
  "reaction",
  NULL
};

int check_name( const char *name, char **list ) {
  while( *list && ( strcmp( name, *list ) != 0 ) ) list++;
  return (*list != NULL);
}

void walk_node(xmlNode * a_node, char **namelist)
{
    xmlNode *cur_node = NULL;
    xmlChar *idval = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
      if (cur_node->type == XML_ELEMENT_NODE) {
	if ( check_name( cur_node->name, namelist ) ) {
	  idval = xmlGetProp( cur_node, "id" );
	  if ( idval )
	    printf("%s: \t\t%s\n", cur_node->name, idval);
	}
      }
      walk_node( cur_node->children, namelist );
    }
}

int main(int argc, char **argv)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    if (argc != 2)
        return(1);

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    doc = xmlReadFile(argv[1], NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", argv[1]);
    }

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    walk_node(root_element, list);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    return 0;
}
