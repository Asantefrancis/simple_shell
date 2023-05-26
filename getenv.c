#include "shell.h"

/**
 * copy_env_strings - Creates a copy of the environment variables as a string array
 * @env: Pointer to the environment variables linked list
 * Return: String array containing the environment variables
 */
char **copy_env_strings(list_t *env)
{
	char **env_strings;
	int count = 0;
	list_t *node = env;

	while (node != NULL)
	{
		count++;
		node = node->next;
	}

	env_strings = malloc(sizeof(char *) * (count + 1));
	if (env_strings == NULL)
		return NULL;

	node = env;
	count = 0;
	while (node != NULL)
	{
		env_strings[count] = strdup(node->str);
		if (env_strings[count] == NULL)
		{
			/* Free memory in case of error */
			while (count > 0)
			{
				count--;
				free(env_strings[count]);
			}
			free(env_strings);
			return NULL;
		}
		count++;
		node = node->next;
	}
	env_strings[count] = NULL;

	return env_strings;
}

/**
 * remove_env_var - Remove an environment variable
 * @env: Pointer to the environment variables linked list
 * @var: The name of the environment variable to remove
 * Return: 1 on success, 0 if variable not found
 */
int remove_env_var(list_t **env, const char *var)
{
	list_t *current, *prev;

	if (*env == NULL || var == NULL)
		return 0;

	current = *env;
	prev = NULL;
	while (current != NULL)
	{
		if (starts_with(current->str, var) == current->str)
		{
			if (prev == NULL)
				*env = current->next;
			else
				prev->next = current->next;
			free(current->str);
			free(current);
			return 1;
		}
		prev = current;
		current = current->next;
	}

	return 0;
}

/**
 * set_env_var - Set or modify an environment variable
 * @env: Pointer to the environment variables linked list
 * @var: The name of the environment variable
 * @value: The value to set for the environment variable
 * Return: 1 on success, 0 on failure
 */
int set_env_var(list_t **env, const char *var, const char *value)
{
	char *new_var;
	list_t *current;

	if (env == NULL || var == NULL || value == NULL)
		return 0;

	new_var = malloc(strlen(var) + strlen(value) + 2);
	if (new_var == NULL)
		return 0;

	sprintf(new_var, "%s=%s", var, value);

	current = *env;
	while (current != NULL)
	{
		if (starts_with(current->str, var) == current->str)
		{
			free(current->str);
			current->str = new_var;
			return 1;
		}
		current = current->next;
	}

	if (add_node_end(env, new_var) == NULL)
	{
		free(new_var);
		return 0;
	}

	return 1;
}
