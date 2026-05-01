#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

void passa_tempo(int tid, int sala, int decimos)
{
    struct timespec zzz, agora;
    static struct timespec inicio = {0,0};
    int tstamp;

    if ((inicio.tv_sec == 0)&&(inicio.tv_nsec == 0)) {
        clock_gettime(CLOCK_REALTIME,&inicio);
    }

    zzz.tv_sec  = decimos/10;
    zzz.tv_nsec = (decimos%10) * 100L * 1000000L;

    if (sala==0) {
        nanosleep(&zzz,NULL);
        return;
    }

    clock_gettime(CLOCK_REALTIME,&agora);
    tstamp = ( 10 * agora.tv_sec  +  agora.tv_nsec / 100000000L )
            -( 10 * inicio.tv_sec + inicio.tv_nsec / 100000000L );

    printf("%3d [ %2d @%2d z%4d\n",tstamp,tid,sala,decimos);

    nanosleep(&zzz,NULL);

    clock_gettime(CLOCK_REALTIME,&agora);
    tstamp = ( 10 * agora.tv_sec  +  agora.tv_nsec / 100000000L )
            -( 10 * inicio.tv_sec + inicio.tv_nsec / 100000000L );

    printf("%3d ) %2d @%2d\n",tstamp,tid,sala);
}


int main(int argc, char** argv) {
  
    // Declarações e leituras iniciais para criação da matriz de controle de threads
    int numSalas, numThreads;
    scanf("%d", &numSalas);
    scanf("%d", &numThreads);
    printf("%d %d\n", numSalas, numThreads);
    
    // Matriz de controle das threads
    #define NUM_MAX_SALAS 30
    #define NUM_MAX_THREADS 10
    #define NUM_INFO_BASICAS_DA_THREAD 3
    
    int matrizDeControleDasThreads[NUM_MAX_THREADS][NUM_INFO_BASICAS_DA_THREAD];
    for (int i = 0; i < NUM_MAX_THREADS; i++) {
        for (int j = 0; j < NUM_INFO_BASICAS_DA_THREAD; j++) {
            matrizDeControleDasThreads[i][j] = 0;
        }
    }

    // Matriz de visitas da thread
    #define NUM_MAXIMO_DE_SALAS_VISITADAS 1000
    #define NUM_DE_INFO_POR_VISITA 2
    int (*matrizDeVisitasDasThreads)[NUM_MAXIMO_DE_SALAS_VISITADAS][NUM_DE_INFO_POR_VISITA] = 
        malloc(NUM_MAX_THREADS * sizeof(matrizDeVisitasDasThreads));

    // Armazenando as informações das threads
    int threadId;
    int tempoInicialDaThread;
    int qtdSalasVisitadasPelaThread;
    for (int i = 0; i < numThreads; i++) {
        scanf("%d", &threadId);
        scanf("%d", &tempoInicialDaThread);
        scanf("%d", &qtdSalasVisitadasPelaThread);
        matrizDeControleDasThreads[i][0] = threadId;
        matrizDeControleDasThreads[i][1] = tempoInicialDaThread;
        matrizDeControleDasThreads[i][2] = qtdSalasVisitadasPelaThread;

        for (int j = 0; j < qtdSalasVisitadasPelaThread; j++){
            int idDaSala;
            int tempoMinimoNaPosicao;
            scanf("%d", &idDaSala);
            scanf("%d", &tempoMinimoNaPosicao);
            matrizDeVisitasDasThreads[i][j][0] = idDaSala;
            matrizDeVisitasDasThreads[i][j][1] = tempoMinimoNaPosicao;
        }

    }


    // Prints for debbuggin
    for (int i = 0; i < numThreads; i++) {
        for (int j = 0; j < NUM_INFO_BASICAS_DA_THREAD; j++) {
            printf("%d ", matrizDeControleDasThreads[i][j]);
        }
        printf("\n");
            for (int m = 0; m < matrizDeControleDasThreads[i][2]; m++) {
                    printf("%d %d \n", 
                        matrizDeVisitasDasThreads[i][m][0], 
                        matrizDeVisitasDasThreads[i][m][1]);
        }
        printf("\n");
    }

    free(matrizDeVisitasDasThreads);
    return 0;
}
