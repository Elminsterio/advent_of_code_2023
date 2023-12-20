#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Game {
    char cards[6];
    int bid;
	int score;
};

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

void swap(struct Game *a, struct Game *b)
{
    struct Game temp = *a;
    *a = *b;
    *b = temp;
}

void order_games(struct Game arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].score > arr[j + 1].score) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int get_score(char cards[6])
{
	char card_types[14] = "AKQJT98765432";
	int score[13];
	int final_score;
	int i;
	int j;

	i = 0;
	while (card_types[i])
	{
		score[i] = 0;
		j = 0;
		while(cards[j])
		{
			if(cards[j] == card_types[i])
				score[i]++;
			j++;
		}
		i++;
	}
	i = 0;
	final_score = 1;
	while (i < 13)
	{
		if (1 < score[i])
			final_score += score[i] * (i + 1);
		i++;
	}
	return (final_score);
}

void get_all_games(char *line, struct Game *game)
{
	int i;
	int j;
	char str_num[5];

	i = 0;
	while (line[i] != ' ')
	{
		game->cards[i] = line[i];
		i++;
	}
	game->cards[i] = '\0';
	j = 0;
	while (line[i])
		str_num[j++] = line[i++];
	str_num[j] = '\0';
	game->bid = atoi(str_num);
	game->score = get_score(game->cards);
	clear_char_arr(str_num);
}

int main(void)
{
	int fd;
	int i;
	char buff[400];
  	struct Game games[1002];

	fd = open_text();
	if (fd == -1)
		return (0);
	i = 0;
	while (read_line(fd, buff) > 0)
	{
		get_all_games(buff, &games[i]);
		i++;
	}
	order_games(games, 1000);
	i = 0;
	while (i < 1000)
	{
        printf("Cards: %s, Bid: %d, Score: %d\n", games[i].cards, games[i].bid, games[i].score);
		i++;
	}
	close(fd);
	return (0);
}