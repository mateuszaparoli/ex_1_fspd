#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define NUM_MAX_SALAS 10
#define NUM_MAX_THREADS 30
#define NUM_INFO_BASICAS_DA_THREAD 3

#define NUM_MAXIMO_DE_SALAS_VISITADAS 60
#define NUM_DE_INFO_POR_VISITA 2

int matrizDeControleDasThreads[NUM_MAX_THREADS][NUM_INFO_BASICAS_DA_THREAD];

int matrizDeVisitasDasThreads[NUM_MAX_THREADS][NUM_MAXIMO_DE_SALAS_VISITADAS][NUM_DE_INFO_POR_VISITA];

int numSalas, numThreads;

void passa_tempo(int tid, int sala, int decimos);

void* trabaioDaThread(void* arg);

int main(int argc, char** argv) {
  
    // leituras iniciais para criação da matriz de controle de threads
    scanf("%d", &numSalas);
    scanf("%d", &numThreads);
    printf("%d %d\n", numSalas, numThreads);
    
    // inicialização da matriz de controle das threads
    for (int i = 0; i < NUM_MAX_THREADS; i++) {
        for (int j = 0; j < NUM_INFO_BASICAS_DA_THREAD; j++) {
            matrizDeControleDasThreads[i][j] = 0;
        }
    }

    // armazenando as informações das threads
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

    // Criação das Threads
    pthread_t nossasThreads[numThreads];
    for (int i = 0; i < numThreads; i++) {
        if(pthread_create(&nossasThreads[i], NULL, trabaioDaThread, (void*)i) != 0) {
            perror("Erro pra cria a thread");
            exit(1);
        }
    }
    
    // Prints para depurar o trem
    // for (int i = 0; i < numThreads; i++) {
    //     for (int j = 0; j < NUM_INFO_BASICAS_DA_THREAD; j++) {
    //         printf("%d ", matrizDeControleDasThreads[i][j]);
    //     }
    //     printf("\n");
    //         for (int m = 0; m < matrizDeControleDasThreads[i][2]; m++) {
    //                 printf("%d %d \n", 
    //                     matrizDeVisitasDasThreads[i][m][0], 
    //                     matrizDeVisitasDasThreads[i][m][1]);
    //     }
    //     printf("\n");
    // }

    // Juntando as threads para esperarem que todas acabem antes do programa encerrar
    for(int i = 0; i < numThreads; i++) {
        pthread_join(nossasThreads[i], NULL);
    }

    return 0;
}

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

void* trabaioDaThread(void* arg) {
    
    long indiceDaThread = (long) arg;

    int idDaThread = matrizDeControleDasThreads[indiceDaThread][0];
    int tempoDeEspera = matrizDeControleDasThreads[indiceDaThread][1];
    int quantidadeDeSalasPraVisitar = matrizDeControleDasThreads[indiceDaThread][2];

    passa_tempo(idDaThread, 0, tempoDeEspera);
    
    for (int k = 0; k < quantidadeDeSalasPraVisitar; k++) {
        
    }

    return NULL;
}