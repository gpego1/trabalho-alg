#include <stdio.h>
#define NUM_CANDIDATOS 6
#define MIN_VOTOS 100

int main() {

    char nomes[NUM_CANDIDATOS][50] = {
        "Ana Silva",
        "Bruno Costa",
        "Carla Dias",
        "Diego Rocha",
        "Elisa Martins",
        "Felipe Souza"
    };

    int input;
    int votos[NUM_CANDIDATOS] = {0};
    int numeroCandidatos[NUM_CANDIDATOS] = {1,2,3,4,5,6};
    int historico[2][8] = {0};
    int totalVotos = 0;
    int votosBranco = 0;
    int votosNulo = 0;
    int vencedor = 0;
    int turno = 1;
    int votosPrimeiroColocado = 0;
    int votosSegundoColocado = 0;
    int primeiroClassificado = 0;
    int segundoClassificado = 0;
    int indexVencedor = 0;
    int apuracao = 0;
    int primeiroTurnoConcluido = 0;

    do{
        printf("==== SISTEMA ELEITORAL ====\n");
        scanf("%d", &input);
        if (input == 0) break;

        switch(input) {
            case(1): {
                if (primeiroTurnoConcluido == 1 || turno != 1) {
                    printf("A apuracao do 1 turno ja foi feita.\n");
                    break;
                }
                int k = 0;
                int voto;

                printf("==== Iniciando %do turno ====\n", turno);
                while(k < MIN_VOTOS) {
                    printf("Numero - Nome");
                    for (int i = 0; i < 6; i++) {
                        printf("%d - %s \n", numeroCandidatos[i], nomes[i]);
                        printf("%d - Voto branco\nQualquer outro numero - Anular", 0);
                    }
                    scanf("%d", &voto);
                    if (voto == 0) {
                        votosBranco += 1;
                        historico[turno -1][6]++;
                    } else if (voto >= 1 && voto <= 6) {
                        historico[turno -1][voto -1]++;
                        votos[voto-1]++;
                        
                    } else {
                        votosNulo += 1;
                        historico[turno -1][7]++;
                    }     
                    totalVotos += 1;
                    k += 1;
                }
                printf("Deseja continuar votando? (S/N)\n");
                char resp;
                do {
                    scanf(" %c", &resp);
                    if (resp == 's' || resp == 'S') {
                        scanf("%d", &voto);
                        if (voto == 0) {
                            votosBranco += 1;
                            historico[turno -1][6]++;
                        } else if (voto >= 1 && voto <= 6) {
                            historico[turno -1][voto-1]++;
                            votos[voto-1]++;
                        } else {
                            votosNulo += 1;
                            historico[turno -1][7]++;
                        }
                        totalVotos += 1;
                        k += 1;
                    } else if (resp != 'S' && resp != 's' && resp != 'N' && resp != 'n') {
                        printf("Entrada inválida, digite 'S' para continuar e 'N' para encerrar.\n");
                        continue;
                    } 
                } while (resp != 'N' && resp != 'n');
                    primeiroTurnoConcluido = 1;
                    break;
            }
            case(2):
                if (apuracao == 1 ||apuracao == 4) {
                    printf("O primeiro turno ja foi apurado.\n");
                    break;
                }

                if (primeiroTurnoConcluido == 0) {
                    printf("Conclua a votacao do primeiro turno antes de apurar.\n");
                    break;
                }

                if (totalVotos > 0 && turno == 1) {
                    int votosValidos =  totalVotos - votosBranco - votosNulo;

                    if (votosValidos <= 0) {
                        printf("Não foi possível concluir a operaação devido à ausencia de votos validos.");
                        apuracao = 4;
                        break;
                    } else {
                        printf("Lendo resultados do %do turno\n", turno);
                        printf("Total: %d   |  Validos: %d (%.1f%%) |  Brancos: %d (%.1f%%)    |   Nulos: %d (%.1f%%) \n",
                        totalVotos, votosValidos, (float) votosValidos/totalVotos * 100, 
                        votosBranco,(float) votosBranco/totalVotos * 100, votosNulo, (float) votosNulo/totalVotos * 100);

                        printf("Numero  Candidato   Votos   %% dos validos \n");
                        for (int i = 0; i < NUM_CANDIDATOS; i++) {
                            float percentual = (float) historico[turno -1][i] / votosValidos * 100;
                            printf("%d - %s - %d - %.1f%%\n",
                                 numeroCandidatos[i], 
                                 nomes[i], 
                                 historico[turno -1][i],
                                 percentual
                                );


                            if (percentual > 50.0) {
                                vencedor = numeroCandidatos[i];
                                indexVencedor = i;
                            } else if (historico[turno -1][i] > votosPrimeiroColocado) {
                                    votosSegundoColocado = votosPrimeiroColocado;
                                    segundoClassificado = primeiroClassificado;

                                    votosPrimeiroColocado = historico[turno -1][i];
                                    primeiroClassificado = numeroCandidatos[i];
                                } else if (historico[turno -1][i] > votosSegundoColocado) {
                                    votosSegundoColocado = historico[turno -1][i];
                                    segundoClassificado = numeroCandidatos[i];
                            }
                        }
                        apuracao = 1;
                    }
                } else {
                    printf("Não houveram votos no %do turno.\n", turno);                
                }
                break;
                
            case(3):
                if (apuracao == 4) {
                    printf("Não houveram votos válidos durante a apuração.\n");
                    break;
                } else if (apuracao == 0) {
                    printf("Faca a apuracao do primeiro turno antes de prosseguir para esta etapa.");
                } else if (vencedor != 0) {
                    printf("As eleições já foram encerradas no primeiro turno, e o vencedor foi %s \n", nomes[indexVencedor]);
                } else if (turno == 2) {
                    printf("O segundo turno ja foi iniciado.\n");
                } else {
                    turno = 2;
                    printf("Iniciando %do turno\n", turno);

                    for (int i = 0; i < 2; i++) {
                        printf("%d - %s \n", primeiroClassificado, nomes[primeiroClassificado -1]);
                        printf("%d - %s \n", segundoClassificado, nomes[segundoClassificado -1]); 
                        printf("%d - Voto branco\nQualquer outro numero - Anular", 0);
                    }

                    int k = 0;
                    totalVotos = 0;
                    votosBranco = 0;
                    votosNulo = 0;
                    int voto = 0;
                    char resp;

                    for (int i = 0; i < NUM_CANDIDATOS; i++) {
                        votos[i] = 0;
                    }

                    while (k != MIN_VOTOS) {
                        scanf("%d", &voto);
                        if (voto == 0) {
                            votosBranco += 1;
                            historico[turno -1][6]++;
                        } else if (voto == primeiroClassificado || voto == segundoClassificado) {
                            historico[turno -1][voto -1]++;
                            votos[voto -1]++;
                        } else {
                            votosNulo += 1;
                            historico[turno -1][7]++;
                        }
                        totalVotos += 1;
                        k += 1;
                    }
                    do {
                        scanf(" %c", &resp);
                        if (resp == 's' || resp == 'S') {
                            scanf("%d", &voto);
                            if (voto == 0) {
                                votosBranco += 1;
                                historico[turno -1][6]++;
                            } else if (voto == primeiroClassificado || voto == segundoClassificado) {
                                historico[turno -1][voto-1]++;
                                votos[voto-1]++;
                            } else {
                                votosNulo += 1;
                                historico[turno -1][7]++;
                            }
                            totalVotos += 1;
                            k += 1;
                        } else if (resp != 'S' && resp != 's' && resp != 'N' && resp != 'n') {
                            printf("Entrada inválida, digite 'S' para continuar e 'N' para encerrar.\n");
                            continue;
                        } 
                    } while (resp != 'N' && resp != 'n');
                        apuracao = 2;
                        break;                    
                }
                break; 
            case(4):
                if (apuracao == 4) {
                    printf("Não houveram votos válidos durante a apuracao.\n");
                } else if (apuracao == 5) {
                    printf("A apuracao do segundo turno nao obteve votos validos. \n");
                } else if (apuracao == 1 && vencedor != 0) {
                    printf("%s venceu no primeiro turno", nomes[indexVencedor]);
                } 
                else if (apuracao == 2 && turno == 2 && totalVotos >= MIN_VOTOS) {
                    int votosValidosSegundoTurno = totalVotos - votosBranco - votosNulo;

                    if (votosValidosSegundoTurno <= 0) {
                        printf("Não foi possível determinar a quantidade de votos válidos.\n");
                        apuracao = 5;
                        break;
                    } else {
                        printf("Lendo resultados do %do turno \n", turno);
                        printf("Total: %d   |  Validos: %d (%.1f%%) |  Brancos: %d (%.1f%%)    |   Nulos: %d (%.1f%%) \n",
                        totalVotos, votosValidosSegundoTurno, (float) votosValidosSegundoTurno/totalVotos * 100, 
                        votosBranco,(float) votosBranco/totalVotos * 100, votosNulo, (float) votosNulo/totalVotos * 100);

                        printf("Numero  Candidato   Votos   %% dos validos \n");
                        for (int i = 0; i < 2; i++) {
                            int candidatoSegTurno;

                            if (i == 0) {
                                candidatoSegTurno = primeiroClassificado -1;
                            } else {
                                candidatoSegTurno = segundoClassificado -1;
                            }
                            float percentual = (float) historico[turno -1][candidatoSegTurno] / votosValidosSegundoTurno * 100;
                            printf("%d - %s - %d - %.1f%%\n",
                                 numeroCandidatos[candidatoSegTurno], 
                                 nomes[candidatoSegTurno], 
                                 historico[turno -1][candidatoSegTurno],
                                 percentual
                                );
                    }
                    int votosPrimeiroClassificado = historico[turno - 1][primeiroClassificado -1];
                    int votosSegundoClassificado = historico[turno -1][segundoClassificado -1];

                    if (votosPrimeiroClassificado > votosSegundoClassificado) {
                        vencedor = primeiroClassificado;
                        indexVencedor = primeiroClassificado -1;
                        printf("Vencedor do 2 turno: %s \n", nomes[indexVencedor]);
                    } else if (votosSegundoClassificado > votosPrimeiroClassificado) {
                        vencedor = segundoClassificado;
                        indexVencedor = segundoClassificado -1;
                        printf("Vencedor do 2 turno: %s \n", nomes[indexVencedor]);
                    } else {
                        printf("Empate no Segundo turno! \n");
                    }
                    apuracao = 3;
                }
            } else if (apuracao == 3) {
                printf("Segundo turno ja encerrado. \n");
            } else {
                printf("Erro inesperado, tente novamente!");
            }
                break;
                
            default:
                printf("Erro inesperado, renicie a aplicação!\n");
        
    }} while (1);


    return 0;
}