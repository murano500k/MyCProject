/*

Rewrite fopen and _fillbuf with fields instead of explicit bit operations.
Compare code size and execution speed.

*/

#include <sys/file.h> // contains open and O_RDONLY etc
#include <unistd.h>   // contains read, write and close

#include <stdlib.h> // for malloc
#include <string.h> // for strlen

//#define NULL      0 // already defined
#define EOF       (-1)
#define BUFSIZ    1024
#define OPEN_MAX  20    // max files open at once

typedef struct _iobuf {
    ssize_t  cnt;	  // characters left
    char	 *ptr;	  // next character position
    char	 *base;	  // location of buffer

    int		 flag_read;	// flags for mode of file access:
    int		 flag_write;
    int		 flag_unbuf;
    int		 flag_eof;
    int		 flag_err;

    int		 fd;	  // file descriptor
} FILE;


extern FILE _iob[OPEN_MAX];
FILE _iob[OPEN_MAX] = {
    { 0, (char *) 0, (char *) 0, 1, 0, 0, 0, 0, 0 },
    { 0, (char *) 0, (char *) 0, 0, 1, 0, 0, 0, 1 },
    { 0, (char *) 0, (char *) 0, 0, 1, 1, 0, 0, 2 }
};

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define feof(p)	  ((p)->flag_eof)
#define ferror(p) ((p)->flag_err)
#define fileno(p) ((p)->fd)

#define getc(p)	  (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))

#define getchar()	getc(stdin)
#define putchar(x)	putc((x), stdout)

#define PERMS 0666 // rw for owner, group, others

// fopen: open file, return file ptr
FILE *fopen(char *name, char *mode);
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (!fp->flag_read && !fp->flag_write)
            break; // found free slot
    if (fp >= _iob + OPEN_MAX) // no free slots
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }

    if (fd == -1) // couldn't access name
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r') {
        fp->flag_read  = 1;
        fp->flag_write = 0;
        fp->flag_unbuf = 0;
        fp->flag_eof   = 0;
        fp->flag_err   = 0;
    } else {
        fp->flag_read  = 0;
        fp->flag_write = 1;
        fp->flag_unbuf = 0;
        fp->flag_eof   = 0;
        fp->flag_err   = 0;
    }

    return fp;
}

int _fillbuf(FILE *fp);
int _fillbuf(FILE *fp)
{
    unsigned long bufsize;

    if (!fp->flag_read || fp->flag_eof || fp->flag_err)
        return EOF;

    bufsize = fp->flag_unbuf ? 1 : BUFSIZ;
    if (fp->base == NULL) // no buffer yet
        if ((fp->base = malloc(bufsize)) == NULL)
            return EOF; // can't allocate buffer

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag_eof = 1;
        else
            fp->flag_err = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int _flushbuf(int, FILE *);

void prints(char *s);
void prints(char *s)
{
    write(stdout->fd, s, strlen(s));
}

int main()
{
    FILE *fin;


    if ((fin = fopen("/home/artem/projects/c/MyCProject/chapter_8/exercise_8-2.c", "r")) == NULL){
        prints("error opening file\n");
        exit(1);
    }
    prints("opened file\n");

    char *buf = malloc(1024 * 1024);
    int i = 0;
    int c;

    while ((c = getc(fin)) != EOF && i < 1024*1024 - 1)
        buf[i++] = (char) c;

    buf[i] = '\0';
    prints(buf);
}
