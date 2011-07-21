/* skeinsum.c -- command-line driver for skein.
   Copyright (C) 2011 Casey Marshall. */
   

#include <getopt.h>
#include <stdlib.h>
#include <skeinApi.h>

#define SKEINSUM_VERSION "0.0.1"

#define OPT_HELP    256
#define OPT_VERSION 257
#define OPT_QUIET   258
#define OPT_STATUS  259

void show_help(void);
void show_version(void);       

static const char *progname = "skeinsum";

int main(int argc, char * const * argv)
{
    int c;
    const char *optstring = "abcltw";
    const struct option longopts[] = {
        { "algorithm", required_argument, NULL, 'a' },
        { "alg", required_argument, NULL, 'a' },
        { "length", required_argument, NULL, 'l' },
        { "len", required_argument, NULL, 'l' },
        { "binary", no_argument, NULL, 'b' },
        { "check", no_argument, NULL, 'c' },
        { "text", no_argument, NULL, 't' },
        { "quiet", no_argument, NULL, OPT_QUIET },
        { "status", no_argument, NULL, OPT_STATUS },
        { "warn", no_argument, NULL, 'w' },
        { "help", no_argument, NULL, OPT_HELP },
        { "version", no_argument, NULL, OPT_VERSION },
        { NULL, 0, NULL, 0 }
    }
    const char *mode = "r";
    int check = 0;
    int quiet = 0;
    int status = 0;
    int warn_lines = 0;
    SkeinSize_t size = Skein512;
    size_t bitLen = 512;
    int bitlenset = 0;

    while ((c = getopt_long(argc, argv, optstring, longopts, NULL)) != -1)
    {
        switch (c)
        {
        case 'a':
            {
                int x = atoi(optarg);
                if (x != Skein256 && x != Skein512 && x != Skein1024)
                {
                    fprintf(stderr, "%s: invalid algorithm: %s (must be %d, %d, or %d)\n",
                        progname, optarg, Skein256, Skein512, Skein1024);
                    fprintf(stderr, "Try `%s --help' for more info", progname);
                    exit(EXIT_FAILURE);
                }
                size = (SkeinSize_t) x;
            }
            break;
            
        case 'l':
            {
                
            }
            
        case 'b':
            mode = "rb";
            break;
            
        case 'c':
            check = 1;
            break;
            
        case 't':
            mode = "r";
            break;
            
        case OPT_QUIET:
            quiet = 1;
            break;
            
        case OPT_STATUS:
            status = 1;
            break;
            
        case 'w':
            warn_lines = 1;
            break;
            
        case OPT_HELP:
            show_help();
            exit(EXIT_SUCCESS);
            
        case OPT_VERSION:
            show_version();
            exit(EXIT_SUCCESS);
            
        case '?':
            fprintf(stderr, "Try `%s --help' for more info", progname);
            exit(EXIT_FAILURE);
        }
    }
    
    exit(0);
}

void show_help(void)
{
    printf()
}

void show_version(void)
{
    printf("%s version %s", progname, SKEINSUM_VERSION);
}