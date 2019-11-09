
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define DEBUG
#define BYTES_IN_MEG (1024 * 1024) // 1 MB
#define DEF_SPLIT (BYTES_IN_MEG * 50) // 50 MB
#define DEF_MAX_ALLOC (BYTES_IN_MEG * 10) // 10 MB
#define FOLDER_EXT ".mandos"

char *replace_ext(char *, char, char, char *);


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
            FILE * fp_rd = fopen(argv[i], "rb");
            if (!fp_rd){
                fprintf(stderr, "Unable to open %s\n", argv[i]);
                continue;
            }
            printf("Dismembering ... %s\n", argv[i]);

            char * folder= replace_ext(argv[i], '.', '/', FOLDER_EXT);
            #ifdef DEBUG
                printf("[dbg] placing in folder: %s\n", folder);
            #endif
            mkdir(folder, 0755);


            char file_name[4096];
            void * buffer = malloc(b);

            unsigned int file_count = 0;

            


            unsigned int bytes_left = s;

            // while (fread(buffer, 1, b, fp_rd)){

            //     // sprintf(file_name, "%s/%d", folder, count);
            //     // FILE* fp_wr = fopen(file_name, "wb");

            //     // fwrite(buffer, 1, b, fp)
  

            //     // fclose(fp_wr);

            //     count++;
            // }



            // struct stat st = {0};
            // if (stat(folder, &st) == -1) {
            // } else {
            //     #ifdef DEBUG
            //         printf("[dbg] folder already exists\n");
            //     #endif
            // }

            // int check = mkdir(argv[i]); 
        } else {


        }




        
	}
}

/*
Pulled and modified from user `paxdiablo` on stackoverflow
https://stackoverflow.com/questions/2736753/how-to-remove-extension-from-file-name
*/
char *replace_ext (char* mystr, char dot, char sep, char * new_ext) {
    char *retstr, *lastdot, *lastsep;

    // Error checks and allocate string.
    if (mystr == NULL)
        return NULL;
    if ((retstr = malloc (strlen (mystr) + strlen (new_ext) + 1)) == NULL)
        return NULL;

    // Make a copy and find the relevant characters.
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, dot);
    lastsep = (sep == 0) ? NULL : strrchr (retstr, sep);

    // If it has an extension separator.
    if (lastdot != NULL) {
        // and it's before the extenstion separator.
        if (lastsep != NULL) {
            if (lastsep < lastdot) {
                // then remove it.
                *lastdot = '\0';
            }
        } else {
            // Has extension separator with no path separator.
            *lastdot = '\0';
        }
    }

    strcat(retstr, new_ext);

    // Return the modified string.
    return retstr;
}

    // FILE* file_ptr = fopen("png_urls.txt", "w");
    //     for (i = 0; i < found; i++){
	// 	        fprintf(file_ptr, "%s\n", pngs_found[i]);
	// 		    }
    // fclose(file_ptr);

