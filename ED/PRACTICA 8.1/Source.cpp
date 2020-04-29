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
#include <fstream>
#include <memory>
#include <cassert>


/*
  Implementación de la clase BinTree para representar árboles binarios.
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
		BinTree<T> result;
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
	// Las definiciones de TreeNode y NodePointer dependen recursivamente
	// la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
	// para que el compilador sepa, cuando analice la definición de NodePointer,
	// que TreeNode va a ser definida más adelante.

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
 * Operador << para mostrar un árbol por pantalla. No es necesario hacer esto
 * en la práctica, pero os lo dejo por si queréis depurar.
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

using namespace std;

// ===============================================================================================
/*@ <answer> */

template <typename T>
bool binary_search_tree(const BinTree<T> &tree) {
	T a, b;
	return binary(tree,a,b);
}
template <typename T>
int minn(T x, T y) {
	if (x > y) {
		return y;
	}
	else {
		return x;
	}
}
template <typename T>
int maxx(T x, T y) {
	if (x < y) {
		return y;
	}
	else {
		return x;
	}
}
template <typename T>
bool binary(const BinTree<T> & root,T & min,T & max) {

	
	T maxi, mini, maxder , minder;
	if (root.empty()|| (root.left().empty() && root.right().empty())) {
		if (!root.empty() &&(root.left().empty() && root.right().empty())) {
			max = root.root();
			min = root.root();
		}
		return true;
	}
	else {
		if (root.left().empty()) {



			bool b = binary(root.right(), minder, maxder);
			
			min = minn(minder, root.root());
			max = maxx(maxder, root.root());
			if (!b || minder<=root.root() || maxder<=root.root()) {
				return false;
			}


		}
		else {
			if (root.right().empty()) {


				bool bb = binary(root.left(), mini, maxi);
				

				max = maxx(maxi, root.root());
				min = minn(mini, root.root());

				if (!bb || maxi>=root.root() || mini>= root.root()) {
					return false;
				}

			}
			else {
				bool cc = binary(root.left(), mini, maxi);
				max = maxx(maxi, root.root());
				min = minn(mini, root.root());
				bool dd = binary(root.right(), minder, maxder);
				max = maxx(maxder, max);
				min = minn(minder, min);
				if (!cc || !dd) {
					return false;
				}
				if (root.root() > maxi && root.root() < minder ) {
					return true;
				}
				else {
					return false;
				}
				


			}
		}

		
		
	}

	
	
	return true;

}


/*@ </answer> */
// ===============================================================================================


void tratar_caso() {
	BinTree<int> tree = read_tree<int>(cin);
	cout << (binary_search_tree(tree) ? "SI" : "NO") << "\n";
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("Text.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int num_casos;
	cin >> num_casos;

	while (num_casos > 0) { tratar_caso(); num_casos--; }

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
     system("PAUSE");
#endif
	return 0;
}
