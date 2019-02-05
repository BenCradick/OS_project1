#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#include "stack.h"

int main(int argc, char **argv) {
    char *inputFile;
    char *outputFile;
    int c; // used to hold integer return value of getopt
    int childCount; // number of children to be generated, also first line in inputFile.

    char line[LINE_MAX];

    pid_t child_pid;

    inputFile = "input.dat";
    outputFile = "output.dat";

    FILE *inputStream;
    FILE *outputStream;

    opterr = 0;

    while((c = getopt(argc, argv, "hi:o:")) != -1 ){
        switch(c) {
            case 'h':
                printf("%s\n\t%s\n\t%s\n\t%s",
                       "The available options for this program are:",
                       "-h: Display the help (this) page",
                       "-i: Specify an input file. ex: cradick.1 -i [file]",
                       "-o: Specify an output file. ex: cradick.1 -o [filename]");
                break;

            case 'i' :
                inputFile = optarg;
                break;

            case 'o' :
                outputFile = optarg;
                break;

            case '?':
                if (optopt == 'i')
                   fprintf(stderr, "Option -i requires an argument");

                else if (optopt == 'o')
                    fprintf(stderr, "Option -o requires an argument.");

                else if (isprint(optopt) == 1)
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);

                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);

                return 1;

            default:
                fprintf(stderr, "Unknown command line argument error occurred. \n");
                printf("Argument error: Use command cradick.1 -h  for help");
                abort();

        }
    }


    inputStream = fopen(inputFile, "r");

    if(inputStream == NULL){
        perror(inputFile);
        return -1;
    }

    if(fgets(line, LINE_MAX, inputStream) == NULL){
        fprintf(stderr, "File %s contains no text", inputFile);
        fclose(inputStream);
        return 2;
    }

    childCount = atoi(line);


    for(int i = 0; i < childCount; i++){
        if(fork() == 0){
            fgets(line, LINE_MAX, inputStream);
            Stack* stack = createStack(stack,atoi(line));

            push(stack, 8);


            printf("%d\n", stack->isEmptyPtr);

            exit(0);
        }
        else{
            child_pid = wait(0);
            printf("Parent = %d\n", getpid());
            printf("Child = %d\n", child_pid);

        }
    }



    return (0);
}