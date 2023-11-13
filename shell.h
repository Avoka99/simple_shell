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
 * struct list_str - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct list_str
{
	int num;
	char *str;
	struct list_str *next;
} list_t;

/**
 * struct passav - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @l_c: the error count
 * @err_no: the error code for exit()s
 * @lc_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @hist: the history node
 * @alias: the alias node
 * @env_ch: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd: address of pointer to cmd_buffer, on if chaining
 * @cmmd: CMD_type ||, &&, ;
 * @rdfd: the fd from which to read line input
 * @histc: the history line number count
 */
typedef struct passav
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int l_c;
	int err_no;
	int lc_flag;
	char *fname;
	list_t *env;
	list_t *hist;
	list_t *alias;
	char **environ;
	int env_ch;
	int status;

	char **cmd;
	int cmmd;
	int rdfd;
	int histc;
} avok_t;

#define AVOK_INIT \
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
	int (*func)(avok_t *);
} builtin_table;

int exec_main(avok_t *av, char **ac);
int av_builtin(avok_t *av);
void find_exec(avok_t *av);
void exec_com(avok_t *av);
int exec(avok_t *av, char *path);
char *dup_chars(char *str, int start, int stop);
char *_path(avok_t *av, char *str, char *cmd);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *_starts(const char *haystack, const char *needle);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **_strtow(char *, char);
char *_memset(char *, char, unsigned int);
void free_array(char **ptr);
void *_realloc(void *, unsigned int, unsigned int);
int free_ptr(void **ptr);
int _inter(avok_t *av);
int _isdelim(char, char *);
int _isalpha(int);
int _atoi(char *str);
int err_atoi(char *str);
void print_error(avok_t *av, char *msg);
int print_dec(int input, int fd);
char *con_num(long int num, int base, int flags);
void rm_cmm(char *buffer);
int av_exit(avok_t *av);
int av_cd(avok_t *av);
int av_help(avok_t *av);
int av_hist(avok_t *av);
int av_alias(avok_t *av);
int unset_alias(avok_t *av, char *str);
int set_alias(avok_t *av, char *str);
int print_alias(list_t *node);
ssize_t user_input(avok_t *av);
int _getline(avok_t *av, char **ptr, size_t *size);
void handle_sig(__attribute__((unused))int sig_num);
ssize_t enter_buffer(avok_t *av, char **buffer, size_t *size);
ssize_t rd_buffer(avok_t *av, char *buffer, size_t *size);
void clear_av(avok_t *av);
void set_av(avok_t *av, char **ac);
void free_av(avok_t *av, int ac);
char *_getenv(avok_t *av, const char *nm);
int av_env(avok_t *av);
int av_setenv(avok_t *av);
int av_unsetenv(avok_t *av);
int env_list(avok_t *av);
char **user_env(avok_t *av);
int _unsetenv(avok_t *av, char *var);
int _setenv(avok_t *av, char *var, char *val);
char *user_histf(avok_t *av);
int wrt_hist(avok_t *av);
int rd_hist(avok_t *av);
int hist_list(avok_t *av, char *buffer, int linec);
int rnum_hist(avok_t *av);
list_t *add_node(list_t **head, const char *str, int num);
list_t *node_end(list_t **head, const char *str, int num);
size_t list_str(const list_t *head);
int del_node(list_t **head, unsigned int i);
void free_list(list_t **ptr);
size_t list_len(const list_t *head);
char **list_to_str(list_t *head);
size_t print_list(const list_t *head);
list_t *node_begins(list_t *head, char *p, char c);
ssize_t node_index(list_t *head, list_t *node);
int chain_com(avok_t *av, char *buffer, size_t *size);
void check_chain(avok_t *av, char *buffer, size_t *p, size_t i, size_t size);
int rep_alias(avok_t *av);
int rep_vars(avok_t *av);
int rep_str(char **old, char *new);

#endif

