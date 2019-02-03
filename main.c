#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *inputFile;
    char *outputFile;
    int c; // used to hold integer return value of getopt

    while((c = getopt(argc, argv, "hi:o:")) != -1 ){
        switch(c){
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

            case '?':
                if (optopt == 'i')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);

                else
                    fprintf (stderr,
                             "Unknown option character `\\x%x'.\n",
                             optopt);
                return 1;

            default:
                abort();

        }
    }
    return 0;
}