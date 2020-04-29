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
   * Comienza poniendo el nombre de los/as componentes del grupo:
   *
   * Estudiante 1:MOHAMMED EL MESSAOUDI
   * Estudiante 2:IGNACIO DE LA CRUZ CRESPO
   */

   /*@ </answer> */


#include <iostream>
#include <cassert>
#include <fstream>

/*
 * Implementación del TAD Conjunto mediante ABBs
 */
template <typename T>
class SetTree {
public:
	SetTree() : root_node(nullptr), num_elems(0) { }
	SetTree(const SetTree &other) : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) { }
	~SetTree() {
		delete_nodes(root_node);
	}

	void insert(const T &elem) {
		bool inserted = insert(root_node, elem);
		if (inserted) { num_elems++; }
	}

	bool contains(const T &elem) const {
		return search(root_node, elem);
	}

	void erase(const T &elem) {
		bool removed = erase(root_node, elem);
		if (removed) { num_elems--; }
	}

	int size() const {
		return num_elems;
	}

	bool empty() const {
		return num_elems == 0;
	}

	// Esta es la función que tienes que implementar. Aquí solo
	// está declarada. Tienes que implementarla más abajo, después
	// de la declaración de la clase SetTree.
	int elems_in_interval(const T &lower, const T &upper) const;

	

	SetTree & operator=(const SetTree &other) {
		if (this != &other) {
			num_elems = other.num_elems;
			delete_nodes(root_node);
			root_node = copy_nodes(other.root_node);
		}
		return *this;
	}

	void display(std::ostream &out) const {
		out << "{";
		display(root_node, out);
		out << "}";
	}

private:
	struct Node {
		T elem;
		Node *left, *right;

		Node(Node *left, const T &elem, Node *right) : left(left), elem(elem), right(right) { }
	};

	Node *root_node;
	int num_elems;

	static Node *copy_nodes(const Node *node) {
		if (node == nullptr) {
			return nullptr;
		}
		else {
			return new Node(copy_nodes(node->left), node->elem, copy_nodes(node->right));
		}
	}

	static void delete_nodes(const Node *node) {
		if (node != nullptr) {
			delete_nodes(node->left);
			delete_nodes(node->right);
			delete node;
		}
	}

	static bool insert(Node * &root, const T &elem) {
		if (root == nullptr) {
			root = new Node(nullptr, elem, nullptr);
			return true;
		}
		else if (elem < root->elem) {
			return insert(root->left, elem);
		}
		else if (root->elem < elem) {
			return insert(root->right, elem);
		}
		else {
			return false;
		}
	}

	static bool search(const Node *root, const T &elem) {
		if (root == nullptr) {
			return false;
		}
		else if (elem == root->elem) {
			return true;
		}
		else if (elem < root->elem) {
			return search(root->left, elem);
		}
		else {
			return search(root->right, elem);
		}
	}

	static bool erase(Node * &root, const T &elem) {
		if (root == nullptr) {
			return false;
		}
		else if (elem < root->elem) {
			return erase(root->left, elem);
		}
		else if (root->elem < elem) {
			return erase(root->right, elem);
		}
		else {
			remove_root(root);
			return true;
		}
	}

	static void remove_root(Node * &root) {
		Node *left_child = root->left, *right_child = root->right;
		delete root;
		if (left_child == nullptr && right_child == nullptr) {
			root = nullptr;
		}
		else if (left_child == nullptr) {
			root = right_child;
		}
		else if (right_child == nullptr) {
			root = left_child;
		}
		else {
			Node *lowest = remove_lowest(right_child);
			lowest->left = left_child;
			lowest->right = right_child;
			root = lowest;
		}
	}


	static Node * remove_lowest(Node * &root) {
		assert(root != nullptr);
		if (root->left == nullptr) {
			root = root->right;
			return root;
		}
		else {
			return remove_lowest(root->left);
		}
	}

	static void display(Node *root, std::ostream &out) {
		if (root != nullptr) {
			if (root->left != nullptr) {
				display(root->left, out);
				out << ", ";
			}
			out << root->elem;
			if (root->right != nullptr) {
				out << ", ";
				display(root->right, out);
			}
		}
	}


	// Si necesitas declarar más funciones auxiliares, hazlo aquí, pero
	// luego impleméntalas abajo, entre las etiquetas <answer> y </answer>    
	void interval( Node *  tree, const T & lower, const T & upper,T & elem) const;
};

template <typename T>
std::ostream & operator<<(std::ostream &out, const SetTree<T> &set) {
	set.display(out);
	return out;
}

// ===============================================================================================
/*@ <answer> */

template <typename T>
int SetTree<T>::elems_in_interval(const T &lower, const T &upper) const {
	T elem=NULL;
	 interval(root_node, lower, upper,elem);
	 return elem;
}
template <typename T>
void SetTree<T>::interval(  Node *  tree, const T & lower, const T & upper,T &elem) const {
	if (tree == nullptr) {
		
	}
	else {
		if (tree->elem>=upper) {
			if (tree->elem == upper) {
				elem++;
			}
			interval(tree->left, lower, upper, elem);


		}
		else {
			if (tree->elem < lower) {
				interval(tree->right, lower, upper, elem);
			}
			else {
				elem++;
				interval(tree->left, lower, tree->elem, elem);
				interval(tree->right, tree->elem, upper, elem);
			}
		}
	}




}
// Implementa aquí los métodos auxiliares que hayas declarado en la clase.

/*@ </answer> */
// ===============================================================================================


using namespace std;

bool tratar_caso() {
	// Leemos los dos primeros números (N y M según el enunciado).
	int num_elems, num_consultas;
	cin >> num_elems >> num_consultas;
	if (cin.eof()) {
		return false;
	}

	// Construimos el conjunto
	SetTree<int> conjunto;

	for (int i = 0; i < num_elems; i++) {
		int elem;
		cin >> elem;
		conjunto.insert(elem);
	}

	// Ejecutamos las consultas
	for (int i = 0; i < num_consultas; i++) {
		// Leer cota inferior y superior
		int lower, upper;
		cin >> lower >> upper;

		// Llamar a la función implementada en el ejercicio e imprimir el resultado
		cout << conjunto.elems_in_interval(lower, upper) << "\n";
	}
	cout << "---\n";
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
