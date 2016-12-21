#include <iostream>
using std::cout;
using std::cin;

#include "genetico.h"
 
int **Disciplina;
int numDeDisciplinas;
int numDeAulas=0;

int fitness(int *individuo);
   
int main(){
    int evolucoes;
    int a=0,vet[]={2,6,0,1,2,7,8,9,2,6,0,1,4,5,8,9,2,4,1,2,7,9,1,7,0,1,2,3,6,7,9,1,5,0,1,4,6,7,2,5,0,2,4,6,8};
    cout << "Informe o numero de disciplinas: ";
    //cin >> numDeDisciplinas;
    numDeDisciplinas = 6;  
    cout << numDeDisciplinas << "\n";
    Disciplina = new int*[numDeDisciplinas];
    
    for(int count=0, aulas, indisp; count<numDeDisciplinas; count++){
        cout << "Informe o numero de aulas da disciplina " << count << ": ";
        //cin >> aulas;
        cout << vet[a] << "\n";
        aulas = vet[a++];
        numDeAulas += aulas;
        cout << "Informe o numero de horarios indisponiveis do professor da disciplina: ";
        //cin >> indisp;
        cout << vet[a] << "\n";
        indisp = vet[a++];
        Disciplina[count] = new int[2+indisp];
        Disciplina[count][0] = aulas;
        Disciplina[count][1] = indisp+2;
        cout << "Informe os horarios indisponiveis do professor (apartir de 0): ";
        for(int count1 = 2; count1<Disciplina[count][1]; count1++){      
            //cin >> Disciplina[count][count1];
            cout << vet[a] << " ";
            Disciplina[count][count1] = vet[a++];
        }
        cout << "\n";
    }
       
    cout << "Informe o numero maximo de evolucoes: ";
    //cin >> evolucoes;
    evolucoes = 1000;
    cout << evolucoes << "\n"; 
    Genetico *genetico = new Genetico(100, evolucoes, numDeAulas, numDeDisciplinas, fitness);
    
    int *horario = genetico->buscar();
    cout << "\nHorario: " << horario[0]-1;
    for(int count=1; count<numDeAulas; count++){
        cout << " - " << horario[count]-1;
    }
    
    getchar();
    getchar();
    return 0;
}
 
//Implementação particular para este problema
int fitness(int *individuo){

    static int resp;
    static int* disc = new int[numDeDisciplinas];
    resp=0;
    for(int count=0; count < numDeDisciplinas; count++){
        disc[count] = 0;
    }
    for(int count=0; count < numDeAulas; count++){
        for(int count1=2; count1 < Disciplina[individuo[count]-1][1]; count1++){
            if(count==Disciplina[individuo[count]-1][count1]){
                resp--;
                break;
            }
        }
        resp++;
        disc[individuo[count]-1]++;
    }
    for(int count=0, count1; count < numDeDisciplinas; count++){
        count1 = Disciplina[count][0] - disc[count];
        if(count1 > 0){
            resp -= count1;
        }
    }
    return resp;
}
  
