#include <math.h>
#include "geometry.h"

double eq_reta(int x1, int y1, double m, int x_para_calcular){

    double y = m*(x_para_calcular-x1) + y1; //calcula o x da reta
    return y;
}

int verify(point p, point a, point b) {

    
    double m = 0; //coneficiente angular da reta partindo do ponto p
    double m_aresta = (double) (b.y - a.y)/(b.x - a.x); //coneficiente angular do segmento de reta

    //calcula o y para a equacação da reta do segmento passando p.x, caso
    //este seja igual o p.y e m = m_aresta, significa que a eq da reta é a mesma
    double y_calculado_aresta = eq_reta(a.x, a.y, m_aresta, p.x);

    double paralelismo = fabs(m - m_aresta);
    double igualidade = fabs(y_calculado_aresta - p.y);

    //se o coeficiente for o mesmo, mas os pontos não coincidirem,
    //significa que as retas são paralelas
    if(paralelismo < 0.000001 && igualidade >= 0.000001){
        return 0;
    } 

    else if(paralelismo < 0.000001 && igualidade < 0.000001){
        return 2;
    }
    
    return 1;
}

int inside(point p, point poly[], int n) {
    return 0;
}
