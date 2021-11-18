#include "minishell.h"

t_job	*ms_job_newlst(void)
{
	t_job	*new;

	new = ft_calloc(1, sizeof(t_job));
	if (!new)
		return (NULL);
/* 	new->cmd = NULL;
	new->next = NULL;
	new->file = NULL;
	new->previous = NULL; */
	return (new);
}

t_job	*ms_job_last(t_job *job)
{
	while (job)
	{
		if (job->next == NULL)
			return (job);
		job = job->next;
	}
	return (job);
}

void	ms_job_addback(t_job **job, t_job *new_job)
{
	t_job *last_job;

	if (*job == NULL)
		*job = new_job;
	else
	{
		last_job = ms_job_last(*job);
		last_job->next = new_job;
		new_job->previous = last_job;
	}
}