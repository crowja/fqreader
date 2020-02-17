/**
 *  @file fqreader.h
 *  @version 0.4.0-dev0
 *  @date Mon Feb 17, 2020 05:47:56 PM CST
 *  @copyright 2019-2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#ifndef FQREADER_H
#define FQREADER_H

struct fqreader;

/**
 *  @brief Create and return a new fqreader object.
 *  @details FIXME longer description here ...
 */
struct fqreader *fqreader_new(char *fname);

/**
 *  @brief Clean up and free a fqreader structure.
 *  @details FIXME longer description here ...
 */
void      fqreader_free(struct fqreader **pp);

/**
 *  @brief Initialize a fqreader object.
 *  @details FIXME longer description here ...
 *  @param p Pointer to a fqreader object
 *  @param x FIXME
 */
int       fqreader_init(struct fqreader *p, void *x);

/**
 *  @brief Return the version of this package.
 *  @details FIXME longer description here ...
 */
const char *fqreader_version(void);

int       fqreader_next(struct fqreader *p, char **h1, char **h2, char **s, char **t);

#endif
