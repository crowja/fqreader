#include <stdlib.h>
#include <stdio.h>
#include "fqreader.h"

int
main(int argc, char *argv[])
{
   char       *h1, *h2, *s, *t;
   struct fqreader *r = fqreader_new(NULL);

   while (fqreader_next(r, &h1, &h2, &s, &t)) {
      printf("Header 1 is    %s\n", h1);
      printf("Sequence is    %s\n", s);
      printf("Header 2 is    %s\n", h2);
      printf("Qualities are: %s\n", t);
   }

   fqreader_free(r);
   return 0;
}
