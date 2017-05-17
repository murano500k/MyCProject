    /*

    Rewrite the program cat using read, write, open, and close instead of their
    standard library equivalents. Perform experiments to determine the relative
    speeds of the two versions.

    */

    #include <stdio.h>
    #include <stdlib.h>

    #include <sys/file.h> // contains open and O_RDONLY etc
    #include <unistd.h>   // contains read, write and close

    void filecopy(int fin, int fout);
    void filecopy(int fin, int fout)
    {
        char buf[BUFSIZ];
        ssize_t n;
        while ((n = read(fin, buf, BUFSIZ)) > 0)
            write(fout, buf, (size_t) n);
    }

    int main(int argc, char *argv[])
    {
        int fin;
        char *prog = argv[0]; // program name for errors

        if (argc == 1)
            filecopy(0, 1);
        else
            while (--argc > 0)

                if ((fin = open(*++argv, O_RDONLY, 0)) == -1) {
                    fprintf(stderr, "%s: can't open %s\n",
                            prog, *argv);
                    exit(1);
                } else {
                    filecopy(fin, 1);
                    close(fin);
                }
        if (ferror(stdout)) {
            fprintf(stderr, "%s: error writing stdout\n", prog);
            exit(2);
        }
        exit(0);
    }
