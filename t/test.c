#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include "fqreader.h"
#include "t/tinytest.h"
#include "t/tinyhelp.h"

static void
test_constr(void)
{
   struct fqreader *z;

   fprintf_test_info(stdout, "test_constr", "fqreader_new, fqreader_free");
   z = fqreader_new(NULL);
   ASSERT("Constructor test", z);
   fqreader_free(&z);
   ASSERT_EQUALS(NULL, z);
}

#if 0                                            /* 12 yy */
static void
test_stub(void)
{
   struct fqreader *z;

   fprintf_test_info(stdout, "test_stub", NULL);

   z = fqreader_new(NULL);
   ASSERT("Constructor test, pt 1", z);
   fqreader_free(&z);
   ASSERT_EQUALS(NULL, z);
}
#endif

int
main(void)
{
   printf("%s\n", fqreader_version());

   RUN(test_constr);

   return TEST_REPORT();
}
