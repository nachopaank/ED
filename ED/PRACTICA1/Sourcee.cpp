
#include <iostream>
#include <fstream>
using namespace std;
//COMPONENTES MOHAMMED EL MESSAOUDI Y IGNACIO DE LA CRUZ CRESPO GRUPO C
const int GRADO_MAX = 5000;

//-----------------------COSTES------------------------------
//3.
//Polinomio()  
//Coste del constructor:Polinomio()
//el coste es lineal con respecto a GRADO_MAX ,ya que existe un bucle iterativo que recorre todas las posiciones del vector de tamaño GRADO_MAX
//asignando el valor 0 , por ello el coste esta en el orden de O(GRADO_MAX) donde GRADO_MAX es el grado maximo que puede tener un polinomio en este caso

//Coste de  void Polinomio::anyadir_monomio(int coef, int exp)
//El coste de este método es constante ya que como sabemos las asginaciones y accesos son de coste constante y por tanto podemos decir que es del orden de O(1)
//al solo existir este tipo de operaciones en el método.

//Coste de  long Polinomio::evaluar(int valor) const 
//Podemos observar que el coste de este metodo es lineal con respecto a GRADO_MAX siendo GRADO_MAX el maximo grado de un polinomio , esto se debe a que el bucle que existe
//en el método se ejecuta siempre GRADO_MAX veces en cualquier caso , recorriendo el bucle de principio a fin, por tanto podemos decir que esta en O(GRADO_MAX)
//las demas operaciones del método son constantes , por ello el coste en el caso peor y mejor es el mismo , O(GRADO_MAX)

class Polinomio {
public:
	Polinomio() {
		for (int i = 0; i < GRADO_MAX; i++) {
			coeficientes[i] = 0;
		}


	}

	void anyadir_monomio(int coef, int exp);
	long evaluar(int valor) const;
private:
	int coeficientes[GRADO_MAX];


};
//1.
void Polinomio::anyadir_monomio(int coef, int exp) {
	coeficientes[exp] += coef;



}
//2.
long Polinomio::evaluar(int valor) const {
	long val = 0;
	long ii = 1;
	for (int i = 0; i < GRADO_MAX; i++) {

		val += (coeficientes[i] * (ii));
		ii = ii * valor;

	}
	return val;
}
//4.
int main() {
	
#ifndef DOMJUDGE
	std::ifstream in("Text.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int n, v;
	cin >> n >> v;
	while (n != 0 ) {

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