#include <iostream>
#include <stdlib.h>

#include <cstdlib>
#include <ctime>

#ifndef GENETICO_H
#define GENETICO_H

using namespace std;

class Genetico{
    public:
        Genetico(int indv, int evolu, int genes, int alfa, int (*fit)(int *))
            :numeroDeAulasNoPeriodo(10),
            numeroDeDisciplinas(6),
            tamanhoDaPopulacao(100),
            numDeIndividuos(indv),
            numDeEvolucoes(evolu),
            numGenes(genes),
            numAlfabeto(alfa),
            fitness(fit){
            long x = 157593*160000+23917;
            seed = (190284 ^ x) & ((1L << 48) - 1);

            srand(time(0));

            initPop = new int*[tamanhoDaPopulacao];
            for(int count=0; count<tamanhoDaPopulacao; count++){
                    initPop[count] = new int[numeroDeAulasNoPeriodo];
            }
            gerarPopulacaoInicial();
            populacao = new int*[numDeIndividuos];
            novaGeracao = new int*[numDeIndividuos];
            for(int count=0; count<numDeIndividuos; count++){
                populacao[count] = new int[numGenes];
                for(int count2=0; count2<numGenes; count2++){
                    populacao[count][count2] = valorMutado();
                    populacao[count][count2] = initPop[count][count2] + 1;
                }
                novaGeracao[count] = new int[numGenes];
            }
            
            ordenarPopulacao();
        }
        
        int *buscar(){
            int *x, *y, *filho, geneMutado, count=0;
            for(count=0; count < numDeEvolucoes && !testeObjetivo(); count++){
                for(int count1=0; count1 < numDeIndividuos; count1++){
                    x = populacao[selecionarIndividuo()];
                    y = populacao[selecionarIndividuo()];
                    reproducao(x,y,count1);
                    geneMutado = geneDeMutacao();
                    if(geneMutado){
                        novaGeracao[count1][geneMutado-1] = valorMutado();
                    }
                }
                int **inverte = novaGeracao;
                novaGeracao = populacao;
                populacao = inverte;
                ordenarPopulacao();
            }
            cout << count <<" geracoes.";
            return populacao[0];
        }
        
        void reproducao(int *x, int *y, int filho){
            static int count, cros;
            cros = crossover();
            for(count=0; count<cros; count++){
                novaGeracao[filho][count] = x[count];
            }
            for(; count<numGenes; count++){
                novaGeracao[filho][count] = y[count];
            }
        }
        
        //Implementação particular para este problema
        bool testeObjetivo(){
            return (*fitness)(populacao[0])==numGenes;
        }
        
        void ordenarPopulacao(){

            for(int count=1, count1,*invert; count<numDeIndividuos; count++){
                invert = populacao[count];
                for(count1 = count-1; count1 >=0 && (*fitness)(populacao[count1])<(*fitness)(invert); count1--){
                    populacao[count1+1] = populacao[count1];
                }
                populacao[count1+1] = invert;
            }
        }
        
        //funções avaliadas
        int crossover(){
            //return rand()%(numGenes+1);
            return obterAleatorioParaCrossOver();
        }
        int geneDeMutacao(){
            //return rand()%(numGenes+1);
            return obterAleatorioParaEscolherGene();
        }
        int valorMutado(){
            //return 1 + rand()%numAlfabeto;
            return obterAleatorioParaRedefinirGene();
        }
        int selecionarIndividuo(){
            //return rand()%(1+rand()%numDeIndividuos);
            return obterAleatorioParaSelecionarIndividuo();
        }
//////////////////////////////////////////////////
int next(int bits)
{
 long qw = 157593*160000+23917;
	seed = (seed * qw + 0xBL) & ((1L << 48) - 1);
	unsigned long x = seed;
	return (int) (x >> (48 - bits));
}

int nextInt()
{
    return next(32);
}

int nextInt(int n)
{
	if ((n & -n) == n) // i.e., n is a power of 2
		return (int) ((n * (long) next(31)) >> 31);
	int bits, val;
	do
	{
		bits = next(31);
		val = bits % n;
	}
	while (bits - val + (n - 1) < 0);
	return val;
}

void gerarPopulacaoInicial(){
    for(int i = 0; i < tamanhoDaPopulacao; i++){
		for(int j = 0; j < numeroDeAulasNoPeriodo; j++){
			initPop[i][j] = -1;
		}
	}
	int numeroDeAulasNoPeriodoPorDisciplina[numeroDeDisciplinas];
	numeroDeAulasNoPeriodoPorDisciplina[0] = 2;
	numeroDeAulasNoPeriodoPorDisciplina[1] = 2;
	numeroDeAulasNoPeriodoPorDisciplina[2] = 2;
	numeroDeAulasNoPeriodoPorDisciplina[3] = 1;
	numeroDeAulasNoPeriodoPorDisciplina[4] = 1;
	numeroDeAulasNoPeriodoPorDisciplina[5] = 2;
	for(int indiv = 0; indiv < tamanhoDaPopulacao; indiv++){
		for(int i = 0; i < numeroDeDisciplinas; i++){
			int j = 0;
			while(j < numeroDeAulasNoPeriodoPorDisciplina[i]){
				int aux = nextInt(numeroDeAulasNoPeriodo);
				if(initPop[indiv][aux] != -1){
					continue;
				}
				initPop[indiv][aux] = i;
				j++;
			}
		}
	}

}

int obterAleatorioParaCrossOver(){
	return nextInt(numeroDeAulasNoPeriodo + 1);
}

int obterAleatorioParaEscolherGene(){
	return nextInt(numeroDeAulasNoPeriodo + 1);
}

int obterAleatorioParaRedefinirGene(){
	return nextInt(numeroDeDisciplinas) + 1;
}

int obterAleatorioParaSelecionarIndividuo(){
	int r = nextInt(tamanhoDaPopulacao) + 1;
	return nextInt(r) + 1;
}
//////////////////////////////////////////////////
    private:
        const int numDeIndividuos;
        const int numDeEvolucoes;
        const int numGenes;
        const int numAlfabeto;
        const int numeroDeAulasNoPeriodo;
        const int numeroDeDisciplinas;
        const int tamanhoDaPopulacao;
        int (*fitness)(int *);
        int **populacao;
        int **initPop;
        int **novaGeracao;
        long seed;
};

#endif
