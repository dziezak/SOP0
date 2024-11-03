#define _GNU_SOURCE
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <ftw.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

ssize_t bulk_read(int fd, char *buf, size_t count)
{
    ssize_t c;
    ssize_t len = 0;
    do
    {
        c = TEMP_FAILURE_RETRY(read(fd, buf, count));
        if (c < 0)
            return c;
        if (c == 0)
            return len;  // EOF
        buf += c;
        len += c;
        count -= c;
    } while (count > 0);
    return len;
}

ssize_t bulk_write(int fd, char *buf, size_t count)
{
    ssize_t c;
    ssize_t len = 0;
    do
    {
        c = TEMP_FAILURE_RETRY(write(fd, buf, count));
        if (c < 0)
            return c;
        buf += c;
        len += c;
        count -= c;
    } while (count > 0);
    return len;
}

void show_stage2(const char *const path, const struct stat *const stat_buf) {
	/*char *line = NULL;
	size_t line_size = 0;
	ssize_t line_len1;//= getline(&line, &line_size, stdin);	
	line_size = 0;
	struct stat buf;
	*/



}

void write_stage3(const char *const path, const struct stat *const stat_buf) {}

void walk_stage4(const char *const path, const struct stat *const stat_buf) {}


int interface_stage1() 
{
	printf("1. show \n2. write\n3. walk\n4.exit\n");
	char *buffer = NULL;
	size_t buf_size = 0;
	ssize_t str_len = getline(&buffer, &buf_size, stdin);
	
	if(str_len == -1) ERR("getline");
	buffer[str_len-1] = '\0';

	char *line = NULL;
	size_t line_size = 0;
	ssize_t line_len1;//= getline(&line, &line_size, stdin);	
	line_size = 0;
	struct stat buf;
	char end = '5';
	if(str_len > 2 ) buffer = &end;
	switch(buffer[0])
	{
		case '1':
	       		line_len1 = getline(&line, &line_size, stdin);
			line[line_len1-1] = '\0';
			if(stat(line, &buf) == 0){
				free(line);
				free(buffer);
			       	printf("Good path\n");
				return 1;
			}
			else printf("Bad path\n");
			free(line);
			free(buffer);
			break;
		case '2':
	       		line_len1 = getline(&line, &line_size, stdin);
			line[line_len1-1] = '\0';
			if(stat(line, &buf) == 0){
			       	printf("Good path\n");
				free(line);
				free(buffer);
				return 1;
			}
			else printf("Bad path\n");
			free(line);
			free(buffer);
			break;
		case '3':
	       		line_len1 = getline(&line, &line_size, stdin);
			line[line_len1-1] = '\0';
			if(stat(line, &buf) == 0){
			       	printf("Good path\n");
				free(line);
				free(buffer);
				return 1;
			}
			else printf("Bad path\n");
			free(line);
			free(buffer);
			break;
		case '4':
			free(buffer);
			return 0;
			break;
		default:
		free(buffer);
		printf("Niepoprawne wejscie%s\n", line);
		return 1;
	}
	return 1;
}

int main()
{
    while (interface_stage1())
        ;
    return EXIT_SUCCESS;
}
