/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:39:19 by mmeredit          #+#    #+#             */
/*   Updated: 2022/07/02 10:56:20 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Все команды исполняются в подпроцессах. Исключение - builtins

// void	print_command(char **str)
// {
// 	int	i;

// 	i = 0;
// 	if (str)
// 	{
// 		while (str[i])
// 			printf ("%s\n", str[i++]);
// 	}
// }

int	parser_next(t_command **command, t_info *info)
{
	t_command	*tmp;
	int			i;

	i = 0;
	tmp = *command;
	while (tmp != NULL)
	{
		if (tmp->flag == 1)
			opening_dollar(tmp, &i, info);
		i = 0;
		tmp = tmp->next;
	}
	return (0);
}

t_command	*pre_parser(t_info *info, char *p)
{
	t_command	*command;
	int			i;

	i = 0;
	command = NULL;
	while (p[i])
		run_str(is_token(p[i]), p, &command, &i);
	if (command != NULL)
		parser_next(&command, info);
	return (command);
}

char	*ft_readline(char *p, t_info *info)
{
	p = readline("minishell$ ");
	if (p)
		add_history(p);
	else
	{
		printf ("exit\n");
		all_free(info, 1, NULL);
		exit(EXIT_SUCCESS);
	}
	return (p);
}

int	main(int ag, char **av, char **env)
{
	t_info		info;
	char		*p;
	t_command	*command;
	char		**str;

	(void) av;
	(void) ag;
	p = NULL;
	str = NULL;
	command = NULL;
	if (!init(&info, env))
		return (write(2, "MEM NOT ALLOC!", 14));
	signal_handlers();
	while (!info.exit_f)
	{
		p = ft_readline(p, &info);
		if (p != NULL && !ft_strcmp_v2(p, "\n"))
		{
			if (lexer(&info, p) == 0)
			{
				command = pre_parser(&info, p);
				str = parser(&command);
				if (str[0] != NULL)
				{
					ft_pipex(str, &info);
				}	
			}
			// print_command(str);
			str = ft_free_array(str);
			all_free(&info, 2, &command);
		}
		free(p);
		p = NULL;
	}
	all_free(&info, 1, &command);
	if (p != NULL)
		free(p);
	return (0);
}

//void	ft_check_print(t_token **token)
//{
//	t_token	*tmp;
//
//	tmp = *token;
//	if (tmp != NULL)
//	{
//		while (tmp->next != NULL)
//		{
//			printf ("%d ", tmp->token);
//			tmp = tmp->next;
//		}
//		printf ("%d\n", tmp->token);
//	}
//}

// void	ft_check_print(t_command **command)
// {
// 	t_command	*tmp;

// 	tmp = *command;
// 	if (tmp != NULL)
// 	{
// 		while (tmp->next != NULL)
// 		{
// 			printf ("%s\n", tmp->str);
// 			tmp = tmp->next;
// 		}
// 		printf ("%s\n", tmp->str);
// 	}
// }
