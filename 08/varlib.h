#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXVARS 200
struct var 
{
    char *str;
    int global;
};

static struct var tab[MAXVARS];
static char *new_string(char *, char *);
static struct var *find_item(char *, int);
int VLstore(char *name, char *val);
char *new_string(char *name, char *val);
char *VLlookup(char *name);
int VLexport(char *name);
static struct var * find_item(char *name, int first_blank);
void VLlist();
int VLenviron2table(char *env[]);
char **VLtable2environ();
