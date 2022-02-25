#ifndef COMMON_H
#define COMMON_H

// macro gestione errori
#define GENERIC_ERROR_HELPER(cond, errCode, msg) do {               \
        if (cond) {                                                 \
            fprintf(stderr, "%s: %s\n", msg, strerror(errCode));    \
            exit(EXIT_FAILURE);                                     \
        }                                                           \
    } while(0)

#define ERROR_HELPER(ret, msg)          GENERIC_ERROR_HELPER((ret < 0), errno, msg)
#define PTHREAD_ERROR_HELPER(ret, msg)  GENERIC_ERROR_HELPER((ret != 0), ret, msg)

/* Configuration parameters */
#define N               5   // numero di semafori e di contatori nel buffer condiviso
#define SLEEP_TIME      3   // numero di secondi per simulare il processamento di una risorsa
#define STATS_TIME      10  // intervallo per stampa statistiche
#define SERVER_ADDRESS  "127.0.0.1"
#define SERVER_COMMAND  "QUIT"
#define SERVER_PORT     2015

#endif
