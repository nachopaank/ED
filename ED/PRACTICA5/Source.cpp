/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 * Indica el nombre y apellidos de los componentes del
 * grupo:
 *
 * Nombre 1:MOHAMMED EL MESSAOUDI
 * Nombre 2:IGNACIO DE LA CRUZ
 * ---------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <list>


using namespace std;


bool es_toeplitz(const list<list<int>> &matriz) {
	auto  it = cbegin(matriz);
	
	auto  it2 =it;
	it2++;//para coger la siguiente fila
	

	while (it2 != cend(matriz)) {
		 auto fila=cbegin((*it));
		
		auto fila2 = cbegin((*(it2)));
		fila2++;//para coger la siguiente columna  de la siguiente fila
		while(fila2 != cend((*it2))) {
		
			if (*fila != *fila2) {
				return false;
			}

			fila++;
			fila2++;
		 }

		it2++;
		it++;
	}
	return true;
}
//COSTE
//El coste de este algoritmo en el caso peor es cuadratico con respecto a la matriz de entrada ,ya que se ejecuta n*m veces donde n y m es el numero de filas y columnas 
//de la matriz , el caso peor podemos definirlo como aquel en el que la diagonal que se encuentra en la parte inferior izquierda como por ejemplo este caso:
/*8 6 1 6 5 0
  9 8 6 1 6 0
  [3] 9 8 6 1 0
  7 [4] 9 8 6 0
  */
//La diagonal diferente se encuentra al final de la matriz ( el 3 y 4) ,forzando al algoritmo ha realizar n*m vueltas en los bucles del algoritmo,
//por tanto el coste esta en el orden de O(n^m) tomando como referencia la matriz ,donde n y m es el numero de filas y columnas de la matriz 
bool tratar_caso() {
	int n;
	int cas;
	list<list<int>> matriz;
	cin >> n;
	cas = n;
	
	if (n != 0) {
	
		while (cas != 0) {
			list<int> fila;
			n = cas;
			while (n != 0) {
				fila.push_back(n);
				cin >> n;
			}
			matriz.push_back(fila);
			cin >> cas;
		}
		if (es_toeplitz(matriz)) {
			cout << "SI" << endl;
		}
		else {
			cout << "NO" << endl;
		}
		
		
	}
	else {
		return false;
	}
	
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("ED/PRACTICA5/Text.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	 system("PAUSE");
#endif

	return 0;
}