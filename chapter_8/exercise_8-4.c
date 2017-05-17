/*

Write fseek. Make sure it works well with the buffering code.

int fseek(FILE *fp, long offset, int origin)

*/

#include <sys/file.h> // contains open and O_RDONLY etc
#include <unistd.h>   // contains read, write and close

#include <stdlib.h> // for malloc
#include <string.h> // for strlen

#include <errno.h>

//#define NULL      0 // already defined
#define EOF       (-1)
#define BUFSIZ    10
#define OPEN_MAX  20    // max files open at once

typedef struct _iobuf {
    ssize_t  cnt;	  // characters left
    char	 *ptr;	  // next character position
    char	 *base;	  // location of buffer
    int		 flag;	  // mode of file access
    int		 fd;	  // file descriptor
} FILE;

enum flags {
    _READ = 01,	  // file open for reading
    _WRITE = 02,  // file open for writing
    _UNBUF = 04,  // file is unbuffered
    _EOF = 010,	  // EOF has occurred on this file
    _ERR = 020	  // error occurred on this file
};

extern FILE _iob[OPEN_MAX];
FILE _iob[OPEN_MAX] = {
    { 0, (char *) 0, (char *) 0, _READ, 0 },
    { 0, (char *) 0, (char *) 0, _WRITE, 1 },
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define feof(p)	  (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p)	  (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))

#define getchar()	getc(stdin)
#define putchar(x)	putc((x), stdout)

#define PERMS 0666 // rw for owner, group, others

void prints(char *s);
void prints(char *s)
{
    write(stdout->fd, s, strlen(s));
}

// fopen: open file, return file ptr
FILE *fopen(char *name, char *mode);
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
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
    fp->flag = (*mode == 'r') ? _READ : _WRITE;

    return fp;
}

ssize_t _fbufsize(FILE *fp);
ssize_t _fbufsize(FILE *fp)
{
    return (fp->flag & _UNBUF) ? 1 : BUFSIZ;
}

void _fclearbuf(FILE *fp);
void _fclearbuf(FILE *fp)
{
    fp->ptr = fp->base;
    if ((fp->flag & _READ) == _READ)
        fp->cnt = 0;
    else
        fp->cnt = (ssize_t) _fbufsize(fp);
}

int _fillbuf(FILE *fp);
int _fillbuf(FILE *fp)
{
    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;

    if (fp->base == NULL) // no buffer yet
        if ((fp->base = malloc((unsigned long)_fbufsize(fp))) == NULL)
            return EOF; // can't allocate buffer

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, (size_t) _fbufsize(fp));
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int fflush(FILE *fp);
int fflush(FILE *fp)
{
    if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
        return EOF;

    if (fp->cnt != (ssize_t) _fbufsize(fp))
        if (write(fp->fd, fp->base, (size_t) _fbufsize(fp) - (size_t) fp->cnt) == -1) {
            fp->flag |= _ERR;
            fp->cnt = 0;
            return EOF;
        }
    _fclearbuf(fp);

    return 1;
}

int _flushbuf(int c, FILE *fp);
int _flushbuf(int c, FILE *fp)
{
    if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
        return EOF;

    if (fp->base == NULL) {// no buffer yet
        if ((fp->base = malloc((unsigned long)_fbufsize(fp))) == NULL)
            return EOF; // can't allocate buffer
        _fclearbuf(fp);
    }
    fflush(fp);

    *(fp->ptr++) = (char) c;
    fp->cnt--;
    return c;
}

int fclose(FILE *fp);
int fclose(FILE *fp)
{
    int result = close(fp->fd);
    free(fp->base);
    fp->base = NULL;
    fp->flag = 0;
    return result;
}

int fseek(FILE *fp, long long offset, int origin);
int fseek(FILE *fp, long long offset, int origin)
{
    fflush(fp);
    _fclearbuf(fp);
    lseek(fp->fd, offset, origin);
    return 1;
}

int main()
{
    FILE *fin, *fout;

    if ((fin = fopen("/home/artem/projects/c/MyCProject/chapter_8/ex_8_04.test", "r")) == NULL)
        prints("error opening /home/artem/projects/c/MyCProject/chapter_8/ex_8_04.test\n");

    // reading seek test
    for (int i = 0; i < 6; i++)
        putc((char) getc(fin), stdout);

    fseek(fin, 0, 0);

    for (int i = 0; i < 6; i++)
        putc((char) getc(fin), stdout);

    fflush(stdout);

    // writing seek test

    if ((fout = fopen("/home/artem/projects/c/MyCProject/chapter_8/ex_8_04.test", "a")) == NULL)
        prints("error opening ex_8_04.test\n");

    putc('1', fout);
    putc('2', fout);
    putc('3', fout);
    fseek(fout, 0, 0);
    fflush(fout);
    putc('7', fout);
    putc('8', fout);
    putc('9', fout);
    fflush(fout);
}


