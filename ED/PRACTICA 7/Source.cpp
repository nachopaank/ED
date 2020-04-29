/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no será corregida.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */


  /*@ <answer> */

  /*
   * Comienza poniendo el nonmbre de los/as componentes del grupo:
   *
   * Estudiante 1:MOHAMMED EL MESSAOUDI
   * Estudiante 2:IGNACIO DE LA CRUZ CRESPO
   */

   /*@ </answer> */



#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>


/*
  Implementación de la clase BinTree para representar árboles binarios.

  Para realizar este ejercicio no es necesario modificar la clase.
 */

template<class T>
class BinTree {
public:

	BinTree() : root_node(nullptr) { }

	BinTree(const T &elem) : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) { }

	BinTree(const BinTree &left, const T &elem, const BinTree &right)
		:root_node(std::make_shared<TreeNode>(left.root_node, elem, right.root_node)) { }


	bool empty() const {
		return root_node == nullptr;
	}

	const T & root() const {
		assert(root_node != nullptr);
		return root_node->elem;
	}

	BinTree left() const {
		assert(root_node != nullptr);
		BinTree result;
		result.root_node = root_node->left;
		return result;
	}

	BinTree right() const {
		assert(root_node != nullptr);
		BinTree result;
		result.root_node = root_node->right;
		return result;
	}

	void display(std::ostream &out) const {
		display_node(root_node, out);
	}

private:
	struct TreeNode;
	using NodePointer = std::shared_ptr<TreeNode>;

	struct TreeNode {
		TreeNode(const NodePointer &left, const T &elem, const NodePointer &right) : elem(elem), left(left), right(right) { }

		T elem;
		NodePointer left, right;
	};

	NodePointer root_node;

	static void display_node(const NodePointer &root, std::ostream &out) {
		if (root == nullptr) {
			out << ".";
		}
		else {
			out << "(";
			display_node(root->left, out);
			out << " " << root->elem << " ";
			display_node(root->right, out);
			out << ")";
		}
	}

};

/*
 * Operador << para mostrar un árbol por pantalla. No es necesario mostrar árboles
 * por pantalla en la práctica, pero os lo dejo por si queréis depurar.
 */
template<typename T>
std::ostream & operator<<(std::ostream &out, const BinTree<T> &tree) {
	tree.display(out);
	return out;
}


/*
 * Función para leer un árbol binario de la entrada. El formato es el siguiente:
 *
 *  Árbol vacío: .
 *  Árbol no vacío: (i x r)  donde i es la representación del hijo izquierdo
 *                                 x es la raíz
 *                                 r es la representación del hijo derecho
 */
template<typename T>
BinTree<T> read_tree(std::istream &in) {
	char c;
	in >> c;
	if (c == '.') {
		return BinTree<T>();
	}
	else {
		assert(c == '(');
		BinTree<T> left = read_tree<T>(in);
		T elem;
		in >> elem;
		BinTree<T> right = read_tree<T>(in);
		in >> c;
		assert(c == ')');
		BinTree<T> result(left, elem, right);
		return result;
	}
}



/*@ <answer> */

/* Completa a continuación la función pedida. Puedes definir las funciones
   auxiliares que necesites, ¡pero siempre antes de la etiqueta </answer>! */

using namespace std;
bool hoja(const BinTree<int> & montanya) {
	return montanya.left().empty() && montanya.right().empty();
}
int  max_hitos(const BinTree<int> & montanya,int &max) {

	int maxx = 0;
	int maxhitos = 0;
	int maxhitos2 = 0;
	if (!montanya.left().empty()) {
		maxhitos = maxx + max_hitos(montanya.left(), max);
	}
	if(!montanya.right().empty()){
	     maxhitos2 = maxx + max_hitos(montanya.right(), max);
	 
	}
	if (maxhitos + maxhitos2 +1> max) {
	    max = maxhitos + maxhitos2+1;
	}
	if (maxhitos >= maxhitos2) {
		maxx = maxhitos;
	}
	else {
		maxx = maxhitos2;
	
	}
	 maxx++;
	 return maxx;

}
int max_hitos_visitados(const BinTree<int> &montanya) {

	int mx =0;
	
	int bs=max_hitos(montanya, mx);
	return mx;
}

//COSTE ARBOL EQUILIBRADO
//La recurrencia de este caso es la siguiente , donde n denota el número de nodos del árbol y  las k son constantes y donde n=ni+nj +1,ni y nj es el número de nodos de los dos hijos
//      |k1 si n=0
//T(n) =|
//      |
//      |T(ni) +T(nj) +k2 si n>0
//Es decir el coste de esta función es lineal con respecto al número de nodos del árbol , T(n) por inducción sabemos que el coste es lineal

//COSTE EL ARBOL DEGENERADO
//La recurrencia de este caso es la siguiente , donde n denota el número de nodos del arbol y  las k son constantes 
//      |k1 si n=0
//T(n) =|
//      |
//      |T(n) +k2 si n>0
//En este caso aunque el árbol sea degenerado se recorren igualmente el número de nodos totales del arbol , T(n) por inducción sabemos que el coste es lineal

/*@ </answer> */


bool tratar_caso() {
	BinTree<int> montanya = read_tree<int>(cin);
	if (montanya.empty()) return false;

	cout << max_hitos_visitados(montanya) << "\n";

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