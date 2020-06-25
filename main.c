#define SHA1HANDSOFF
#define TAILLE_MAX 1000 // Tableau de taille 1000

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>	/* for u_int*_t */
#if defined(__sun)
#include "solarisfixes.h"
#endif
#include "sha1.h"
#include "md4.h"
#include "md5.h"

int main(int argc, char const *argv[])
{

    FILE* fichier = NULL;
    FILE* out1, *out2, *out3 = NULL;
    out1 = fopen("out/md4.txt", "a+");
    out2 = fopen("out/md5.txt", "a+");
    out3 = fopen("out/sha1.txt", "a+");

    char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
    fichier = fopen("in.txt", "r");
    while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
    {
    // SHA-1 call
      char result[21];
      size_t offset;

      /* calculate hash */
      SHA1( result, chaine, strlen(chaine) );

      /* format the hash for comparison */
      printf("SHA-1=");
      for( offset = 0; offset < 20; offset++) {
        printf("%02x", result[offset]&0xff);
        fprintf(out3,"%02x", result[offset]&0xff);
      }
      printf("\n");
      fprintf(out3,"\n");
    // MD4 call
        printf("MD4=%s \n", MD4(chaine, strlen(chaine)));
        fprintf(out1,"%s \n", MD4(chaine, strlen(chaine)));

    // MD5 call
        unsigned *d = md5(chaine, strlen(chaine));
        WBunion u;

        int j,k;
        printf("MD5=");
        for (j=0;j<4; j++){
            u.w = d[j];
            for (k=0;k<4;k++) {
                printf("%02x",u.b[k]);
                fprintf(out2,"%02x",u.b[k]);
            }
        }
        printf("\n");
        fprintf(out2,"\n");
        fclose(fichier);
    }
     return 0;
}
