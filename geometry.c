#include <math.h>
#include "geometry.h"
#include <stdio.h>

int min(int x, int y){
  return (x < y) ? x : y;
}

int max(int x, int y){
  return (x > y) ? x : y;
}

point retorna_menor_ponto(point a, point b){

    if (a.x < b.x){
        return a;
    }
    return b;
}

point retorna_maior_ponto(point a, point b){

    if(a.x < b.x){
        return b;
    }

    return a;
}

double eq_reta(int x1, int y1, double m, int x_para_calcular){

    double y = (double) m*(x_para_calcular-x1) + y1; //calcula o x da reta
    return y;
}

int verify(point p, point a, point b) {
    
    double m = 0; //coneficiente angular da reta partindo do ponto p
    double m_aresta = (double) (b.y - a.y)/(b.x - a.x); //coneficiente angular do segmento de reta

    //calcula o y para a equacação da reta do segmento passando p.x, caso
    //este seja igual o p.y e m = m_aresta, significa que a eq da reta é a mesma
    double y_calculado_aresta = (double) eq_reta(a.x, a.y, m_aresta, p.x);

    double paralelismo = (double)fabs(m - m_aresta);  // se m do robô é igual ao m da aresta
    double igualidade =  (double)fabs(y_calculado_aresta - p.y); // se ponto p está na aresta 

    point menor_ponto = retorna_menor_ponto(a, b);
    point maior_ponto = retorna_maior_ponto(a, b);

    //1 - > nao é igual

   // printf("verifica: %d\n", igualidade >= 0.000001);

    // ------------------------------------- CASOS ESPECÍFICOS ------------------------------------- 

    if(igualidade < 0.000001 && p.x >= menor_ponto.x && p.x <= maior_ponto.x){
        return 2;
    }


    //se o coeficiente for o mesmo, mas os pontos não coincidirem, significa que as retas não tem intersecção (check)
    else if(paralelismo < 0.000001 && p.x > maior_ponto.x){
        return 0;
    } 

    //se as retas são paralelas e p está na mesma direção da aresta mas não sobre ela, existe intersecção (check)
    else if(paralelismo < 0.000001 && p.x < menor_ponto.x && p.y == menor_ponto.y){
        return 0;
    }

    //casos verticais
    else if (a.x == b.x){
       // printf("vertical \n");
        //reta ta na mesmo x que o ponto
        if(b.x == p.x){
            //p tem que estar entre o maior e o menor valor de a e b
           if(p.y<=max(b.y,a.y) && p.y>= min(b.y,a.y)){
               return 2;
           }
           else{
               return 0; //nao ta no intervalo
           }
        }else{
            //verficar se esta na direita (0) ou na esquerda-> verifica se esta no intervalo de y 
            if(p.x > b.x){
                return 0; //esta na direita 
            }else{
                //esta na esquerda 
                if(p.y <= max(b.y,a.y) && p.y > min(b.y,a.y)){
                    return 1;
                }
                else{
                    return 0; //nao ta no intervalo
                }

            }
        }
    }

    // ---------------------------------------------------------------------------------------------

    // ------------------------------------- CASOS GERAIS -------------------------------------

    else{

        //verificar se as retas se cruzam

        //minimo valor de x para a aresta
        int aresta_x_min = min(a.x, b.x);

        //maximo valor de x para a aresta
        int aresta_x_max = max(a.x, b.x);

        //minimo valor de x para raio do robô
        int robo_x_min = p.x;

        //maximo valor de x para raio do robô
        int robo_x_max = 2147483647;

        //robo ta a direita da aresta
        if(robo_x_min > aresta_x_min && aresta_x_max < robo_x_min){
            return 0;
        }

        //y = A*x + b

        //equacao da reta robo 
        double b1 = (double) p.y;

        //equacao da reta para a aresta 
        double b2 = (double) a.y - m_aresta*a.x;

        //para intersectar o X deve ser igual nas duas equacoes
        double xc =  (double) ((b2-b1)/(-m_aresta));

        //para possuir intersecção (ponto A), precisamos que o x de A
        //esteja contido no intervalo entre do menor x e o maior x para
        //as duas retas

        int cx_min = max(aresta_x_min, robo_x_min);
        int cx_max = min(aresta_x_max, robo_x_max);
        
        double xa_double = (double)a.x;
        double xb_double = (double)b.x;
        double dif_xc_xa = (double) fabs(xa_double -xc);
        double dif_xc_xb = (double) fabs(xb_double -xc);


        if(xc > cx_max || xc < cx_min){
            return 0;
        }
        else if((dif_xc_xa < 0.000001 && a.y>b.y)|| (dif_xc_xb < 0.000001  && b.y>a.y)){
           // printf("entrou aqui \n");
            return 1;
            
        }
        else if ((dif_xc_xa < 0.000001 && a.y<b.y) || (dif_xc_xb < 0.000001  && b.y<a.y)){
            return 0;
        }


        else if (xc>cx_min && xc<cx_max){
            return 1;
        }
    }

    // ----------------------------------------------------------------------------------------
    return 0;
}

int inside(point p, point poly[], int n) {
    int resposta;   
    int numeros_de_um = 0;

    //percorre o vetor de arestas e chama a funcao verify para ver oque ela devolve e coloca no veotr respsta
    for(int i =0; i<n; i++){
        if(i==(n-1)){
            resposta= verify(p,poly[i],poly[0]);
        }else{
            resposta = verify(p,poly[i],poly[i+1]);
        }
        if(resposta==2){
            //se tiver algum 2 retorna dentro
            return 1;
        }
        else if(resposta==1){
            //se tiver 1 soma um em numeors_de_um
            numeros_de_um+=1;
        }
    }

    if(numeros_de_um%2 != 0){
        //se a quantidade de uns for par devolve fora
        return 1;
    }
    else{
        return 0;
    }
    

    return 0;
}
