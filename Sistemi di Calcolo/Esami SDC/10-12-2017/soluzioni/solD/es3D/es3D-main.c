#include <stdio.h>
#include <string.h>
#include "es3D.h"

#define N 20000

char* str =
    "Designed to take fans of The Hobbit and The Lord of the "
    "Rings deeper into the myths and legends of Middle-Earth, "
    "The Silmarillion is an account of the Elder Days, of the "
    "First Age of Tolkien's world. It is the ancient drama to "
    "which the characters in The Lord of the Rings look back, "
    "and in whose events some of them such as Elrond and "
    "Galadriel took part. The tales of The Silmarillion are set "
    "in an age when Morgoth, the first Dark Lord, dwelt in "
    "Middle-Earth, and the High Elves made war upon him for the "
    "recovery of the Silmarils, the jewels containing the pure "
    "light of Valinor. Included in the book are several shorter "
    "works. The Ainulindale is a myth of the Creation and in the "
    "Valaquenta the nature and powers of each of the gods is "
    "described. The Akallabeth recounts the downfall of the great "
    "island kingdom of Numenor at the end of the Second Age and Of "
    "the Rings of Power tells of the great events at the end of the "
    "Third Age, as narrated in The Lord of the Rings. This pivotal "
    "work features the revised, corrected text and includes, by way "
    "of an introduction, a fascinating letter written by Tolkien in "
    "1951 in which he gives a full explanation of how he conceived "
    "the early Ages of Middle-Earth.";

int main() {

    unsigned i, j, chksum = 0;

    for (i=0; i<N; ++i) {
        charset* s = charset_new();
        unsigned n = strlen(str);

        for (j=0; j<n; ++j) charset_add(s, str[j]);
        for (j=0; j<256; ++j) chksum += charset_contains(s, j);

        charset_delete(s);
    }

    printf("Risultato %s (%u).\n",
        chksum == 1000000 ? "corretto" : "errato", chksum);

    return 0;
}
