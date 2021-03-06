/**
 *  @file fqreader.c
 *  @version 0.4.0
 *  @date Mon Feb 17, 2020 05:47:56 PM CST
 *  @copyright 2019-2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

/* Needed because fileno() seems to be POSIX C but not ANSI C */
#define _POSIX_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "varstr.h"
#ifdef   HAVE_ZLIB
#include "zlib.h"
#else
typedef FILE *gzFile;
#define  gzdopen(a, b) fdopen((a), (b))
#define  gzopen(a, b)  fopen((a), (b))
#define  gzclose(a)    fclose((a))
#define  gzgetc(a)     getc((a))
#endif
#include "fqreader.h"

#ifdef  IS_NULL
#undef  IS_NULL
#endif
#define IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  FREE
#undef  FREE
#endif
#define FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

struct fqreader {
   struct varstr *h1;
   struct varstr *h2;
   struct varstr *s;
   struct varstr *t;
   gzFile    in;
};

struct fqreader *
fqreader_new(char *fname)
{
   struct fqreader *tp;

   tp = (struct fqreader *) malloc(sizeof(struct fqreader));
   if (IS_NULL(tp))
      return NULL;

   if (IS_NULL(fname))
      tp->in = gzdopen(fileno(stdin), "r");

   else
      tp->in = gzopen(fname, "r");

   if (IS_NULL(tp->in))
      return NULL;

#ifdef  HAVE_ZLIB
   gzbuffer(tp->in, 1024 * 32);                  /* requires at least zlib-1.2.4 */
#endif

   tp->h1 = varstr_new();
   varstr_buffersize(tp->h1, 100, 50);
   tp->h2 = varstr_new();
   varstr_buffersize(tp->h2, 100, 50);
   tp->s = varstr_new();
   varstr_buffersize(tp->s, 100, 50);
   tp->t = varstr_new();
   varstr_buffersize(tp->t, 100, 50);

   return tp;
}

void
fqreader_free(struct fqreader **pp)
{
   gzclose((*pp)->in);
   varstr_free(&(*pp)->h1);
   varstr_free(&(*pp)->h2);
   varstr_free(&(*pp)->s);
   varstr_free(&(*pp)->t);

   FREE(*pp);
   *pp = NULL;
}

const char *
fqreader_version(void)
{
   return "0.4.0";
}

int
fqreader_next(struct fqreader *p, char **h1, char **h2, char **s, char **t)
{
   unsigned  rc = 1;
   int       c;
   enum states { s_need_h1, s_in_h1, s_in_s, s_in_h2, s_in_t };
   enum states state = s_need_h1;

   varstr_empty(p->h1);
   varstr_empty(p->h2);
   varstr_empty(p->s);
   varstr_empty(p->t);

   while ((c = gzgetc(p->in)) > 0) {

      switch (state) {

         case s_need_h1:
            if (isspace(c))
               continue;
            else if (c == '@')
               state = s_in_h1;
            else
               exit(1);
            break;

         case s_in_h1:
            if (c == '\n')
               state = s_in_s;
            else
               varstr_catc(p->h1, c);
            break;

         case s_in_s:
            if (isspace(c))
               continue;
            else if (c == '+')
               state = s_in_h2;
            else
               varstr_catc(p->s, c);
            break;

         case s_in_h2:
            if (c == '\n')
               state = s_in_t;
            else
               varstr_catc(p->h2, c);
            break;

         case s_in_t:
            if (isspace(c))
               continue;
            else if (strlen(varstr_str(p->s)) > 1 + strlen(varstr_str(p->t)))
               varstr_catc(p->t, c);
            else {
               varstr_catc(p->t, c);
               goto DONE;
            }
            break;
      }
   }

   rc = 0;

 DONE:

   *h1 = varstr_str(p->h1);
   *h2 = varstr_str(p->h2);
   *s = varstr_str(p->s);
   *t = varstr_str(p->t);

   return rc;
}

#undef IS_NULL
#undef FREE
