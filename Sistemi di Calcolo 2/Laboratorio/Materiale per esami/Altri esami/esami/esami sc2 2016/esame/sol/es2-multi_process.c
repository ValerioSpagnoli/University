#include <unistd.h>
#include <sys/wait.h>
#include "common.h"

#define CHILD_COUNT 2
#define GRANDCHILD_COUNT 3

int main(int argc, char* argv[]) {
    
	/**
     * SOLUZIONE
     * 
     * Obiettivi: creare CHILD_COUNT processi figlio
     * - usare il ciclo for seguente per creare CHILD_COUNT processi
     * - ogni figlio deve salvare la propria identità i (vedi specifica)
     * - gestire eventuali errori
     */
	 
    int i = 0, j = 0;
    for (; i < CHILD_COUNT; i++) {
        pid_t pid = fork();
        ERROR_HELPER(pid, "Errore fork");
        if (pid == 0) break;
    }
    
	
	/**
     * SOLUZIONE
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
	 
    if (i < CHILD_COUNT) {
        printf("[Figlio #%d] iniziato\n", i);
        for (; j < GRANDCHILD_COUNT; j++) {
            pid_t pid = fork();
            ERROR_HELPER(pid, "Errore fork");
            if (pid == 0) break;
        }
        
        if (j < GRANDCHILD_COUNT) {
            printf("[Nipote #%d.%d] iniziato\n", i, j);
            sleep(1);
            printf("[Nipote #%d.%d] terminato\n", i, j);
        } else {
            printf("[Figlio #%d] nipoti lanciati, in attesa della loro terminazione...\n", i);
            for (j = 0; j < GRANDCHILD_COUNT; j++) {
                pid_t pid = wait(NULL);
                ERROR_HELPER(pid, "Errore nella wait");
            }
            printf("[Figlio #%d] terminato\n", i);
        }
    } else {
        printf("[Padre] figli lanciati, in attesa della loro terminazione...\n");
        for (i = 0; i < CHILD_COUNT; i++) {
            pid_t pid = wait(NULL);
            ERROR_HELPER(pid, "Errore nella wait");
        }
        printf("[Padre] figli terminati\n");
    }
    
    return EXIT_SUCCESS;
}
