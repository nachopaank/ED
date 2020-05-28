/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
 * Comienza poniendo el nombre de los/as componentes del grupo:
 *
 * Estudiante 1:MOHAMMED EL MESSAOUDI
 * Estudiante 2:IGNACIO DE LA CRUZ CRESPO
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>
using namespace std;

class Supermercado {
public:
	Supermercado( int  num_cajas) {
		cajas = new vector<list<string>>(num_cajas);
		//coste costante, creación de un array en el heap
	}
	~Supermercado() {
		delete cajas;
	}
	void nuevo_cliente(string cod_cliente,int  num_cola) {
		if (num_cola<0 || num_cola>cajas->size() - 1) {
			throw domain_error("Cola inexistente");
	    }
		if (clientes.count(cod_cliente) == 1) {
			throw domain_error("Cliente duplicado");
		}
		cajas->at(num_cola).push_back(cod_cliente);
		clientes[cod_cliente] = num_cola;
		auto it = cajas->at(num_cola).end();
		it--;
		clienteIt[cod_cliente] = it;
		//Coste constante ya que todas las operaciones ya sean de unordered_map o de listas son constantes según las librerias STL , O(1)

	}
	void cambiar_cola(string cod_cliente,int num_cola) {
		if (num_cola<0 || num_cola>(cajas->size() - 1)) {
			throw domain_error("Cola inexistente");
		}
		if (clientes.count(cod_cliente) == 0) {
			throw domain_error("Cliente inexistente");
		}
		if (clientes[cod_cliente] != num_cola) {
			cajas->at(clientes.at(cod_cliente)).erase(clienteIt.at(cod_cliente));
			cajas->at(num_cola).push_back(cod_cliente);
			auto it = cajas->at(num_cola).end();
			it--;
			clienteIt[cod_cliente] = it;
			clientes[cod_cliente] = num_cola;
		}
		//Coste constante ya que todas las operaciones ya sean de unordered_map o de listas son constantes según las librerias STL , O(1)
	}
	int consultar_cliente(string cod_cliente) {
		if (clientes.count(cod_cliente) == 0) {
			throw domain_error("Cliente inexistente");
		}
		return clientes[cod_cliente];
		//Coste constante ya que es un unordered_map y por tanto el coste es amortizado constante , implementado mediante tablas hash O(1)
	}
	int  cuantos_en_cola(int num_cola) {
		if (num_cola<0 || num_cola>cajas->size() - 1) {
			throw domain_error("Cola inexistente");
		}
		return cajas->at(num_cola).size();
		//Coste constante , acceso y metodo size presentan coste constante O(1)
	}
	list<string> clientes_en_cola(int num_cola) {
		if (num_cola<0 || num_cola>cajas->size() - 1) {
			throw domain_error("Cola inexistente");
		}
		list<string> s;
		auto it = cajas->at(num_cola).cend();
		if (!cajas->at(num_cola).empty()) {
			it--;
		}
		for (int i = 0; i < cajas->at(num_cola).size(); i++) {
			s.push_back((*it));
			if (it != cajas->at(num_cola).cbegin()) {
				it--;
			}
		}
		return s;
		////Coste lineal debido al recorrido para insertarlos en orden inverso , por lo tanto coste O(n) donde n es el numero de clientes en la cola (num_colas)
	}

private:
	
	unordered_map<string, int> clientes;
	unordered_map<string, list<string>::iterator> clienteIt;
	vector<list<string>> *cajas;
	
};


bool tratar_caso() {
	int n;
	cin >> n;
	if(!cin.eof()){
		string p;
		cin >> p;
		Supermercado super(n);
		while (p != "FIN") {
			try {
				if (p == "nuevo_cliente") {
					string id;
					int num;
					cin >> id >> num;
					super.nuevo_cliente(id, num);
				}
				else if (p == "cuantos_en_cola") {
					int num;
					cin >> num;
					int cont = super.cuantos_en_cola(num);
					cout << "En la cola " << num << " hay " << cont << " clientes" << endl;
				}
				else if (p == "clientes_en_cola") {
					int num;
					cin >> num;
					string resul ="";
					if (super.cuantos_en_cola(num) > 0) {
						resul += " ";
					}
					for(auto it: super.clientes_en_cola(num)){


						resul += (it)+" ";
					}
					cout << "En la cola " << num << " estan:" << resul << endl;
				}
				else if (p == "cambiar_cola") {
					string id;
					int n;
					cin >> id >> n;
					super.cambiar_cola(id, n);
				}
				else if (p == "consultar_cliente") {
					string id;
					cin >> id;
					int num = super.consultar_cliente(id);
					cout << "El cliente " << id << " esta en la cola " << num << endl;
				}
			}
			catch (exception & e) {
				cout << "ERROR: " <<e.what() << endl;
			}
			cin >> p;

			
		}
		cout << "---" << endl;
	}
	else {
		return false;
	}
	return true;
}



int main() {
#ifndef DOMJUDGE
	std::ifstream in("Text.txt");
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
