#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int numtraces = atoi(argv[2]);
    char input_name[100], outbuff[100], outname[100];
    char iord, type;
    unsigned long long addr;
    unsigned pc;

    sprintf(outname, "%s.out", argv[1]);
    FILE *fout = fopen(outname, "w");
    for (int k = 0; k < numtraces; k++) {
        sprintf(input_name, "%s_%d", argv[1], k);
        FILE *fp = fopen(input_name, "rb");
        assert(fp != NULL);

        while (!feof(fp)) {
            fread(&iord, sizeof(char), 1, fp);
            fread(&type, sizeof(char), 1, fp);
            fread(&addr, sizeof(unsigned long long), 1, fp);
            fread(&pc, sizeof(unsigned), 1, fp);

            // Process the entry
            sprintf(outbuff, "IorD: %d  Type: %d  Address: %12llu  PC: %u",
                    iord, type, addr, pc);
            fprintf(fout, "%s\n", outbuff);
        }
        fclose(fp);
        printf("Done reading file %d!\n", k);
    }
    fclose(fout);
    printf("Results written to file %s\n", outname);
    return 0;
}
