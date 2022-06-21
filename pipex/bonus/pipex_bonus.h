/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:29:47 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/09 17:13:21 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../get_next_line/get_next_line.h"
# include <sys/types.h>
# include <sys/syscall.h> 
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <string.h> // Для strerror
# include <errno.h> /* содержит объявления для errno */

typedef struct s_pipes
{
	int	**fds;
	int	last_pipe_num;
	int	current_pipe_num;
	int	no_pipe_flag;
}	t_pipes;
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
typedef struct s_files
{
	char	*input_file_name;
	char	*output_file_name;
	int		here_doc_flag;
	char	*limiter;
}	t_files;
typedef struct s_process
{
	char	**command;
	int		last_process_num;
	int		current_process_num;
	int		id;
}	t_process;

void		ft_free(void *pointer);
int			ft_split_free(char **s);
void		ft_free_pipes(t_pipes *pipes);
void		ft_free_processes(t_process **processes);
void		ft_errors(t_pipes *pipes, t_process **processes);
char		*ft_check_access(char *command_name, char **path);
void		ft_print_split(char **s);//r
int			ft_strcmp_hand(char *s1, char*s2);
int			num_of_strings(char const *s, char c, int start);
char		**ft_find_word_path(char **envp, int *success_flag);
char		**ft_get_path(char **envp);
int			ft_close_unnecessary_fds(t_pipes *pipes, t_process **processes);
int			ft_read_here_doc(char *limiter, t_pipes *pipes);
int			ft_handle_dup_first_proc(t_files files, t_pipes *pipes);
int			ft_handle_dup_last_proc(t_files files, \
t_pipes *pipes, int current_process_num);
int			duplicate_fd(int current_process_num, \
int num_of_last_process, t_pipes *pipes, t_files files);
void		ft_not_in_quotes_part(int iter, t_vars *vars, \
t_pipes *pipes, t_process **processes);
void		ft_define_command(int iter, t_vars *vars, \
t_pipes *pipes, t_process **processes);
void		ft_check_access_big(int iter, t_vars vars, \
t_pipes *pipes, t_process **processes);
t_process	**process_malloc(t_process **processes, \
t_vars *vars, t_pipes *pipes, int iter);
t_process	**process_init(t_process **processes, t_vars vars, t_pipes *pipes);
t_pipes		*ft_start_pipes(int num_of_processes, t_vars vars, t_pipes *pipes);
t_pipes		*ft_init_pipes(int num_of_processes, t_pipes *pipes, t_vars vars);
void		ft_new_process_only(t_pipes *pipes, \
t_files files, t_process **processes, t_vars vars);
int			ft_execute(t_pipes *pipes, t_files files, \
t_process **processes, t_vars vars);
int			ft_waiter(int num_of_processes, t_process **processes);
char		*ft_check_here_doc(char **argv);
void		init_variables(t_vars *vars, t_files *files);
t_process	**init_process_and_pipe(t_process **processes, t_vars vars, \
t_pipes **pipes, t_files files);
int			pipex(int argc, char **argv, char **envp);
#endif