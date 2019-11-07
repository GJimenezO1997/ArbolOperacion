#include <iostream>
#include <cstdlib>
#include <string.h>
#include <cmath>
#include <stack>
#include <ctype.h>
#include <string>
#include <cstring>
#include <conio.h>

using namespace std;

struct nodo{
     char nro;
     struct nodo *izq, *der;
};

typedef struct nodo *A;
int prioridad(char op) {
 	switch (op) {
  		case '^': return 3;
  		case '*':
 	 	case '/': return 2;
  		case '+': 
  		case '-': return 1;
  		case ')': return -1;
  		default: return 0;
 	}
} 
string convertir(string in) {
 	stack<char> pila;
 	string posf = "";
 	for (int i=0; i < in.size(); i++) {
  		switch (in[i]) {
   			case '(':
    			pila.push('(');
    		break;
   			
			case ')':
   				 while (!pila.empty() && pila.top() != '(') {
     				posf += string(1,pila.top()) + " ";
     				pila.pop();
    			}
   			pila.pop();
    		break;
    		
   			case '+':
   			case '-':
   			case '*':
   			case '/':
   			case '^':
				while (!pila.empty() && prioridad(in[i]) <= prioridad(pila.top())) {
     				posf += string(1,pila.top()) + " ";
     				pila.pop();
    			}
    			pila.push(in[i]);
    		break;
  			default:
   				 while (isdigit(in[i]) || in[i] == '.') 
     				posf += string(1, in[i++]);
    				posf += " ";
    				i--;
  		}
 	}
	
	while (!pila.empty()) {
  		posf += string(1, pila.top()) + " ";
  		pila.pop();
 	}
 	return posf;
}

double evaluar(string p) {
 	stack<double> pila;
 	double op1, op2;
 	
	for (int i=0; i < p.size(); i+=2) {
  		switch (p[i]) {
   			case '^':
    			op2 = pila.top(); pila.pop();
    			op1 = pila.top(); pila.pop();
   			 	pila.push(pow(op1, op2));
    		break;
   			
			case '*':
    			op2 = pila.top(); pila.pop();
    			op1 = pila.top(); pila.pop();
    			pila.push(op1*op2);
    		break;
   			
			case '/':
    			op2 = pila.top(); pila.pop();
    			op1 = pila.top(); pila.pop();
    			pila.push(op1 / op2);
    		break;
    		
   			case '+':
    			op2 = pila.top(); pila.pop();
    			op1 = pila.top(); pila.pop();
    			pila.push(op1 + op2);
    		break;
   			
			case '-':
    			op2 = pila.top(); pila.pop();
    			op1 = pila.top(); pila.pop();
    			pila.push(op1 - op2);
    		break;
   			
			default:
    			string aux = "";
    			while (p[i] != ' ')
     			aux += string(1, p[i++]);
    			pila.push(atof(aux.c_str()));
    			i--;
  		}
 	}
 	return pila.top();
}

A crearNodo(char x){
     A nuevoNodo = new(struct nodo);
     nuevoNodo->nro = x;
     nuevoNodo->izq = NULL;
     nuevoNodo->der = NULL;

     return nuevoNodo;
}
float insertar(A &arbol, char x)
{
     if(arbol==NULL)
     {
           arbol = crearNodo(x);
     }
     

	else if(x <= arbol->nro)
         insertar(arbol->izq, x);
     else if(x >= arbol->nro)
       insertar(arbol->der, x);
   else if(x<=arbol->nro || x>arbol->nro){ 
   switch (x){
          
          case '+':
return (insertar(arbol->izq,x) + insertar(arbol->der,x));
break;
case '-':
return (insertar(arbol->izq,x) - insertar(arbol->der,x));
break;
case '*':
return (insertar(arbol->izq,x) * insertar(arbol->der,x));
break;
case '/':
return (insertar(arbol->izq,x) / insertar(arbol->der,x));
break;
}
      
}
}

void postorden(A arbol)
{
     if(arbol!=NULL){
	 	postorden(arbol->der);
	 	cout << arbol->nro << " ";
          
          postorden(arbol->izq);
		  
         
           
		  
     }
}
float evaluar (A arbol) {

switch (arbol->nro) {
case '+':
return (evaluar(arbol->izq) + evaluar(arbol->der));
break;
case '-':
return (evaluar(arbol->izq) - evaluar(arbol->der));
break;
case '*':
return (evaluar(arbol->izq) * evaluar(arbol->der));
break;
case '/':
return (evaluar(arbol->izq) / evaluar(arbol->der));
break;
}
}


int main()
{
    A arbol = NULL; 
    int n,i,j,f;  
    string x;
    string p;
	char tecla;
	char *k=new char;
    do{
	
	cout <<"\n Ingresa la ecuacion a evaluar: ";
    cin >> x;
	p = convertir(x);
	
	char *y=strdup(x.c_str());
	i = 0;
	j = 0;
  	while (y[i] != '\0'){
    	if ('('!= y[i]&& ')'!= y[i]){
   			k[j] = y[i];
			j++;
		}
		i++;
	}
	k[j] = '\0';
	n=(strlen(k));
	for( i=0; i<n ; i++)
    {
		insertar( arbol, k[i]);

    }
   
    cout << "\n\n Resultado: " << evaluar(p) << endl;
    cout << endl << endl;


    
    
    tecla=getch();
	/*n=x.size();
    for( i=0; i<n ; i++)
    {
		insertar( arbol, x[i]);

    }
    cout << "\n Post Orden :  ";   
	postorden(arbol);
    cout << endl << endl;
*/}while(tecla!=27);
    return 0;
}
