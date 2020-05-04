/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 * Indica el nombre y apellidos de los componentes del
 * grupo:
 *
 * Nombre 1:MOHAMMED EL MESSAODUI
 * Nombre 2:IGNACIO DE LA CRUZ
 * ---------------------------------------------------
 */



#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cassert>
#include <sstream>

using namespace std;
class Date {
public:
	Date() {
		this->dia = 1;
		this->mes = 1;
		this->year = 2000;
	}
	Date(int day, int month, int year) :dia(day), mes(month), year(year) {

	}

	bool operator<(const Date &other) const {
		if (this->year < other.year) {
			return true;
		}
		else {
			if (this->year == other.year) {
				if (this->mes < other.mes) {
					return true;
				}
				else {
					if (this->mes == other.mes) {
						if (this->dia < other.dia) {
							return true;
						}
					}
				}

			}
		}
		return false;
	}

	bool operator<=(const Date &other) const {
		if (this->year == other.year && this->dia==other.dia && this->mes==other.mes) {
			return true;
		}
		else {
			if (*this < other) {//llamo al otro operator< 
				return true;
			}
		}
		return false;
	}


	void read(istream &in) {
		
		char separador;

		in >> this->dia>>separador>>this->mes>>separador>>this->year;
		
	}

private:
	 int dia;
	 int mes;
	 int year;
};
istream & operator>>(istream &in, Date &f) {
	f.read(in);
	return in;
}


class FamilyTree {
public:
	FamilyTree() {
		root = nullptr;
	}
	~FamilyTree() {
		
		deleteMemory(*this->root);
		delete this->root;
		
	}
	void read(std::istream &in) {
		this->root = node(in);

	}
	
	
	bool nonsense() {

		
		return non(this->root);
	}
	
private:
	struct FamilyTreeNode {
		Date date;
		std::vector<FamilyTreeNode *> children;
	};
	bool non(FamilyTreeNode * dt) {
		auto it = dt->children.cbegin();
	
		while (it != dt->children.end() ) {
			if (dt->date< (*it)->date ) {
				if(!non(*it)) {
					return false;
				}
			}else{
				return false ;
			}
			it++;
		}
		return true;
	}
	FamilyTreeNode *node(istream &in) {
		FamilyTreeNode * dt = new FamilyTreeNode();
	   dt->date.read(in);
	   int n;
	   in >> n;
	   for (int i = 0; i < n; i++) {
		   
		   dt->children.push_back(node(in));
	   }
	   return dt;
	}
	void deleteMemory(FamilyTreeNode  &dt) {
		if (dt.children.empty()) {

		}
		else {
			for (int i = 0; i < dt.children.size(); i++) {
				deleteMemory( *dt.children.at(i));
				delete dt.children.at(i);
			}
			
		}
	}

	FamilyTreeNode *root;
};

std::istream & operator>>(std::istream &in, FamilyTree &f) {
	f.read(in);
	return in;
}


using namespace std;

void tratar_caso() {
	FamilyTree arbol;
	arbol.read(cin);
	if (!arbol.nonsense()) {
		cout << "SI" << endl;
	}else {
		cout << "NO" << endl;
	}
}
//COSTE
//El coste de la funci�n nonsense podemos decir que tiene un coste cuadr�tico con respecto al n�mero de nodos que esten entre el primer nivel y el �ltimo ,ya que se 
//visita cada nodo como m�ximo dos veces , esto es asi en el caso en el que un padre tenga nietos , es decir, habr�a que comparar la fecha del padre con la del hijo ,y 
//a su vez la fecha de este con la de su hijo , accediendo dos veces .
//Por ejemplo si tuviesemos este �rbol
//         JUAN
//   PACO    LUCIA   LEIRE
//   ALFREDO          PEDRO
//Habr�a que acceder a la fecha de Juan y Paco ,despues habr�a que comparar a Paco y Alfredo...
//Por lo que se acceder�a a Paco dos veces.
//El coste es cuadr�tico segun el n�mero de nodos mencionado anteriormente , ya que al padre(la raiz del �rbol) solo se le visita 1 vez ,adem�s ocurre que a la �tima generaci�n de la familia
//no se accede a su fecha mas de una vez ya que no hay mas descendientes con los que comparar.

int main() {
#ifndef DOMJUDGE
	std::ifstream in("ED/PRACTICA6/Text.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int num_casos;
	cin >> num_casos;
	for (int i = 0; i < num_casos; i++) {
		tratar_caso();
	}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	 system("PAUSE");
#endif
	
	return 0;
}
