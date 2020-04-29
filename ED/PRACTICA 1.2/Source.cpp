
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <cassert>
using namespace std;
//COMPONENTES MOHAMMED EL MESSAOUDI Y IGNACIO DE LA CRUZ CRESPO GRUPO C

//COSTES
//Constructor :Polinomio()
//Coste constante ya que es una asignacion , de la cual sabemos que el coste esta en O(1)

//Coste de anyadir_monomio(int coef, int exp)
//El coste de añadir podemos desglosarlo en dos casos , el peor y el mejor

//En el caso peor el coste es lineal con respecto a num_monomios siendo num_monomios el numero de monomios presentes en el array ,ya que si el monomio que se quiere insertar deberia ir en  la primera posicion del array
//el bucle for correspondiente a insertar los elementos en su posición se ejecutaria num_monomios veces o en el caso en el que el coeficiente se haga cero en la primera posición hay que mover todos los elementos , por tanto el coste sera lineal con respecto a num_monomios, 
//en cambio el bucle while anterior encargado de encontrar en que posición 
//deberia ir el monomio, como máximo  es de coste logarítmico con respecto a num_monomios ya que se van descartando partes mas pequeñas del array  consecutivamente
//en esta busqueda suponemos que la posición que buscamos no se encuentra en la mitad sino en uno de los extremos
//por tanto quedaría de esta forma O(num_monomios) + O(log num_monomios) , donde num_monomios es el numero de elementos o monomios que existen en el array
//como seleccionamos el orden mas elevado el coste quedaría lineal de orden  O(num_monomios)

//En el caso mejor, suponemos que la posición del elemento a insertar corresponde exactamente con la mitad  del array y por tanto la busqueda 
//binaria implementada es de coste constante ,o(1)  ya que el elemento esta justo en la mitad y  el bucle correspondiente 
//a insertar el elemento y mover  los demas elementos no se ejecutaría ya que si ya existe un exponente en el array , solo lo actualizamos ,suponiendo eso si
//que los coeficientes no se hacen nulos y tampoco hay que mover los demas monomios.
//el coste por tanto de el método es de coste constante O(1)  .


//Coste de Polinomio::evaluar(int valor) const
//El coste de este algoritmo es lineal con respecto a num_monomios ya que el bucle se ejecuta siempre independientemente de cualquier otra condición 
//por ello el coste es de orden O(num_monomios)  donde num_monomios es el número de elementos o monomios que existen en el array .


const int MAX_MONOMIOS = 1000;
class Polinomio {
public:
	Polinomio() {
		num_monomios = 0;
	}
	void anyadir_monomio(int coef, int exp);
	long evaluar(int valor) const;
private:
	struct Monomio {
		int coeficiente;
		int exponente;
	};
	Monomio monomios[MAX_MONOMIOS];
	int num_monomios;
};



void Polinomio::anyadir_monomio(int coef, int exp) {
	//assert(0 <= num_monomios && num_monomios <= MAX_MONOMIOS);
	//assert(coef != 0 );
	bool yahayexp = false;
	bool coefsehacenulo = false;
	int ini = 0, fin = num_monomios - 1;
	while (ini < fin && !yahayexp) {
		
		int mitad = (ini + fin) / 2;
		if (monomios[mitad].exponente > exp) {
			fin = mitad - 1;
		}
		else {
			if (monomios[mitad].exponente == exp) {
				if (monomios[mitad].coeficiente + coef == 0) {//esto se comprueba porque puede darse el caso de que el coef se haga nulo por ejemplo -3x^2 +3x^2 , y hay que eliminar dicho monomio y mover los demas monomios
					coefsehacenulo = true;
					ini = mitad;
				}
				else {
					monomios[mitad].coeficiente += coef;
				}
				
				yahayexp = true;
			}
			else {
				ini = mitad + 1;
			}
		}
	}
	if (!yahayexp) {
		for (int i = num_monomios; i >= ini; i--) {
			monomios[i] = monomios[i - 1];

		}
		monomios[ini].coeficiente = coef;
		monomios[ini].exponente = exp;
		num_monomios++;
	}
	if (coefsehacenulo) {
		for (int i = ini; i <num_monomios-1; i++) {
			monomios[i] = monomios[i+1];

		}
		num_monomios--;
	}
	

}
long Polinomio::evaluar(int valor) const {
	long val = 0;
	
	for (int i = 0; i < num_monomios; i++) {
		val += monomios[i].coeficiente*pow(valor,monomios[i].exponente);

	}


	return val;


}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("Text.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int n, v;
	cin >> n >> v;
	while (n != 0) {

		Polinomio pol;

		for (int i = 0; i < n; i++) {
			int x, y;
			cin >> x;
			cin >> y;
			pol.anyadir_monomio(x, y);
		}
		cout << pol.evaluar(v) << endl;
		cin >> n >> v;
	}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}