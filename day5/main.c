#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 300
#define NUM_CATEGORIES 60

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

void clear_char_arr(char *arr)
{
	int i;

	i = 0;
	while (arr[i])
		arr[i++] = '\0';
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

void clean_int_arr2(unsigned int long long category[][8], int start)
{
	int i;

	while (start < 20)
	{
		i = 0;
		while (i < 9)
			category[start][i++] = 0;
		start++;
	}
}

int skip_to_next_category(char *line)
{
	int i;

	i = 0;
	while (line[i] < '0' || line[i] > '9')
		i++;
	return (--i);
}

void category_to_arr(unsigned int long long category[][3], unsigned int long long *seed, int category_num)
{
	int i;

	i = 0;
	while (i < 60)
	{
		if (category[i][0] == 0 && category[i][1] == 0 && category[i][2] == 0)
			break ;
		//printf("%d\n", i);
		if (
			seed[category_num - 1] <= (category[i][1] + (category[i][2] - 1)) && 
			seed[category_num - 1] >= category[i][1]
		)
		{
			printf("Destination: %I64u.\n Source: %I64u.\n Length: %I64u.\n", category[i][0], category[i][1], category[i][2]);
			seed[category_num] = category[i][0] + (seed[category_num - 1] - category[i][1]);
			break ;
		}
		i++;
	}
	printf("La categoría es: %d.\n La seed inicial es: %I64u.\n El número nuevo es: %I64u.\n", category_num, seed[category_num - 1], seed[category_num]);
	if(!seed[category_num])
		seed[category_num] = seed[category_num - 1];
}

int get_all_seeds(char *line, unsigned int long long seeds[][8])
{
	int i;
	int j;
	int num;
	char str_num[30];

	num = 0;
	i = skip_to_next_category(line);
	while (line[i])
	{
		if (line[i] == ' ')
		{
			i++;
			continue;
		}
		j = 0;
		while (line[i + j] >= '0' && line[i + j] <= '9')
		{
			str_num[j] = line[i + j];
			j++;
		}
		str_num[j] = '\0';
		seeds[num][0] = atoll(str_num);
		printf("La seed inicial inicial es: %I64u\n", seeds[num][0]);
		clear_char_arr(str_num);
		num++;
		i += j;
	}
	return (i);
}

unsigned int long long get_closest_location(unsigned int long long seeds[20][8])
{
	int i;
	unsigned int long long loc;

	i = 0;
	loc = seeds[i][7];
	while (i < 20)
	{
		if(seeds[i][7] < loc)
			loc = seeds[i][7];
		i++;
	}
	return (loc);
}

void process_category(int fd, char *buff, unsigned int long long category[][3])
{
	char str_num[40];
	int i;
	int j;
	int z;
	int counter;

	counter = 0;
	while (read_line(fd, buff) > 0)
	{
		if(!buff[0])
			continue ;
		if(buff[0] >= 'a' && buff[0] <= 'z')
			break ;
		i = 0;
		z = 0;
		while (z < 3)
		{
			j = 0;
			if(buff[i + j] == ' ')
			{
				i++;
				continue ;
			}
			while (buff[i + j] >= '0' && buff[i + j] <= '9')
			{
				str_num[j] = buff[i + j];
				j++;
			}
			str_num[j] = '\0';
			category[counter][z] = atoll(str_num);
			clean_int_arr(category, counter + 1);
			clear_char_arr(str_num);
			i += j;
			z++;
		}
		counter++;
	}
	return ;
}

int main(void)
{
	int fd;
	int i;
	int j;
	char buff[400];
	unsigned int long long seeds[20][8];
	unsigned int long long category[60][3];

	fd = open_text();
	if (fd == -1)
		return (0);
	read_line(fd, buff);
	clean_int_arr2(seeds, 0);
	get_all_seeds(buff, seeds);
	read_line(fd, buff);
	i = 0;
	while (i < 7)
	{
		read_line(fd, buff);
		process_category(fd, buff, category);
		j = 0;
		while (j < 20)
		{
			category_to_arr(category, seeds[j], i + 1);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("La localización más cercana es: %I64u", get_closest_location(seeds));
	close(fd);
	return (0);
}