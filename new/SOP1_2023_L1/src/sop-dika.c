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
#include <stdbool.h>

#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))
#define BUFFER_SIZE 1024

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
	if(S_ISREG(stat_buf->st_mode)){

		printf("Plik %s\n", path);
		printf("Rozmiar pliku: %ld bajtow\n", stat_buf->st_size);
		FILE *file = fopen(path, "r");
		if( file == NULL ) {
			perror("Nie mozna otworzyc pliku");
			return;
		}

		char ch;
		while ((ch = fgetc(file)) != EOF){
			putchar(ch);
		}
		fclose(file);

	}else if( S_ISDIR(stat_buf->st_mode)){
		printf("Katalog: %s\n", path);
		DIR *dir = opendir(path);
		if( dir == NULL ){
			perror("Nie mozna otworzyc katalogu");
			return;
		}

		struct dirent *entry;
		printf("Zawartosc katalogu:\n");
		while((entry = readdir(dir)) != NULL){
			if(entry -> d_name[0] != '.'){
				printf(" %s\n", entry -> d_name);
			}
		}
		closedir(dir);
	}else{
		printf("Plik: %s jest innego typu (nieznany typ).\n", path);
	}
}

void write_stage3(const char *const path, const struct stat *const stat_buf) {
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;
	int fd = open(path, O_RDONLY);
	if(fd < 0){
		perror("Blad otwierania pliku do odczytu");
		return;
	}

	printf("Obecna zawartosc pliku '%s': \n", path);
	while((bytes_read = bulk_read(fd, buffer, sizeof(buffer))) > 0){
		if(bulk_write(STDOUT_FILENO, buffer, bytes_read) < 0){
			perror("Blad wyswietlenia zawartosci pliku");
			close(fd);
			return;
		}
	}
	if(bytes_read < 0){
		perror("Blad odczytu zawartosci pliku");
		close(fd);
		return;
	}
	close(fd);
	fd = open(path, O_WRONLY |O_APPEND);
	if(fd < 0){
		perror("Blad otwierania pliku do odpisywania");
		return;
	}

	printf("\nWpisz nowe linie ( pusta linia konczy dopisywanie):\n");
	while(true){
		if(fgets(buffer, sizeof(buffer), stdin) == NULL){
			perror("Blad odczytu z stdin");
			break;
		}
		if(strcmp(buffer, "\n") == 0){
			break;
		}
		if(bulk_write(fd, buffer, strlen(buffer)) < 0){
			perror("Blad odpisywania do pliku");
			break;
		}
	}
	close(fd);
}

void walk_stage4(const char *const path, const struct stat *const stat_buf) {

}


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
				show_stage2(line, &buf);
				free(line);
				free(buffer);
			       	printf("Good path\n");
				return 1;
			}
			else printf("Bad path\n");
			break;
		case '2':
	       		line_len1 = getline(&line, &line_size, stdin);
			line[line_len1-1] = '\0';
			if(stat(line, &buf) == 0){
				write_stage3(line, &buf);
			       	printf("Good path\n");
				free(line);
				free(buffer);
				return 1;
			}
			else printf("Bad path\n");
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
	free(line);
	free(buffer);
	return 1;
}

int main()
{
    while (interface_stage1())
        ;
    return EXIT_SUCCESS;
}
