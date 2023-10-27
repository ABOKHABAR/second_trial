#ifndef _H7k2L_S1sH_
#define _H7k2L_S1sH_

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

#define H7K2L_READ_BUF_SIZE 1024
#define H7K2L_WRITE_BUF_SIZE 1024
#define H7K2L_BUF_FLUSH -1

#define H7K2L_CMD_NORM 0
#define H7K2L_CMD_OR 1
#define H7K2L_CMD_AND 2
#define H7K2L_CMD_CHAIN 3

#define H7K2L_CONVERT_LOWERCASE 1
#define H7K2L_CONVERT_UNSIGNED 2

#define H7K2L_USE_GETLINE 0
#define H7K2L_USE_STRTOK 0

#define H7K2L_HIST_FILE ".h7k2l_shell_history"
#define H7K2L_HIST_MAX 4096

extern char **h7k2l_environ;


/**
 * struct h7k2l_liststr - A structure to represent a list of strings.
 *
 * @num: An integer associated with the string.
 * @str: The string.
 * @next: Pointer to the next node in the list.
 */
typedef struct h7k2l_liststr
{
	int num;
	char *str;
	struct h7k2l_liststr *next;
} h7k2l_list_t;

/**
*struct h7k2l_passinfo- Structure to hold information related to shell commands
*
* @h7k2l_arg: The first argument or command.
* @h7k2l_argv: An array of command arguments.
* @h7k2l_path: The path to the command.
* @h7k2l_argc: The number of arguments.
* @h7k2l_line_count: The current line count in the shell.
* @h7k2l_err_num: Error number.
* @h7k2l_linecount_flag: Line count flag.
* @h7k2l_fname: File name.
* @h7k2l_env: Pointer to the environment list.
* @h7k2l_history: Pointer to the history list.
* @h7k2l_alias: Pointer to the alias list.
* @h7k2l_environ: Pointer to the shell environment.
* @h7k2l_env_changed: Flag to indicate environment changes.
* @h7k2l_status: Command execution status.
* @h7k2l_cmd_buf: Command buffer.
* @h7k2l_cmd_buf_type: Type of command buffer.
* @h7k2l_readfd: File descriptor for reading.
* @h7k2l_histcount: History count.
*/
typedef struct h7k2l_passinfo
{
	char *h7k2l_arg;
	char **h7k2l_argv;
	char *h7k2l_path;
	int h7k2l_argc;
	unsigned int h7k2l_line_count;
	int h7k2l_err_num;
	int h7k2l_linecount_flag;
	char *h7k2l_fname;
	h7k2l_list_t *h7k2l_env;
	h7k2l_list_t *h7k2l_history;
	h7k2l_list_t *h7k2l_alias;
	char **h7k2l_environ;
	int h7k2l_env_changed;
	int h7k2l_status;
	char **h7k2l_cmd_buf;
	int h7k2l_cmd_buf_type;
	int h7k2l_readfd;
	int h7k2l_histcount;
} h7k2l_info_t;

#define H7K2L_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
 * struct h7k2l_builtin - Structure to represent a built-in shell command.
 *
 * @h7k2l_type: The type or name of the built-in command.
 * @h7k2l_func: A function pointer to the implementation of the command.
 */
typedef struct h7k2l_builtin
{
	char *h7k2l_type;
	int (*h7k2l_func)(h7k2l_info_t *);
} h7k2l_builtin_table;

int h7k2l_hsh(h7k2l_info_t *, char **);
int h7k2l_find_builtin(h7k2l_info_t *);
void h7k2l_find_cmd(h7k2l_info_t *);
void h7k2l_fork_cmd(h7k2l_info_t *);

int h7k2l_is_cmd(h7k2l_info_t *, char *);
char *h7k2l_dup_chars(char *, int, int);
char *h7k2l_find_path(h7k2l_info_t *, char *, char *);

int h7k2l_loophsh(char **);

void h7k2l_eputs(char *);
int h7k2l_eputchar(char);
int h7k2l_putfd(char c, int fd);
int h7k2l_putsfd(char *str, int fd);

int h7k2l_strlen(char *);
int h7k2l_strcmp(char *, char *);
char *h7k2l_starts_with(const char *, const char *);
char *h7k2l_strcat(char *, char *);

char *h7k2l_strcpy(char *, char *);
char *h7k2l_strdup(const char *);
void h7k2l_puts(char *);
int h7k2l_putchar(char);

char *h7k2l_strncpy(char *, char *, int);
char *h7k2l_strncat(char *, char *, int);
char *h7k2l_strchr(char *, char);

char **h7k2l_strtow(char *, char *);
char **h7k2l_strtow2(char *, char);

char *h7k2l_memset(char *, char, unsigned int);
void h7k2l_ffree(char **);
void *h7k2l_realloc(void *, unsigned int, unsigned int);

int h7k2l_bfree(void **);

int h7k2l_interactive(h7k2l_info_t *);
int h7k2l_is_delim(char, char *);
int h7k2l_isalpha(int);
int h7k2l_atoi(char *);

int h7k2l_erratoi(char *);
void h7k2l_print_error(h7k2l_info_t *, char *);
int h7k2l_print_d(int, int);
char *h7k2l_convert_number(long int, int, int);
void h7k2l_remove_comments(char *);

int h7k2l_myexit(h7k2l_info_t *);
int h7k2l_mycd(h7k2l_info_t *);
int h7k2l_myhelp(h7k2l_info_t *);

int h7k2l_myhistory(h7k2l_info_t *);
int h7k2l_myalias(h7k2l_info_t *);

ssize_t h7k2l_get_input(h7k2l_info_t *);
int h7k2l_getline(h7k2l_info_t *, char **, size_t *);
void h7k2l_sigintHandler(int);

void h7k2l_clear_info(h7k2l_info_t *);
void h7k2l_set_info(h7k2l_info_t *, char **);
void h7k2l_free_info(h7k2l_info_t *, int);

char *h7k2l_getenv(h7k2l_info_t *, const char *);
int h7k2l_myenv(h7k2l_info_t *);
int h7k2l_mysetenv(h7k2l_info_t *);
int h7k2l_myunsetenv(h7k2l_info_t *);
int h7k2l_populate_env_list(h7k2l_info_t *);

char **h7k2l_get_environ(h7k2l_info_t *);
int h7k2l_unsetenv(h7k2l_info_t *, char *);
int h7k2l_setenv(h7k2l_info_t *, char *, char *);

char *h7k2l_get_history_file(h7k2l_info_t);
int h7k2l_write_history(h7k2l_info_t);
int h7k2l_read_history(h7k2l_info_t);
int h7k2l_build_history_list(h7k2l_info_t, char *, int);
int h7k2l_renumber_history(h7k2l_info_t);

h7k2l_list_t *h7k2l_add_node(h7k2l_list_t **, const char *, int);
h7k2l_list_t *h7k2l_add_node_end(h7k2l_list_t **, const char *, int);
size_t h7k2l_print_list_str(const h7k2l_list_t *);
int h7k2l_delete_node_at_index(h7k2l_list_t **, unsigned int);
void h7k2l_free_list(h7k2l_list_t **);

size_t h7k2l_list_len(const h7k2l_list_t *);
char **h7k2l_list_to_strings(h7k2l_list_t *);
size_t h7k2l_print_list(const h7k2l_list_t *);
h7k2l_list_t *h7k2l_node_starts_with(h7k2l_list_t *, char *, char);
ssize_t h7k2l_get_node_index(h7k2l_list_t *, h7k2l_list_t *);

int h7k2l_is_chain(h7k2l_info_t *, char *, size_t *);
void h7k2l_check_chain(h7k2l_info_t *, char *, size_t *, size_t, size_t);
int h7k2l_replace_alias(h7k2l_info_t *);
int h7k2l_replace_vars(h7k2l_info_t *);
int h7k2l_replace_string(char **, char *);

#endif
