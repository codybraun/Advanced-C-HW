#include "list.h"       /* assume list implementation */

typedef struct CHTbl_ {
  int                        buckets; /* M in class terminology */
  int                        (*h)(const void *key); /* this is just g, f is built in */
  int                        (*match)(const void *key1, const void *key2);
  void                       (*destroy)(void *data);
  int                        size; /* n in class terminology */
  List                       *table; /* array of List type -- one per bucket */
} CHTbl;

int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key), int        
	       (*match)(const void *key1, const void *key2), void (*destroy)(void *data));
void chtbl_destroy(CHTbl *htbl);
int chtbl_insert(CHTbl *htbl, const void *data);
int chtbl_remove(CHTbl *htbl, void **data);
int chtbl_lookup(const CHTbl *htbl, void **data);
#define chtbl_size(htbl) ((htbl)->size)
