#include "minishell.h"

int is_semi_pipe(char *str)
{
	if (!str)
		return (0);
	return((!ft_strcmp(str, ";") || !ft_strcmp(str, "|")));
}

int is_redir(char *str)
{
	if (!str)
		return (0);
	 return((!ft_strcmp(str, ">") || !ft_strcmp(str, "<")) || !ft_strcmp(str, ">>"));

}

int ft_syntax_error(t_parse *head)
{
	t_parse *new;

	new = head;
	if (!new)
		return (0);
	if (new && !(ft_strcmp(new->content, "|")) && !new->type)
		return (!ft_error("syntax error near unexpected token", new->content, 1));
	while (new && new->next)
	{
		if (!new->type)
			if ((is_redir(new->content) && is_redir(new->next->content))
			|| (is_semi_pipe(new->content) && is_semi_pipe(new->next->content)))
				return (!ft_error("syntax error near unexpected token", new->content, 1));
			new = new->next;
	}
	if (!new->type)
		if (!ft_strcmp(new->content, "|") || is_redir(new->content))
			return (!ft_error("syntax error near unexpected token", new->content, 1));
	return (0);
}

int	ft_error(char *mess, char *mess2, int status)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, mess, ft_strlen(mess));
	if (mess2)
	{
		write(2, ": ", 2);
		write(2, mess2, ft_strlen(mess2));
	}
	write(2, "\n", 1);
	g_status = status;
	return (0);
}