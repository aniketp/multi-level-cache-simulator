#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_TRACES 6
#define MAX_CHARS 100

typedef struct trace {
    int nums;
    char name[30];
} trace_t;

static mode_t mode = 0777;
static const char* tracedir = "traces";
static trace_t traces[6] = {
    {2, "bzip2.log_l1misstrace"},
    {2, "gcc.log_l1misstrace"},
    {1, "gromacs.log_l1misstrace"},
    {1, "h264ref.log_l1misstrace"},
    {1, "hmmer.log_l1misstrace"},
    {2, "sphinx3.log_l1misstrace"},
};

int main(int argc, char **argv) {
    char input_name[MAX_CHARS], outbuff[MAX_CHARS], out_name[MAX_CHARS];
    char iord, type;
    const char *folder = "output";
    unsigned pc;
    unsigned long long addr;
    struct stat sb;

    // Create a folder to store the processed traces
    if (stat(folder, &sb) || !S_ISDIR(sb.st_mode))
        mkdir(folder, mode);
    else printf("Output folder exists.\n");

    // For every trace provided, output the 'type' and 'address' in the
    // corresponding trace outfile. e.g bzip2.log_l1misstrace.out
    for (int i = 0; i < NUM_TRACES; i++) {
        sprintf(out_name, "%s/%s.out", folder, traces[i].name);
        FILE *fout = fopen(out_name, "w");
        for (int k = 0; k < traces[i].nums; k++) {
            sprintf(input_name, "%s/%s_%d", tracedir, traces[i].name, k);
            FILE *fp = fopen(input_name, "rb");
            assert(fp != NULL);

            while (!feof(fp)) {
                fread(&iord, sizeof(char), 1, fp);
                fread(&type, sizeof(char), 1, fp);
                fread(&addr, sizeof(unsigned long long), 1, fp);
                fread(&pc, sizeof(unsigned), 1, fp);

                // Process the entry
                sprintf(outbuff, "%d %llu", type, addr);
                fprintf(fout, "%s\n", outbuff);
            }
            fclose(fp);
            printf("Done reading file: %s\n", traces[i].name);
        }
        fclose(fout);
        printf("Results written to file: %s\n", out_name);
    }
    return 0;
}
