#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "pipex/mandatory/pipex.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# define SEP 0
# define WORD 1
# define FIELD 2
# define EXP_FIELD 3
# define REDIR_OUT 4
# define REDIR_IN 5
# define REDIR_APPEND 6
# define REDIR_INSOLUSION 7
# define PIPE 8
# define MAXDIR 256
//BUILT
# define PWD "pwd\0"
# define ENV "env\0"
# define EXPORT "export\0"
# define UNSET "unset\0"
# define CD "cd\0"
# define ECHO "echo\0"
# define EXIT "exit\0"

extern char	**environ;

# define NOTMALLOC -1

typedef struct s_token
{
	int				token;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				*str;
	int					flag;
	struct s_command	*next;
}	t_command;

typedef struct s_errors
{
	int	flag;
	int	error;
}	t_errors;

// typedef int (*t_builtin_ptr)(t_lists *list, struct s_info *info);

typedef struct s_info
{
	char			*res_word[7];	// ключевые слова
	char			**envp;     	// переменная окружения
	t_lists			*envp_list;		// переменная окружения в листe
	t_token			*token;			// лист токенов
	int				envp_f;			// флаг на изменение envp. изменяется, если зменился envp_list
	int				exit_f;			// флаг на выход из программы
	int				status;			// когда вызываем $?
}	t_info;

//typedef int (*t_builtin_ptr)(t_lists *list, struct s_info *info);
//
//t_builtin_ptr	builtins[7];

// typedef int (*t_builtin_ptr)(t_lists *list, struct s_info *info);

// t_builtin_ptr	builtins[7];	// массив функций ключевых слов

int			ft_strlens(char *str);
int			mem_lists(t_lists **envp_list, char *str);
char		*key_value_cpy(char *dest, char *src, int flag);
int			key_value_mem(char *str, int flag);
int			start_lists(t_lists **envp_list, char **envp);
void		print_error(t_info *info, int flag);
void		*ft_free_list(t_lists **envp_list);
char		**ft_free_array(char **envp);
int			init(t_info *info, char **env);
void		ft_strcopy(char *dest, char *src);
void		free_token(t_token **token);
void		ft_free_command(t_command **command);

int			lexer(t_info *info, char *line);
void		all_free(t_info *info, int flag, t_command **command);
int			is_token(char c);
int			check_fields(t_token **token);
int			skip_field(t_token **token, int x);
int			sub_check(int token, char *p, int *i);

int			parser_next(t_command **command, t_info *info);
int			is_not_word(int x);
char		**parser(t_command **command);
int			all_check(t_info *info, char *p);
int			count_status(int status);
void		ft_itoan(char *dst, int status, int *j);
int			is_not_word(int x);
int			ft_strcmp_v2(char *cmp, char *str);

char		*check_env_var(t_lists *envp_list, char *str);
char		*ft_copy(char *dst, char *src, char *env, int count);
int			run_str(int token, char *p, t_command **command, int *i);
void		ft_strcopy2(char *dest, char *src);
int			opening_dollar(t_command *cmd, int *i, t_info *info);
void		signal_handlers(void);
int			f(t_command *command);
int			skip_words(int token, char *p, int *i);

int			ft_pipex(char **arr_of_comands, t_info *info);
t_info		*ft_waiter(t_process_config *process_config, t_info *info);
int			ft_heredoc_handler(t_process_config *process);
//BUILTS
// int			ft_check_if_builtins(t_process_config *process);
char		*ft_pwd(int print_flag);
void		ft_env(t_info *info);
void		ft_print_lists(t_lists *list, char *elem_needed);
t_lists		*ft_create_list_elem(char *key, char *value);
int			ft_check_if_builtins(t_process_config *process, t_info *info);
t_lists		*ft_unlink_elem_from_list(t_lists \
*list, char *unset, int free_flag);
t_info		*ft_unset(t_info *list, char **unset);
t_lists		*ft_cd(char *path, t_lists **env);
void		ft_echo(char **arr);
int			ft_check_n_arg_echo(char *arg);
void		ft_exit(char **arr);
char		**ft_get_array_list(t_lists *list);
char		**ft_get_array_com(t_commands *list);
void		ft_echo_part(char **arr);
void		ft_echo(char **arr);
void		ft_exit(char **arr);
void		ft_cd_part(char **old_pwd, char **current_pwd, char ***tmp);
t_lists		*ft_cd(char *path, t_lists **env);
void		ft_export_with_no_args(t_lists *list);
int			ft_check_name_export(char **key_value, char **elems, int *i);
int			ft_export_find_place(t_lists *env, t_lists **prev_elem_env, \
char **key_value, int *match_flag);
t_lists		*ft_export_place_new_el(int match_flag, t_lists \
*prev_elem_env, t_lists *env, char **key_value);
t_lists		*ft_export(t_lists *env, char **elems);
int			ft_check_exit_arg(char **arg);
int			ft_exp_uns_name(char *arg);
char		**ft_exp_uns_parser(char *arg);
void		*ft_get_val_by_key(t_lists *list, char *key_needed);
int			ft_chech_words(t_process_config *process, t_info *info);
void		ft_check_builtins_part1(t_process_config *process, t_info *info);


#endif