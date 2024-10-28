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

void show_stage2(const char *const path, const struct stat *const stat_buf) {}

void write_stage3(const char *const path, const struct stat *const stat_buf) {}

void walk_stage4(const char *const path, const struct stat *const stat_buf) {}

if(str_len == -1) ERR("getline");
        buffer[str_len-1] = '\0';
        free(buffer);


int interface_stage1() 
{
	printf("1. show \n2. write\n3. walk\n4.exit\n");
	char *buffer = NULL;
	size_t buf_size = 0;
	ssize_t str_len = getline(&buffer, &buf_size, stdin);
	
	//printf("znak: %s\n", buffer);

	if(str_len == -1) ERR("getline");
	buffer[str_len-1] = '\0';
	free(buffer);


	char *line = NULL;
	size_t line_size = 0;
	ssize_t str_len1 = getline(&line, &line_size, stdin);	
	switch(buffer)
	{
		case 1:
	       		str_len1 = getline(&line, &line_size, stdin);
			break;
		case 2:
	       		str_len1 = getline(&line, &line_size, stdin);	
			break;
		case 3:
	       		str_len1 = getline(&line, &line_size, stdin);	
			break;
		case 4:
	       		str_len1 = getline(&line, &line_size, stdin);	
			break;
		default:
		printf("Niepoprawne wejscie\n");
	}
}

int main()
{
    while (interface_stage1())
        ;
    return EXIT_SUCCESS;
}
