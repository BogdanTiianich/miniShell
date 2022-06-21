/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:39:19 by mmeredit          #+#    #+#             */
/*   Updated: 2022/06/21 15:34:26 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Все команды исполняются в подпроцессах. Исключение - builtins

void	print_command(char **str)
{
	int	i;

	i = 0;
	if (str && *str)
	{
		while (str[i])
			printf ("%s\n", str[i++]);
	}
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

char	*ft_readline(char *p)
{
	p = readline("minishell$ ");
	if (p && *p)
		add_history(p);
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
	if (!init(&info, env))
		return (write(2, "MEM NOT ALLOC!", 14));
	while (!info.exit_f)
	{
		p = ft_readline(p);
		lexer(&info, p);
		command = pre_parser(&info, p);
		str = parser(&command);
		// print_command(str);
		av++;
		ft_pipex(av, &info);
		ft_free_array(str);
		all_free(&info, 2, &command);
		free(p);
		p = NULL;
		break;
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
