/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Manuel Montenegro Montes
 *              Facultad de Inform�tica
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
 * MUY IMPORTANTE: Para realizar este ejercicio solo pod�is
 * modificar el c�digo contenido entre las etiquetas <answer>
 * y </answer>. Toda modificaci�n fuera de esas etiquetas est�
 * prohibida, pues no ser� corregida.
 *
 * Tampoco esta permitido modificar las l�neas que contienen
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
#include <stack>
#include <cctype>
#include <optional>
#include <sstream>
#include <string>

using namespace std;

/* ======================================================================
 * Implementaci�n de la clase BinTree para representar �rboles binarios.
 * ======================================================================
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
	// Las definiciones de TreeNode y NodePointer dependen recursivamente
	// la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
	// para que el compilador sepa, cuando analice la definici�n de NodePointer,
	// que TreeNode va a ser definida m�s adelante.

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
 * Operador << para mostrar un �rbol por pantalla. No es necesario hacer esto
 * en la pr�ctica, pero os lo dejo por si quer�is depurar.
 */
template<typename T>
std::ostream & operator<<(std::ostream &out, const BinTree<T> &tree) {
	tree.display(out);
	return out;
}


/*
 * Funci�n para leer un �rbol binario de la entrada. El formato es el siguiente:
 *
 *  �rbol vac�o: .
 *  �rbol no vac�o: (i x r)  donde i es la representaci�n del hijo izquierdo
 *                                 x es la ra�z
 *                                 r es la representaci�n del hijo derecho
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


/* ======================================================================
 * Implementaci�n de la clase MapTree para representar diccionarios
 * mediante �rboles binarios de b�squeda
 * ======================================================================
 */


template <typename K, typename V, typename ComparatorFunction = std::less<K>>
class MapTree {
private:
	template <typename S>
	class iterator_gen;
public:

	struct MapEntry {
		K key;
		V value;

		MapEntry(K key, V value) : key(key), value(value) { }
		MapEntry(K key) : key(key) { }
	};

	using const_iterator = iterator_gen<const MapEntry &>;
	using iterator = iterator_gen<MapEntry &>;


	MapTree() : root_node(nullptr), num_elems(0) { }
	MapTree(ComparatorFunction less_than) : root_node(nullptr), num_elems(0), less_than(less_than) { }
	MapTree(const MapTree &other) : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) { }
	~MapTree() {
		delete_nodes(root_node);
	}

	void insert(const MapEntry &entry) {
		if (insert(root_node, entry)) { num_elems++; }
	}

	bool contains(const K &key) const {
		return search(root_node, key) != nullptr;
	}

	const V & at(const K &key) const {
		Node *result = search(root_node, key);
		assert(result != nullptr);
		return result->entry.value;
	}

	V & at(const K &key) {
		Node *result = search(root_node, key);
		assert(result != nullptr);
		return result->entry.value;
	}

	V & operator[](const K &key) {
		bool inserted;
		Node *result = search_or_insert(root_node, key, inserted);
		if (inserted) num_elems++;
		return result->entry.value;
	}

	void erase(const K &key) {
		if (erase(root_node, key)) { num_elems--; }
	}

	int size() const {
		return num_elems;
	}
	bool empty() const {
		return num_elems == 0;
	}

	MapTree & operator=(const MapTree &other) {
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

	iterator begin() {
		return iterator(root_node);
	}

	iterator end() {
		return iterator();
	}

	const_iterator begin() const {
		return const_iterator(root_node);
	}

	const_iterator end() const {
		return const_iterator();
	}

	const_iterator cbegin() {
		return const_iterator(root_node);
	}

	const_iterator cend() {
		return const_iterator();
	}

private:
	struct Node {
		MapEntry entry;
		Node *left, *right;

		Node(Node *left, const MapEntry &entry, Node *right) : left(left), entry(entry), right(right) { }
	};

	Node *root_node;
	int num_elems;
	ComparatorFunction less_than;

	template <typename S>
	class iterator_gen {
	public:

		S operator*() const {
			assert(!st.empty());
			return st.top()->entry;
		}

		iterator_gen & operator++() {
			assert(!st.empty());
			Node *top = st.top();
			st.pop();
			descend_and_push(top->right, st);
			return *this;
		}

		iterator_gen operator++(int) {
			iterator_gen previous = *this;
			++(*this);
			return previous;
		}

		bool operator==(const iterator_gen &other) {
			return st == other.st;
		}

		bool operator!=(const iterator_gen &other) {
			return !this->operator==(other);
		}

	private:
		friend class MapTree;

		iterator_gen() { }

		iterator_gen(Node *root) {
			descend_and_push(root, st);
		}

		std::stack<Node *> st;
	};


	static Node *copy_nodes(const Node *node) {
		if (node == nullptr) {
			return nullptr;
		}
		else {
			return new Node(copy_nodes(node->left), node->entry, copy_nodes(node->right));
		}
	}

	static void delete_nodes(const Node *node) {
		if (node != nullptr) {
			delete_nodes(node->left);
			delete_nodes(node->right);
			delete node;
		}
	}

	bool insert(Node * &root, const MapEntry &entry) {
		if (root == nullptr) {
			root = new Node(nullptr, entry, nullptr);
			return true;
		}
		else if (less_than(entry.key, root->entry.key)) {
			return insert(root->left, entry);
		}
		else if (less_than(root->entry.key, entry.key)) {
			return insert(root->right, entry);
		}
		else {
			return false;
		}
	}

	Node * search(Node *root, const K &key) const {
		if (root == nullptr) {
			return nullptr;
		}
		else if (less_than(key, root->entry.key)) {
			return search(root->left, key);
		}
		else if (less_than(root->entry.key, key)) {
			return search(root->right, key);
		}
		else {
			return root;
		}
	}

	Node * search_or_insert(Node * &root, const K &key, bool &inserted) {
		if (root == nullptr) {
			inserted = true;
			root = new Node(nullptr, { key }, nullptr);
			return root;
		}
		else if (less_than(key, root->entry.key)) {
			return search_or_insert(root->left, key, inserted);
		}
		else if (less_than(root->entry.key, key)) {
			return search_or_insert(root->right, key, inserted);
		}
		else {
			inserted = false;
			return root;
		}
	}

	bool erase(Node * &root, const K &key) {
		if (root == nullptr) {
			return false;
		}
		else if (less_than(key, root->entry.key)) {
			return erase(root->left, key);
		}
		else if (less_than(root->entry.key, key)) {
			return erase(root->right, key);
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
			out << root->entry.key << " -> " << root->entry.value;
			if (root->right != nullptr) {
				out << ", ";
				display(root->right, out);
			}
		}
	}

	static void descend_and_push(Node *node, std::stack<Node *> &st) {
		Node *current = node;
		while (current != nullptr) {
			st.push(current);
			current = current->left;
		}
	}

};

template <typename K, typename V>
std::ostream & operator<<(std::ostream &out, const MapTree<K, V> &map) {
	map.display(out);
	return out;
}



/* ======================================================================
 * Analizador l�xico/sint�ctico del lenguaje Calculon++
 * ====================================================================== */


class Lexer {
public:
	Lexer(std::istream &in) : in(in) { }

	std::string peek() {
		if (next != "") {
			return next;
		}
		else {
			next = read_next();
			return next;
		}
	}

	std::string get() {
		std::string result = peek();
		next = "";
		return result;
	}

private:
	std::istream &in;

	std::string read_next() {
		ostringstream result;
		char current;
		in >> current;
		while (iswspace(current)) {
			in >> current;
		}


		if (isdigit(current)) {
			result << current;
			while (isdigit(cin.peek())) {
				in >> current;
				result << current;
			}
		}
		else if (isalpha(current)) {
			result << current;
			while (isalnum(cin.peek())) {
				in >> current;
				result << current;
			}
		}
		else if (current == '+' || current == '-' || current == '*' || current == ';' || current == '(' || current == ')') {
			result << current;
		}
		else if (current == ':') {
			result << current;
			in >> current;
			if (current != '=') throw std::domain_error("invalid token: :" + current);
			result << current;
		}
		else {
			throw std::domain_error("invalid_token: " + current);
		}

		return result.str();
	}



private:
	std::string next;
};

class Parser {
public:
	Parser(std::istream &in) : l(in) { }

	BinTree<std::string> parse() {
		return S();
	}

private:
	Lexer l;

	bool is_identifier(const std::string &token) {
		return (!token.empty() && isalpha(token[0]));
	}

	bool is_identifier_or_number(const std::string &token) {
		return (!token.empty() && isalnum(token[0]));
	}


	BinTree<std::string> S() {
		std::string identifier = l.get();
		if (!is_identifier(identifier)) throw std::domain_error("identifier expected, found " + identifier);

		std::string equal = l.get();
		if (equal != ":=") throw std::domain_error(":= expected, found " + equal);

		BinTree<std::string> rhs = E();

		std::string semicolon = l.get();
		if (semicolon != ";") throw std::domain_error("; expected, found " + semicolon);

		return { { identifier }, ":=", rhs };
	}

	BinTree<std::string> E() {
		BinTree<std::string> term = T();
		return Ep(term);
	}

	BinTree<std::string> Ep(const BinTree<std::string> &left) {
		std::string op = l.peek();
		if (op == "+" || op == "-") {
			l.get();
			BinTree<std::string> term = T();
			return Ep({ left, op, term });
		}
		else {
			return left;
		}
	}

	BinTree<std::string> T() {
		BinTree<std::string> factor = F();
		return Tp(factor);
	}

	BinTree<std::string> Tp(const BinTree<std::string> &left) {
		std::string op = l.peek();
		if (op == "*") {
			l.get();
			BinTree<std::string> factor = F();
			return Tp({ left, "*", factor });
		}
		else {
			return left;
		}
	}

	BinTree<std::string> F() {
		std::string next = l.get();
		if (is_identifier_or_number(next)) {
			return { next };
		}
		else if (next == "(") {
			BinTree<std::string> inner = E();
			std::string closing = l.get();
			if (closing != ")") throw std::domain_error(") expected, found " + closing);
			return inner;
		}
		else {
			throw std::domain_error("number or identifier expected, found " + next);
		}
	}
};


// Funci�n que lee un programa de la entrada y devuelve su AST.

BinTree<std::string> parse(std::istream &in) {
	return Parser(in).parse();
}


/* ======================================================================
 * Escribe tu soluci�n entre las etiquetas "answer" que se muestran a
 * continuaci�n.
 *
 * No es necesario a�adir ni modificar ning�n m�todo de las clases
 * anteriores.
 * ====================================================================== */

 /*@ <answer> */

using namespace std;
bool esHoja(const BinTree<string> tree) {
	return tree.left().empty() && tree.right().empty();
}
bool esnumero(string c) {
	char * p;
	strtol(c.c_str(), &p, 10);

	return (*p == 0);
}
bool esvar(string c){
	if(c!="=" && c!="*" && c!="+" && c!="-" && !esnumero(c)){
		return true;
	}
	else {
		return false;
	}
}
 int valor( string c, int y, int j) {
	if (c == "*") {
		return y * j;
	}
	else {
		if (c == "-") {
			return y - j;
		}
		else {
			if (c == "+") {
				return y + j;
			}
		}
	}
	return 0;
}
int calcul(BinTree<string> tree, const MapTree<string, int> & map) {

	if (esHoja(tree)) {
		if (esvar(tree.root())) {
			return map.at(tree.root());
		}
		else {
			return stoi(tree.root());
		}
	}
	else {
		return valor(tree.root(), calcul(tree.left(), map), calcul(tree.right(), map));
	}




}

bool tratar_caso() {
	int n;
	cin >> n;
	if(n!=0){
		MapTree<string, int> map;
		
		for (int i = 0; i < n; i++) {
			BinTree<string> tree = parse(cin);
			MapTree<string, int >::MapEntry  par { tree.left().root(),calcul(tree.right(),map) };
			map[par.key] = par.value;
		}
		for (MapTree<string,  int >::MapEntry  it: map) {
			cout << (it).key << " " << "=" << " " << it.value << endl;
		}
		cout << "---" << endl;
		return true;
	}
	else {
		return false;
	}

}

/*@ </answer> */



int main() {
#ifndef DOMJUDGE
	std::ifstream in("ED/PRACTICA9/sample.in");
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
