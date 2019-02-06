// Ben Cradick
// 2/6/19
// cs4760

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "stack.h"



//Note: Many comments are to tell myself what the hell I was thinking, later.

void check_fprintf(int);

int main(int argc, char **argv) {
    char *inputFile;
    char *outputFile;
    int c; // used to hold integer return value of getopt
    int childCount; // number of children to be generated, also first line in inputFile.

    // Written when 8GB RAM was standard, on a project where efficiency was not a requirement.

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
    outputStream = fopen(outputFile, "w+");
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

    int *pids = malloc(sizeof(int) * childCount);

    for(int i = 0; i < childCount; i++){
        fgets(line, LINE_MAX, inputStream);
        if(fork() == 0){

            Stack stack = createStack(&stack, atoi(line));

            //sizeof line provides the appropriate string length.
            fgets(line, sizeof(line), inputStream);

            char* token = strtok(line, " ");

            while(token != NULL){

                stack.push(&stack, atoi(token)); // TODO: type check token before moving to atoi.
                token = strtok(NULL, " ");
            }

            check_fprintf(
                fprintf(outputStream, "%d: ", getpid())
                );

            while(stack.size != -1){
                //function across 3 lines for readability.
                check_fprintf(
                        fprintf(outputStream, "%d ", stack.pop(&stack))
                        );
            }

            check_fprintf(fprintf(outputStream, "\n"));

            exit(0);
        }
        else{
            //sneak the pids that were used in so they can be displayed later
            pids[i] =  wait(0);

        }
        fgets(line, LINE_MAX, inputStream);
    }

    // readability.
    check_fprintf(
            fprintf(outputStream, "All children used:   ")
    );


    for(int x = 0; x < childCount; x++){
        //for readability

       check_fprintf(
               fprintf(outputStream, "%d ", pids[x])
               );
    }
    check_fprintf(
            fprintf(outputStream, "\n")
            );
    fclose(outputStream);
    return (0);
}

void check_fprintf(int toBeChecked){
    if(toBeChecked < 0){
        perror("Failed to write to stream output: ");
    }
}
