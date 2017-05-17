/*

Write a program that reads a C program and prints in alphabetical order each
group of variable names that are identical in the first 6 characters, but
different somewhere thereafter. Don't count words within strings and comments.
Make 6 a parameter that can be set from the command line.

*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// testcomment2 testcomment2

#define MAXWORD 100

static char* test1 = "teststring";
static char* test2 = "teststring";
static char test3  = 'z';

struct wnode {
    char *word;
    int count;
    struct wnode *left;
    struct wnode *right;
};

int getchar_c(void);
int getchar_c(void)
{
    int c1, c2;

    c1 = getchar();
    if (c1 == '/') {
        // possibly in comment
        c2 = getchar();
        if (c2 == '/') {
            // skip cpp comment
            while ((c1 = getchar()) != '\n')
                ;
        } else if (c2 == '*') {
            // skip c comment
            c1 = getchar();
            c2 = getchar();
            while (!(c1 == '*' && c2 == '/')) {
                c1 = c2;
                c2 = getchar();
            }
            c1 = getchar();
        }
    } else if (c1 == '"') {
        // skip string
        while ((c1 = getchar()) != '"')
            if (c1 == '\\')
                c1 = getchar();
        c1 = getchar();
    } else if (c1 == '\'') {
        // skip char
        while ((c1 = getchar()) != '\'')
            if (c1 == '\\')
                c1 = getchar();
        c1 = getchar();
    }
    return c1;
}

int getword(char *word);
int getword(char *word)
{
    int c;
    while (isspace(c = getchar_c()))
        ;

    while (!(isalpha(c) || c == '_' || c == EOF))
        c = getchar_c();

    if (c == EOF)
        return 0;

    int i = 0;
    while (isalpha(c) || c == '_') {
        word[i] = (char) c;
        c = getchar_c();
        i++;
    }

    word[i] = '\0';
    return 1;
}

struct wnode *update_tree(struct wnode *node, char *word);
struct wnode *update_tree(struct wnode *node, char *word)
{
    struct wnode *np;
    if (node == NULL) {
        np = (struct wnode *) malloc(sizeof(struct wnode));
        np->word = strdup(word);
        np->count = 1;
        np->left = NULL;
        np->right = NULL;
    } else {
        np = node;
        int cond = strcmp(word, node->word);
        if (cond == 0)
            node->count++;
        else if (cond > 0)
            node->right = update_tree(node->right, word);
        else
            node->left = update_tree(node->left, word);
    }
    return np;
}

void print_words(struct wnode *node, int prefix_length, char *previous_prefix, int *count);
void print_words(struct wnode *node, int prefix_length, char *previous_prefix, int *count)
{
    if (node != NULL) {
        print_words(node->left, prefix_length, previous_prefix, count);
        if (strncmp(previous_prefix, node->word, (unsigned long) prefix_length) != 0) {
            int prev_was_null = (previous_prefix[0] == '\0');
            previous_prefix[0] = '\0';
            strncat(previous_prefix, node->word, (unsigned long) prefix_length);
            if (!prev_was_null)
                printf("\n");
            if (*count == 1) {
                printf("\033[F");
                printf("\033[K");
            }
            *count = 0;
        }
        printf("%s ", node->word);
        (*count)++;
        print_words(node->right, prefix_length, previous_prefix, count);
    }
}

int collect_value(char *s, int *value);
int collect_value(char *s, int *value)
{
    int got    = 0;
    int result = 0;
    while (*s && isdigit(*s)) {
        got     = 1;
        result *= 10;
        result += *s - '0';
        s++;
    }
    if (got)
        *value = result;
    return got;
}

#define DEFAULT_PREFIX_LENGTH 6

int main(int argc, char *argv[])
{
    struct wnode *root = NULL;
    char word[MAXWORD];
    int val;

    int testvariable_foo;
    int testvariable_bar;

    while (getword(word)) {
        root = update_tree(root, word);
        word[0] = '\0';
    }

    int prefix_length = DEFAULT_PREFIX_LENGTH;
    while (*++argv)
        if (strcmp(*argv, "-p") == 0)
            if (*++argv)
                if (collect_value(argv[0], &val))
                    prefix_length = val;

    char previous_prefix[MAXWORD] = "";
    int count = 0;

    print_words(root, prefix_length, previous_prefix, &count);
    if (count == 1)
        printf("\033[F");
    printf("\n");

}

