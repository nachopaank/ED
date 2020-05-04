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
 * Estudiante 1:IGNACIO DE LA CRUZ CRESPO
 * Estudiante 2:MOHAMMED EL MESSAOUDI
 */


#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <map>
#include <set>

using namespace std;



bool tratar_caso() {
	int n;
	cin >> n;
	if (n != 0) {
		
		map< int, unordered_set<string>> mapa;
		map<string,int> s;
		for (int i = 0; i < n; i++) {
			unordered_set<string> nombres;
			string id;
			
			cin >> id;
			
			int p;
			cin >> p;
			while (p != 0) {
				s[id]++;
				if (mapa.count(p) == 0) {
					nombres.insert(id);
					mapa.insert(pair<int, unordered_set<string>>(p, nombres));
				}
				else {
					mapa[p].insert(id);
				}
				cin >> p;
			}
			
			

		}
		bool b = true;
		int f;
		
		cin >> f;
		while (b) {
			if (mapa.count(f) == 1) {
				auto it2 = mapa[f].begin();

					while (it2 != mapa[f].end()) {
						if (s.count((*it2)) == 1) {
							s[(*it2)]--;
						}
						if (s[(*it2)] == 0) {
							b = false;
						}
						it2++;
					}
					mapa.erase(f);
			}
			if (b) {
				cin >> f;
			}
		}
		
		
		for (auto it : s) {
			if (it.second == 0) {
				cout << it.first << " ";
			}
		}
		cout << endl;
	    return true;
	}
	else {
		return false;
	}
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
