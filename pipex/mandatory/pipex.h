/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:47 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/21 14:18:34 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/syscall.h> 
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h> // Для strerror
# include <errno.h> /* содержит объявления для errno */
# include "../../libft/libft.h"
# include "../../get_next_line/get_next_line.h"
// # include "../../minishell.h"

typedef struct s_vars
{
	int		i;
	int		j;
	int		count;
	int		counter;
	int		current_process;
	int		start;
	int		num_of_processes;
	int		argc;

	char	**argv;
	char	**envp;
	char	**s;
}	t_vars;

typedef struct s_lists
{
	char			*key;
	char			*value;
	struct s_lists	*next;
}	t_lists;

typedef struct s_file
{
	char				*file;
	int					type_flag;//0-heredoc, 1-input, 2-output, 3-output_append
	struct s_file		*next;
}	t_file;
typedef struct s_commands
{
	char				*command;
	struct s_commands	*next;
}	t_commands;
typedef struct s_process_config
{
	t_commands				*command;
	char					*heredoc;
	int						number_of_proc;
	t_file					*read_files;
	t_file					*out_files;
	int						*here_doc_pipes;
	int						from_prev_pipe;
	int						to_next_pipe;
	int						im_last_flag;
	int						id;
	struct s_process_config	*next;
}	t_process_config;

int					ft_split_print(char **s);
void				ft_free(void *pointer);
int					ft_split_free(char **s);
void				ft_errors(int code);
char				*ft_check_access(char *command_name, char **path);
void				ft_print_split(char **s);
int					ft_strcmp_hand(char *s1, char*s2);
int					num_of_strings(char const *s, char c);
char				**ft_find_word_path(char **envp);
char				**ft_get_path(char **envp);
int					ft_waiter(t_process_config *process_config);
t_process_config	*ft_parce_commands(char **arr_of_comands, \
t_process_config	*process_config);

void				ft_check_malloc(void *data);
void				*add_to_end(void *list, void *elem, int which_struct);
t_process_config	*ft_create_proc_elem(int number);
t_file				*ft_create_file_elem(char *file_name, int type_flag);
t_commands			*ft_create_command_elem(char *command_name);
char				*ft_check_access_new(char *cmd, char **paths);
char				**ft_get_path_new(char **env);
char				**ft_get_array(t_commands *list);
void				*add_to_top(void *list, void *elem, int which_struct);
char				*ft_create_str(char *str);
void				ft_handle_write_stuff(t_process_config *process);
void				ft_handle_read_stuff(t_process_config *process);
int					ft_heredoc_handler(t_process_config *process);
#endif