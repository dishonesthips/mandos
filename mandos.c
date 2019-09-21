
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define BYTES_IN_MEG (1024 * 1024) // 1 MB
#define DEF_SPLIT (BYTES_IN_MEG * 50) // 50 MB
#define DEF_MAX_ALLOC (BYTES_IN_MEG * 10) // 10 MB

int main(int argc, char ** argv){
    int opt, i;
    unsigned int r,d,s,b,k;
	r = 0;
    d = 0;
    k = 0;
    s = DEF_SPLIT;
    b = DEF_MAX_ALLOC;

    while ((opt = getopt(argc, argv, "rdks:b:")) != -1) {
        switch (opt) {
        case 'r':
            r = 1;
            break;
        case 'd':
            d = 1;
            break;
        case 'k':
            k = 1;
            break;
		case 's':
		    s = strtoul(optarg, NULL, 10) * BYTES_IN_MEG;
		    break;
		case 'b':
		    b = strtoul(optarg, NULL, 10) * BYTES_IN_MEG;
		    break;
		default: /* '?' */
	        fprintf(stderr, "Usage: %s [OPTIONS] filepath1 filepath2 ...\n",
		    argv[0]);
		    exit(EXIT_FAILURE);
		}
	}

	if (!(r ^ d)){
	    fprintf(stderr, "You MUST specify EITHER [-d] OR [-r]\n");
	    exit(EXIT_FAILURE);
	}

	if (optind >= argc) {
	    fprintf(stderr, "Expected filepath argument(s) after options\n");
	    exit(EXIT_FAILURE);
	}

	for (i = optind; i < argc; i++){

        if (d){
            FILE * fp = fopen(argv[i], "rb");
            if (!fp){
                fprintf(stderr, "Unable to open %s\n", argv[i]);
                continue;
            }
            printf("Dismembering ... %s\n", argv[i]);

            char path[4096] = argv[i];

            struct stat st = {0};

            if (stat(argv[i], &st) == -1) {
                mkdir(argv[i], 0755);
            }

            // int check = mkdir(argv[i]); 
        } else {


        }




        
	}
// #ifdef DEBUG
// printf("debug:x = %d, y = %f\n", x, y);
//      ...
// #endif



}

void rem_ext(char * file_path){

    
}


    // FILE* file_ptr = fopen("png_urls.txt", "w");
    //     for (i = 0; i < found; i++){
	// 	        fprintf(file_ptr, "%s\n", pngs_found[i]);
	// 		    }
    // fclose(file_ptr);

