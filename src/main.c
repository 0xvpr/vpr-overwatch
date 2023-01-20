#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define ever ;;

static uint32_t frequency_us = 100;
static int32_t  command_rv;

static time_t   last_edited_time;
static struct   stat file_stat;

static char     filename[256];
static char     command[256];
static int      verbose;

void __attribute__((noreturn)) __usage(const char* const restrict msg, int code)
{
    (void)msg;
    exit(code);
}

void parse_args(int argc, char** restrict argv)
{
    int i = 1;
    while (i < argc)
    {
        switch (argv[i][0])
        {
            case '-':
            {
                switch (argv[i][1])
                {
                    case 'c':
                    {
                        if (argv[i][2])
                        {
                            snprintf(command, sizeof(command), "%s", argv[i]+2);
                        }
                        else
                        {
                            snprintf(command, sizeof(command), "%s", argv[i+1]);
                        }
                        command[255] = 0;
                        break;
                    }
                    case 'f':
                    {
                        if (argv[i][2])
                        {
                            snprintf(filename, sizeof(filename), "%s", argv[i]+2);
                        }
                        else
                        {
                            snprintf(filename, sizeof(filename), "%s", argv[i+1]);
                        }
                        command[255] = 0;
                        break;
                    }
                    case 't':
                    {
                        sscanf(optarg, "%u", &frequency_us);
                        break;
                    }
                    case 'v':
                    {
                        verbose = 1;
                        break;
                    }
                }
            }
        }
        ++i;
    }
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        __usage("Positional arguments required.", 1);
    }

    parse_args(argc, argv);

    if (stat(filename, &file_stat) == -1)
    {
        perror("stat");
        fprintf(stderr, "filename: %s\n", filename); // TODO
        return errno;
    }

    last_edited_time = file_stat.st_mtime;
    //printf("Last modification: %s", ctime(&file_stat.st_mtime)); //TODO: if verbose

    if ((command_rv = system(command)))
    {
        // TODO status message
        return command_rv;
    }

    for (ever)
    {
        time_t start_time = time(NULL);
        if (stat(filename, &file_stat) == -1)
        {
            if (errno == ENOENT)
            {
                break;
            }

            perror("stat");
            fprintf(stderr, "filename: %s\n", filename); // TODO
            return errno;
        }

        if (last_edited_time < file_stat.st_mtime)
        {
            last_edited_time = file_stat.st_mtime;
            //printf("Last modification: %s", ctime(&file_stat.st_mtime)); //TODO: if verbose
            if ((command_rv = system(command)))
            {
                return command_rv;
            }
        }
        time_t elapsed_time = time(NULL) - start_time;
        usleep((frequency_us - elapsed_time) & INT32_MAX);
    }

    return 0;
}
