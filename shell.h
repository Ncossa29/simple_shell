#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passdata
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} data_t;

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(data_t *);
} 
builtin_table;



int hsh(data_t *, char **);
int find_builtin(data_t *);
void find_cmd(data_t *);
void fork_cmd(data_t *);


int nk_cmd(data_t *, char *);
char *dupchar(char *, int, int);
char *find_path(data_t *, char *, char *);


int loophsh(char **);

/
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);


int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);


char *_strdup(const char *);
void _puts(char *);
int _putchar(char);


char *_strncat(char *, char *, int);
char *_strchr(char *, char);


char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);


char **strtow(char *, char *);
char **strto(char *, char);


int nk_free(void **);


int active(data_t *);
int isdelim(char, char *);
int the_alpha(int);
int _atoi(char *);

int err_atoi(char *);
void print_error(data_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void comments_off(char *);


int nk_exit(data_t *);
int nk_cd(data_t *);
int nk_help(data_t *);


int nk_history(data_t *);
int nkalias(data_t *);


ssize_t get_input(data_t *);
int _getline(data_t *, char **, size_t *);
void sigintHandler(int);


void clear_data(data_t *);
void set_data(data_t *, char **);
void free_data(data_t *, int);

char **get_environ(data_t *);
int nk_unsetnv(data_t *, char *);
int nk_setnv(data_t *, char *, char *);


char *get_env(data_t *, const char *);
int nk_env(data_t *);
int nk_setenv(data_t *);
int nk_unsetenv(data_t *);
int env_list(data_t *);


char *get_history_file(data_t *data);
int write_history(data_t *data);
int read_history(data_t *idata);
int make_history_list(data_t *data, char *buf, int linecount);
int renumber_history(data_t *idata);


list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);


size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);


int ischain(data_t *, char *, size_t *);
void chk_chain(data_t *, char *, size_t *, size_t, size_t);
int replace_alias(data_t *);
int replace_vars(data_t *);
int replace_string(char **, char *);

#endif
