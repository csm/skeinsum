/* skeinsum.c -- command-line driver for skein.
   Copyright (C) 2011 Casey Marshall. */
   

#include <getopt.h>
#include <stdio.h>
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
    const char *optstring = "bcl:s:tw";
    const struct option longopts[] = {
        { "statesize", required_argument, NULL, 's' },
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
    };
    const char *mode = "r";
    int check = 0;
    int quiet = 0;
    int status = 0;
    int warn_lines = 0;
    SkeinSize_t size = Skein512;
    size_t bitlen = 512;
    int bitlenset = 0;

    while ((c = getopt_long(argc, argv, optstring, longopts, NULL)) != -1)
    {
        switch (c)
        {
        case 's':
            {
                int x = atoi(optarg);
                if (x != Skein256 && x != Skein512 && x != Skein1024)
                {
                    fprintf(stderr, "%s: invalid state size: %s (must be %d, %d, or %d)\n",
                        progname, optarg, Skein256, Skein512, Skein1024);
                    fprintf(stderr, "Try `%s --help' for more info.\n", progname);
                    exit(EXIT_FAILURE);
                }
                size = (SkeinSize_t) x;
            }
            break;
            
        case 'l':
            {
                bitlen = atoi(optarg);
                if (bitlen < 0 || bitlen > 1024)
                {
                    fprintf(stderr, "%s: invalid bit length size: %s\n", progname, bitlen);
                    fprintf(stderr, "Try `%s --help' for more info.\n", progname);
                    exit(EXIT_FAILURE);
                }
            }
            break;
            
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
            fprintf(stderr, "Try `%s --help' for more info.\n", progname);
            exit(EXIT_FAILURE);
        }
    }
    
    if (bitlen > size)
    {
        fprintf(stderr, "%s: invalid bit length size: %s\n", progname, bitlen);
        fprintf(stderr, "Try `%s --help' for more info.\n", progname);
        exit(EXIT_FAILURE);        
    }
    
    exit(0);
}

void show_help(void)
{
    printf("Usage: %s [OPTIONS]... [FILE]...\n", progname);
    printf("Print or check Skein checksums.\n");
    printf("With no FILE, or when FILE is -, read standard input.\n\n");
    
    printf("  -s, --statesize=SIZE      Use internal state size SIZE, one of\n");
    printf("                            256, 512, or 1024 (default 512)\n");
    printf("  -l, --length=LEN          Use output length LEN (default, equals\n");
    printf("                            state size).\n");
    printf("  -b, --binary              Read files in binary mode.\n");
    printf("  -c, --check               Read Skein sums from the FILEs and check them.\n");
    printf("  -t, --text                Read files in text mode (default).\n\n");
    
    printf("The following options are used when checking sums:\n");
    printf("      --quiet               Don't print OK for each successfully verified file.\n");
    printf("      --status              Don't output anything, status code shows success.\n");
    printf("  -w, --warn                Warn about improperly formatted checksum lines.\n\n");
    
    printf("Other options:\n");
    printf("      --help                Show this help and exit.\n");
    printf("      --version             Show version number and exit.\n");
}

void show_version(void)
{
    printf("%s version %s\n", progname, SKEINSUM_VERSION);
}