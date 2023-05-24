#include "shell.h"

/**
 * exit_shell - Exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Exits with a given exit status
 * (0) if info->argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
	int exit_status;

	if (info->argv[1]) /* Check if there is an exit argument */
	{
		exit_status = string_to_int(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			print_string(info->argv[1]);
			print_character('\n');
			return 1;
		}
		info->error_number = string_to_int(info->argv[1]);
		return -2;
	}

	info->error_number = -1;
	return -2;
}

/**
 * change_directory - Changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int change_directory(info_t *info)
{
	char *current_path, *directory, buffer[1024];
	int chdir_ret;

	current_path = get_current_directory(buffer, 1024);
	if (!current_path)
		print_string("TODO: >>get_current_directory failure emsg here<<\n");

	if (!info->argv[1])
	{
		directory = get_environment_variable(info, "HOME=");
		if (!directory)
			chdir_ret = /* TODO: What should this be? */
				change_directory((directory = get_environment_variable(info, "PWD=")) ? directory : "/");
		else
			chdir_ret = change_directory(directory);
	}
	else if (compare_strings(info->argv[1], "-") == 0)
	{
		if (!get_environment_variable(info, "OLDPWD="))
		{
			print_string(current_path);
			print_character('\n');
			return 1;
		}
		print_string(get_environment_variable(info, "OLDPWD="));
		print_character('\n');
		chdir_ret = /* TODO: What should this be? */
			change_directory((directory = get_environment_variable(info, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_ret = change_directory(info->argv[1]);

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		print_string(info->argv[1]);
		print_character('\n');
	}
	else
	{
		set_environment_variable(info, "OLDPWD", get_environment_variable(info, "PWD="));
		set_environment_variable(info, "PWD", get_current_directory(buffer, 1024));
	}

	return 0;
}

/**
 * display_help - Displays help information
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int display_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	print_string("help call works. Function not yet implemented \n");
	if (0)
		print_string(*arg_array); /* Temporary workaround to avoid unused variable warning */
	return 0;
}

