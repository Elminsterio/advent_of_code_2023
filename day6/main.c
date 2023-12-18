#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
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
	buff[i] = '\0';
	return (i);
}

void clean_int_arr(unsigned int long long category[][3], int start)
{
	int i;

	while (start < 60)
	{
		i = 0;
		while (i < 3)
			category[start][i++] = 0;
		start++;
	}
}

void clear_char_arr(char *arr)
{
	int i;

	i = 0;
	while (arr[i])
		arr[i++] = '\0';
}

int skip_colon(char *line)
{
	int i;

	i = 0;
	while (line[i] != ':')
		i++;
	return (++i);
}

void get_distance_or_time(char *line, unsigned int races[5][3], int time_or_dist)
{
	int i;
	int j;
	int num;
	char str_num[5];
	i = skip_colon(line);
	num = 0;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			i++;
			continue ;
		}
		j = 0;
		while (line[i + j] >= '0' && line[i + j] <= '9')
		{
			str_num[j] = line[i + j];
			j++;
		}
		races[num][time_or_dist] = atoi(str_num);
		clear_char_arr(str_num);
		num++;
		i += j;
	}
	return ;
}

int get_ways_to_win(unsigned int race[3])
{
	int race_time;
	int dist_rec;
	int counter;
	int i;

	i = 0;
	counter = 0;
	race_time = race[0];
	dist_rec = race[1];
	while (i <= race_time)
	{
		if(((race_time - i) * i) > dist_rec)
			counter++;
		i++;
	}
	race[2] = dist_rec;
	return (counter);
}

int main(void)
{
	int fd;
	int i;
	int mult;
	char buff[400];
	unsigned int races[5][3];

	fd = open_text();
	if (fd == -1)
		return (0);
	read_line(fd, buff);
	get_distance_or_time(buff, races, 0);
	read_line(fd, buff);
	get_distance_or_time(buff, races, 1);

	i = 0;
	mult = 1;
	while (i < 4)
	{
		mult *= get_ways_to_win(races[i]);
		printf("El mejor tiempo en la carrera %d es: %d\nLa cantidad de formas diferentes de ganar son: %d\n", races[i][0], races[i][2], get_best_race(races[i]));
		i++;
	}
	printf("El resultado final es: %d\n", mult);
	close(fd);
	return (0);
}