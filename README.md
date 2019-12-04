# fqreader 0.1.1-dev0

Read a file or stream of sequences in FASTQ format:
```c
    char       *h1, *h2, *s, *t;
    struct fqreader *r = fqreader_new(NULL);
     . . .
    while (fqreader_next(r, &h1, &h2, &s, &t)) {
       printf("Header 1 is    %s\n", h1);
       printf("Sequence is    %s\n", s);
       printf("Header 2 is    %s\n", h2);
       printf("Qualities are: %s\n", t);
    }
     . . . 
    fqreader_free(r);
```

