#include <unistd.h>
#include <sys/wait.h>
#include "common.h"

#define CHILD_COUNT 2
#define GRANDCHILD_COUNT 3

int main(int argc, char* argv[]) {
    
    /**
     * COMPLETARE QUI
     * 
     * Obiettivi: creare CHILD_COUNT processi figlio
     * - usare il ciclo for seguente per creare CHILD_COUNT processi
     * - ogni figlio deve salvare la propria identità i (vedi specifica)
     * - gestire eventuali errori
     */
     
    int i = 0, j = 0;
    for (; i < CHILD_COUNT; i++) {

    }
    
    
    /**
     * COMPLETARE QUI
     * 
     * Obiettivi
     * - ognuno dei processi figli deve a sua volta creare altri
     *   GRANDCHILD_COUNT processi figli (che qui chiamiamo processi nipoti)
     *   ° i processi nipoti devono eseguire sleep(1)
     *   ° i processi figli devono attendere il termine di tutti i 
     *     nipoti
     * - il processo padre deve attendere il termine di tutti i figli
     * - usare la variabile i per distinguere il padre dai figli
     * - usare la variabile j per distinguere i figli dai nipoti
     * - gestire eventuali errori
     */
    
    
    return EXIT_SUCCESS;
}
