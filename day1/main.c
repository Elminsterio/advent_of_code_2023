#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int open_text(void)
{
	int fd;

	if ((fd = open("D:\\Descargas\\input.txt", O_RDONLY)) == -1)
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

int locate_l_number_lt(char *line, char *number)
{
	int i;
	int j;
	int loc;
	int pos;

	i = 0;
	loc = 0;
	pos = 0;
	while (line[i])
	{
		j = 0;
		while (number[j])
		{
			if (number[j] == line[i + j])
				loc = 1;
			else
			{
				loc = 0;
				break ;
			}
			j++;
		}
		if (loc)
		{
			pos = i + j;
			i += j;
		}
		else
			i++;
	}
	return (pos);
}

int locate_l_number_st(char *line, char *number)
{
	int i;
	int j;
	int loc;

	i = 0;
	loc = 0;
	while (line[i])
	{
		j = 0;
		while (number[j])
		{
			if (number[j] == line[i + j])
				loc = 1;
			else
			{
				loc = 0;
				break ;
			}
			j++;
		}
		if (loc)
			return (i + j);
		i++;
	}
	return (0);
}

char get_lt_number(char *line, char numbers[9][6])
{
	int i;
	int j;
	int num;
	int pos;
	int tmp;

	i = 0;
	num = 0;
	pos = 0;
	while (i < 9)
	{
		tmp = locate_l_number_lt(line, numbers[i]);
		if (tmp && tmp > pos)
		{
			pos = tmp;
			num = i + 1;
		}
		i++;
	}
	i = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9' && i + 1 > pos)
		{
			pos = i + 1;
			num = line[i] - 48;
		}
		i++;
	}
	return (num + 48);
}

char get_st_number(char *line, char numbers[9][6])
{
	int i;
	int j;
	int num;
	int pos;
	int tmp;

	i = 0;
	num = 0;
	pos = 100;
	while (i < 9)
	{
		tmp = locate_l_number_st(line, numbers[i]);
		if (tmp && tmp < pos)
		{
			pos = tmp;
			num = i + 1;
		}
		i++;
	}
	i = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9' && i + 1 < pos)
		{
			pos = i + 1;
			num = line[i] - 48;
		}
		i++;
	}
	return (num + 48);
}

int main(void)
{
	int fd;
	int sum;
	char num[3];
	char nums[9][6] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	char buff[100];

	fd = open_text();
	if (fd == -1)
		return (0);
	sum = 0;
	while (read_line(fd, buff) > 0)
	{
		num[0] = get_st_number(buff, nums);
		num[1] = get_lt_number(buff, nums);
		num[2] = '\0';
		sum += atoi(num);
		printf("El num es: %s, La string es: %s y la suma es: %d\n", num, buff, sum);
	}
	close(fd);
	return (0);
}