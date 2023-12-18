#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int open_text(void)
{
	int fd;

	if ((fd = open("./input.txt", O_RDONLY)) == -1)
	{
		printf("Error! opening file");
		return (-1);
	}
	return (fd);
}

int read_line(int fd, char *buff)
{
	int i;
	char c;

	i = 0;
    while (read(fd, &c, 1) == 1 && c != '\n')
        buff[i++] = c;
	if (c == '\n')
        buff[i] = '\0';
	return (i);
}

int skip_colon(char *line)
{
	int i;

	i = 0;
	while (line[i] != ':')
		i++;
	return (++i);
}

int get_color_value(char *buff_game, char *cube)
{
	int i;
	int j;
	int num;
	int loc;

	i = 0;
	j = 0;
	loc = 0;
	while (buff_game[i])
	{
		j = 0;
		while (cube[j] && buff_game[i + j])
		{
			if (cube[j] == buff_game[i + j])
				loc = 1;
			else
			{
				loc = 0;
				break ;
			}
			j++;
		}
		if (loc)
			break ;
		i++;
	}
	if (!i)
		return (0);
	i -= 2;
	while (buff_game[i] >= '0' && buff_game[i] <= '9' && i != 0)
		i--;

	printf("El dígito es: %s", buff_game);
	return (atoi((buff_game + i)));
}

int get_next_game(char *game, int *game_values)
{
	int j;
	int num;
	char cubes[4][6] = {"red", "green", "blue"};

	j = 0;
	num = 0;
	while (j < 3)
	{
		num = get_color_value(game, cubes[j]);
		printf("El cubo analizado es: %s. El numero es: %d\n", cubes[j], num);
		if(num > game_values[j])
			game_values[j] = num;
		j++;
	}
	return (1);
}

int get_all_games(char *line)
{
	int i;
	int j;
	char game[150];
	// red, green, blue
	int game_values[3] = {0, 0, 0};

	i = skip_colon(line);
	while (line[i])
	{
		j = 0;
		while (line[i + j] != ';' && line[i + j])
		{
			game[j] = line[i + j];
			j++;
		}
		game[j] = '\0';
		printf("El game es: %s\n", line + i);
		if(!get_next_game(game, game_values))
			return (0);
		if(!line[j + i])
		{
			printf("red %d, green %d, blue %d\n", game_values[0], game_values[1], game_values[2]);
			return (game_values[0] * game_values[1] * game_values[2]);
		}
		i = j + i + 1;
	}
}

int main(void)
{
	int fd;
	int sum;
	int i;
	char buff[200];

	fd = open_text();
	if (fd == -1)
		return (0);
	sum = 0;
	i = 1;
	while (read_line(fd, buff) > 0)
	{
		printf("La linea es: %s\n\n", buff);
		sum += get_all_games(buff);
		i++;
	}
	printf("\nLa cantidad total es: %d\n", sum);
	close(fd);
	return (0);
}