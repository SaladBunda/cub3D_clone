/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:17:29 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/04 19:59:31 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ext_test(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	i--;
	if (filename[i] == 'b')
	{
		i--;
		if (filename[i] == 'u')
		{
			i--;
			if (filename[i] == 'c')
			{
				i--;
				if (filename[i] == '.')
					return (1);
			}
		}
	}
	return (0);
}

int file_existance(char *filename)
{
	int fd;
	fd = open(filename, O_RDONLY);
	if(fd == -1)
		return 1;
	else
	{
		close(fd);
		return 0;
	}
}

int copy_file(char *filename, t_data *data)
{
	int fd;
	(void) data;
	char *line;
	fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		printf("couldnt open file\n");
		exit(1);	
	}
	int i = 0;
	while(1)
	{
		line = get_next_line(fd);
		if(!line) 
			break;
		i++;
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		printf("couldnt open file\n");
		exit(1);	
	}
	data->file = malloc(sizeof(char *) * (i + 1));
	if(!data->file)
		return 1;
	int j = 0;
	while(j < i)
	{
		data->file[j] = get_next_line(fd);
		j++;
	}
	data->file[j] = NULL;
	return 0;
}

int test_floor_ceiling(char **line, char *flag,t_map_data *x)
{
	(void) line;
	if(ft_fcmp(flag,"F")== 0)
	{
		x->floor.str = ft_strdup(line[1]);
		x->floor.count++;
	}
	if(ft_fcmp(flag,"C")== 0)
	{
		x->ceiling.str = ft_strdup(line[1]);
		x->ceiling.count++;
	}
	if(ft_fcmp(flag,"NO")== 0)
	{
		x->no.str = ft_strdup(line[1]);
		x->no.count++;
	}
	if(ft_fcmp(flag,"SO")== 0)
	{
		x->so.str = ft_strdup(line[1]);
		x->so.count++;
	}
	if(ft_fcmp(flag,"WE")== 0)
	{
		x->we.str = ft_strdup(line[1]);
		x->we.count++;
	}
	if(ft_fcmp(flag,"EA")== 0)
	{
		x->ea.str = ft_strdup(line[1]);
		x->ea.count++;
		
	}
	printf("inside testfloorceiling that fills paths for textures:%s\n", line[1]);
	return 0;
}
int test_colors(char **line, char *flag, t_map_data *x)
{
	(void)x;
	char **args;
	int i = 0;
	int error = 0;
	int num;
	if(ft_fcmp(flag, "F") == 0 || ft_fcmp(flag, "C") == 0)
	{
		args = ft_split(line[1],',');
		while(args[i])
			i++;
		if(i == 3)
		{
			i = 0;
			while(args[i])
			{
				num = ft_atoi(args[i], &error);
				if(error != 0)
					return 1;
				if(num < 0 || num > 255)
					return 1;
				if(ft_fcmp(flag, "F") == 0)
					x->fcolor[i] = num;
				else if(ft_fcmp(flag, "C") == 0)
					x->ccolor[i] = num;
				i++;
			}
		}
		else
		{
			printf("invalid argument for F/C\n");
			return 1;
		}
	}
	return 0;
}

int open_textures(char **line, char *flag, t_map_data *x)
{
	(void) x;
	int fd;
	if(ft_fcmp(flag, "NO") == 0 || ft_fcmp(flag, "SO") == 0 || ft_fcmp(flag, "WE") == 0 || ft_fcmp(flag, "EA") == 0)
	{
		fd = open(line[1], O_RDONLY);
		if(fd == -1)
		{
			printf("invalid texture file\n");
			return 1;
		}
	}
	return 0;
}

int test_line(char **line, t_map_data *x,int *state)
{
	(void) x;
	int i = 0;
	while(line[i])
		i++;
	if(ft_fcmp(line[0], "F") == 0 || ft_fcmp(line[0],"C") == 0 || ft_fcmp(line[0],"NO") == 0|| ft_fcmp(line[0],"SO") == 0|| ft_fcmp(line[0],"EA") == 0|| ft_fcmp(line[0],"WE") == 0)
	{
		printf("line[0]:%s\n",line[0]);
		if(i != 2)
			return (*state = 3, printf("wrong parameters\n"),1);
		else
		{
			printf("else\n");
			test_floor_ceiling(line, line[0], x);
			if(test_colors(line,line[0],x) == 1)
			{
				printf("failed test colors\n");
				return (*state = 1,1);
			}
			if(open_textures(line,line[0],x) == 1)
			{
				printf("failed opening textures\n");
				return (*state = 1, 1);
			}
			return 0;
		}
	}
	else
		return 1;	
	
}

void free_2d(char **arr)
{
	int i = 0;
	while(arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}

int test_characters(char **map, t_map_data *x)
{
	(void)x;
	int i = 0;
	int count = 0;
	int j;
	while(map[i])
	{
		j = 0;
		while(map[i][j] && map[i][j] != '\n')
		{
			if(map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W')
				count++;
			else if(map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ')
				return 1;
			j++;
		}
		i++;
	}
	if(count != 1)
		return 1;
	return 0;
}

int test_textures(t_data *data, int *index, t_map_data *x)
{
	char **line;
	// t_map_data x;
	// x.ceiling.str = NULL;
	// x.ceiling.count = 0;
	// x.floor.str = NULL;
	// x.floor.count = 0;
	// x.ea.str = NULL;
	// x.no.str = NULL;
	// x.we.str = NULL;
	// x.so.str = NULL;
	// x.ea.count = 0;
	// x.no.count = 0;
	// x.we.count = 0;
	// x.so.count = 0;
	int state = 0;
	int i  = 0;
	while(data->file[i])
	{
		if(ft_fcmp(data->file[i],"") == 0)
		{
			i++;
			continue ;
		}
		line = ft_split(data->file[i],' ');
		if(test_line(line, x,&state) == 1)
		{
			free_2d(line);
			break ;
		}
		free_2d(line);
		i++;
	}
	if(!x->ceiling.str || !x->floor.str || !x->no.str || !x->so.str || !x->we.str || !x->ea.str)
		return (printf("invalid file map\n"), 1);
	if(state > 0)
		return(printf("failed tests:%d\n",state), 1);
	if(x->ceiling.count != 1 || x->floor.count != 1 || x->no.count != 1 || x->so.count != 1 || x->we.count != 1 || x->ea.count != 1)
		return (printf("duplicate data\n"), 1);
	if(test_characters(data->file + i, x) == 1)
		return(printf("bad map\n"), 1);
	*index = i;
	return 0;
	
	
}
int copy_map(t_data *data, int i)
{
	int j = 0;
	while(data->file[i])
	{
		j = 0;
		while(data->file[i][j])
		{
			if(data->file[i][j] == ' ')
				j++;
			else
				break;
		}
		if(data->file[i][j] =='\0')
			i++;
		else
			break ;
	}
	int count = 0;
	j = i;
	while(data->file[i])
	{
		count++;
		i++;	
	}
	data->map = malloc(sizeof(char *) * (count +1));
	int l = 0;
	while(data->file[j])
	{
		data->map[l++] = ft_strdup(data->file[j]);
		j++;
	}
	data->map[l] = NULL;
	data->h_map = l;
	int max;
	max = 0;
	i =0;
	while(data->map[i])
	{
		if(ft_strlen(data->map[i]) > max)
			max = ft_strlen(data->map[i]);
		i++;
	}
	data->w_map = max;
	
	return 0;
}

void flood_fill(t_data *data, char ***copy,int x, int y, int *error)
{
	if(x > data->w_map  || x < 0 || y > data->h_map || y < 0)
		return ;
	else if(x == data->w_map - 1 || x == 0 || y == data->h_map - 1 || y == 0)
	{
		if((*copy)[y][x] == ' ' || (*copy)[y][x] == '0')
			*error = 1;
		return ;
	}
	if((*copy)[y][x] == '1')
		return ;
	if((*copy)[y][x] == ' ' || (*copy)[y][x] == '\0')
	{
		*error = 1;
		return ;
	}
	(*copy)[y][x] = '1';
	flood_fill(data,copy,x + 1,y,error);
	flood_fill(data,copy,x - 1,y,error);
	flood_fill(data, copy,x,y + 1,error);
	flood_fill(data, copy,x,y - 1,error);
}

int another_function(char **copy, int *error, int height)
{
	int i = 0;
	int j;
	int line_len;
	while(copy[i])
	{
		j = 0;
		line_len = ft_strlen(copy[i]);
		while(copy[i][j])
		{
			if(copy[i][j] == ' ')
			{
				if(i > 0 && i < height - 1)
				{
					if(j == 0)
					{
						if(copy[i - 1][j] == '0')
							return(*error = 1, 1);
						else if(copy[i + 1][j] == '0')
							return(*error = 1, 1);
						else if(copy[i][j + 1] == '0')
							return(*error = 1, 1);	
					}
					else if(j == line_len)
					{
						if(copy[i - 1][j] == '0')
							return(*error = 1, 1);
						else if(copy[i + 1][j] == '0')
							return(*error = 1, 1);
						else if(copy[i][j - 1] == '0')
							return(*error = 1, 1);	
					}
					else
					{
						if(copy[i - 1][j] == '0')
							return(*error = 1, 1);
						else if(copy[i + 1][j] == '0')
							return(*error = 1, 1);
						else if(copy[i][j + 1] == '0')
							return(*error = 1, 1);	
						else if(copy[i][j - 1] == '0')
							return(*error = 1, 1);	
					}
				}
				else if(i == 0)
				{
					if(j == 0)
					{
						if(copy[i + 1][j] == '0')
							return(*error = 1, 1);
						else if(copy[i][j + 1] == '0')
							return(*error = 1, 1);	
					}
					else if(j == line_len)
					{
						if(copy[i + 1][j] == '0')
							return(*error = 1, 1);
						else if(copy[i][j - 1] == '0')
							return(*error = 1, 1);	
					}
					else
					{
						if(copy[i + 1][j] == '0')
							return(*error = 1, 1);
						else if(copy[i][j + 1] == '0')
							return(*error = 1, 1);	
						else if(copy[i][j - 1] == '0')
							return(*error = 1, 1);	
					}
				}
				else
				{
					if(j == 0)
					{
						if(copy[i - 1][j] == '0')
							return(*error = 1, 1);
						else if(copy[i][j + 1] == '0')
							return(*error = 1, 1);	
					}
					else if(j == line_len)
					{
						if(copy[i - 1][j] == '0')
							return(*error = 1, 1);
						else if(copy[i][j - 1] == '0')
							return(*error = 1, 1);	
					}
					else
					{
						if(copy[i - 1][j] == '0')
							return(*error = 1, 1);
						else if(copy[i][j + 1] == '0')
							return(*error = 1, 1);	
						else if(copy[i][j - 1] == '0')
							return(*error = 1, 1);	
					}
				}
			}
			j++;
		}
		i++;
	}
	return 0;
}

int parsing_test(t_data *data)
{
	int i = 0;
	char **copy;
	int j;
	int error = 0;
	while(data->map[i])
	{
		j = 0;
		while(data->map[i][j])
		{
			if(data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W')
				(data->p_x = j, data->p_y = i);
			j++;
		}
		i++;
	}
	copy = malloc(sizeof(char *) * (data->h_map + 1));
	
	i = 0;
	while(i < data->h_map)
	{
		copy[i] = ft_strdup(data->map[i]);
		i++;
	}
	copy[i] = NULL;
	i = 0;
	while(copy[i])
	{
		j = 0;
		while(copy[i][j] && copy[i][j] == ' ')
			j++;
		if(copy[i][j] == '\0')
			return (printf("found empty line\n"),1);
		i++;
	}
	flood_fill(data, &copy, data->p_x,data->p_y,&error);
	i = 0;
	printf("--------------------------------\n");
	if(another_function(copy,&error, data->h_map) == 1)
		return(printf("fucked up map\n"),1);
	while(copy[i])
	{
		printf("%s\n",copy[i]);
		i++;
	}
	if(error == 1)
		return(printf("found space in map\n"),1);
	return 0;
}

int test_map_validity(char *filename, t_data *data, t_map_data *x)
{
	int i =0;
	if(ext_test(filename) == 0)
	{
		printf("failed in file extension\n");
		return 1;
	}
	if(file_existance(filename) == 1)
	{
		printf("failed in opening file\n");
		return 1;
	}
	copy_file(filename, data);
	if(test_textures(data, &i, x) == 1)
	{
		printf("texrure test\n");
		return 1;
	}
	copy_map(data, i);
	if(parsing_test(data) == 1)
		return 1;
	return 0;
}