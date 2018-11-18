#include <iostream>
#include <math.h>
#include <cmath>
#include <iomanip>

using namespace std;

float pi = 3.14159;

float tolerance = 0.0001;
int maximum_interations = 100;
int Nx = 4, Ny = 4;

float V1 = 0;
float V2 = 10;
float V3 = 20;
float V4 = -10;

float AV = (V1 + V2 + V3 + V4)/4;

float h = 1/float(Nx);


int main(){

    float V[1+Nx][1+Ny] = {AV};

    //Incluindo as codições de contorno

    for(int i = 0; i<=Nx; i++){
        V[i][0] = V1;
        V[i][Ny] = V3;
        V[0][i] = V4;
        V[Nx][i] = V2;
    }

    //Mudando os Potenciais nas bordas

    V[0][0] = (V1 + V4)/2;
    V[0][4] = (V4 + V3)/2;
    V[4][0] = (V1 + V2)/2;
    V[4][4] = (V2 + V3)/2;


    //Encontrando o fator de relaxação otimizado

    float T = cos(pi/Nx) + cos(pi/Ny);
    float w = (8 - sqrt(64 - 16 * T * T)) / (T * T);
    float w4 = w/4;

    cout << "Fator de Relaxacao: " << w << endl;

    //Contador de Iterações

    int ncount = 0;
    float rmin = 0;

    float x;
    float y;
    float g;
    float residue;




    while(true){

        for(int i = 1; i <= (Nx - 1) ;i++){
            x = h*i;


            for(int j = 1; j<= (Ny -1); j++){

                y = h*j;
                g = -36 * pi * x * (y - 1);
                residue = w4*(V[i +1][j] + V[i-1][j] + V[i][j+1] + V[i][j-1] - 4*V[i][j] - g*h*h);
                rmin = rmin + abs(residue);
                V[i][j] = V[i][j] + residue;


            }
        }

        //Média de Resíduo por ponto da grade

        rmin = rmin/(Nx*Ny);


        if(rmin >= tolerance){
            ncount = ncount + 1;
        }
            else{

                cout << "A solucao convergiu em " << ncount << " iteracoes:" << endl;
                cout << setw(12);
                for(int i = 1; i<=3; i++){
                    for(int j = 1; j<=3; j++){
                        cout << V[i][j] << setw(12);
                    }
                cout << endl;
                }

                break;
            }






    }

     /*
        V1  V4  V4  V4  V3
        V1  0   0   0   V3
        V1  0   0   0   V3
        V1  0   0   0   V3
        V1  V2  V2  V2  V3

*/




return 0;

}

