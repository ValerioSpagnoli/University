#ifndef COMMON_H
#define COMMON_H

// macros for handling errors
#define handle_error_en(en, msg)    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
#define handle_error(msg)           do { perror(msg); exit(EXIT_FAILURE); } while (0)

/* Configuration parameters */
#define N               5   // numero di semafori e di contatori nel buffer condiviso
#define SLEEP_TIME      3   // numero di secondi per simulare il processamento di una risorsa
#define STATS_TIME      10  // intervallo per stampa statistiche
#define SERVER_ADDRESS  "127.0.0.1"
#define SERVER_COMMAND  "QUIT"
#define SERVER_PORT     2015

#endif
