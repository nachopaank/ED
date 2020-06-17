/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
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

  /*@ <answer>
   * Comienza poniendo el nonmbre de los/as componentes del grupo:
   *
   *  Estudiante 1:MOHAMMED EL MESSAOUDI
   *  Estudiante 2:IGNACIO DE LA CRUZ
   *@ </answer> */

   /*
	* Implementa las operaciones pedidas en el ejercicio al final de
	* este fichero, entre las etiquetas.
	*/


#include <cassert>
#include <iostream>
#include <fstream>

class ListLinkedSingle {
private:
	struct Node {
		int value;
		Node* next;
	};

public:
	ListLinkedSingle() : head(nullptr) { }
	~ListLinkedSingle() {
		delete_list(head);
	}

	ListLinkedSingle(const ListLinkedSingle& other)
		: head(copy_nodes(other.head)) { }

	void push_front(const int& elem) {
		Node* new_node = new Node{ elem, head };
		head = new_node;
	}

	void push_back(const int& elem);

	void pop_front() {
		assert(head != nullptr);
		Node* old_head = head;
		head = head->next;
		delete old_head;
	}

	void pop_back();

	int size() const;

	bool empty() const {
		return head == nullptr;
	};

	const int& front() const {
		assert(head != nullptr);
		return head->value;
	}

	int& front() {
		assert(head != nullptr);
		return head->value;
	}

	const int& back() const {
		return last_node()->value;
	}

	int& back() {
		return last_node()->value;
	}

	const int& at(int index) const {
		Node* result_node = nth_node(index);
		assert(result_node != nullptr);
		return result_node->value;
	}

	int& at(int index) {
		Node* result_node = nth_node(index);
		assert(result_node != nullptr);
		return result_node->value;
	}

	void display(std::ostream& out) const;
	void display() const {
		display(std::cout);
	}

	void merge(ListLinkedSingle& other);

private:
	Node* head;

	void delete_list(Node* start_node);
	Node* last_node() const;
	Node* nth_node(int n) const;
	Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
	if (start_node != nullptr) {
		Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
		return result;
	}
	else {
		return nullptr;
	}
}

void ListLinkedSingle::delete_list(Node* start_node) {
	if (start_node != nullptr) {
		delete_list(start_node->next);
		delete start_node;
	}
}

void ListLinkedSingle::push_back(const int& elem) {
	Node* new_node = new Node{ elem, nullptr };
	if (head == nullptr) {
		head = new_node;
	}
	else {
		last_node()->next = new_node;
	}
}

void ListLinkedSingle::pop_back() {
	assert(head != nullptr);
	if (head->next == nullptr) {
		delete head;
		head = nullptr;
	}
	else {
		Node* previous = head;
		Node* current = head->next;

		while (current->next != nullptr) {
			previous = current;
			current = current->next;
		}

		delete current;
		previous->next = nullptr;
	}
}

int ListLinkedSingle::size() const {
	int num_nodes = 0;

	Node* current = head;
	while (current != nullptr) {
		num_nodes++;
		current = current->next;
	}

	return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
	assert(head != nullptr);
	Node* current = head;
	while (current->next != nullptr) {
		current = current->next;
	}
	return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
	assert(0 <= n);
	int current_index = 0;
	Node* current = head;

	while (current_index < n && current != nullptr) {
		current_index++;
		current = current->next;
	}

	return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
	out << "[";
	if (head != nullptr) {
		out << head->value;
		Node* current = head->next;
		while (current != nullptr) {
			out << ", " << current->value;
			current = current->next;
		}
	}
	out << "]";
}

/* ==============================================================================================
 * Implementa aqu� el m�todo merge y la funci�n merge_lists
 * ==============================================================================================
 *
 *@ <answer>
 */


using namespace std;
//2.COSTE
//El coste de merge en el caso peor podemos decir que es lineal con respecto de n , donde n es una variable que representaria el numero de nodos 
//de la lista enlazada con mayor tama�o ,ya que el caso peor ocurriria en el que una lista seria mayor que la otra , suponiendo que es necesario seguir recorriendola hasta el final
//notese que la variable descrita anteriormente como n no aparece en el programa, a continuacion reflejamos un ejemplo de esto ultimo
//1 2 3 4 5 6 7  
//9
//como ve, es necesario recorrer la primera lista en su totalidad para poder asignar el nodo de la otra lista al final
//este caso es uno de los muchos que existen , por ello suponiendo lo anterior el coste como maximo es de orden O(n) donde n es el tama�o de la lista con mayor tama�o 
//suponiendo que el caso peor es el mencionado anteriormente
//generalizando un poco podemos decir entonces que el coste se refiere al maximo tama�o de entre las dos listas en el caso peor



void ListLinkedSingle::merge(ListLinkedSingle& other) {
	// l1 y l2 son las listas mencionadas en la practica , l1 es la lista original en la que queremos meter los valores en orden de l2 , pasada por parametro

	Node* aux = head;//variable que recorrera l1
	Node* aux2 = other.head;//variable para poner a salvo en algunas situaciones nodos de l2
	Node* current = other.head;//indica en que nodo de l2 estamos
	if (aux == nullptr) { //cuando mi lista es vacia 
		this->head = aux2;
		current = nullptr;
	}
	else if (aux2 == nullptr) { //cuando lista other es vacia no hago nada
		current = nullptr;
	}
	else if (head->value > other.head->value) { //caso particular en la que la cabeza de other es menor y la modifica antes de entrar , poniendo el menor de other como cabeza
		current = other.head->next;//ponemos a salvo el siguiente nodo de other
		head = other.head;//la cabeza de l1 ahora es le minimo de l2
		head->next = aux;//la cabeza apunta a lo que antes era la cabeza de l1
		aux = head;//el aux ahora a punta a la cabeza
	}
	while (current != nullptr) {//mientras no haya mas valores que insertar en l2

		if (aux->next == nullptr) { //si la lista original ya ha acabado pero quedan elementos en other
			
			aux->next = current;//si hemos acabado con l1 , eso significa que  el ultimo elemento de l1 es menor que el elemento en el que estamos de l2 , entonces las conectariamos y habria acabado
			current = nullptr;
		}else if ((aux->value < current->value && aux->next->value >= current->value) || aux->value == current->value) { //si un valor de  l1 es menor que otro de l2 , pero este es menor a su vez que el siguiente de l1
			//o la otra condicion indica que los dos valores son  iguales y por tanto se inserta en l1
			aux2 = current->next;//ponemos a salvo el siguiente nodo de l2
			current->next = aux->next;//el nodo de l2 apunta a al siguiente nodo de l1 
			aux->next = current;//el nodo de l1 apunta al nodo anterior
			current = aux2;//recuperamos el nodo puesto a salvo
		}
		aux = aux->next;//avanzamos en l1
		}
	other.head = nullptr;
	}






/*ListLinkedSingle merge_lists(const ListLinkedSingle& l1, const ListLinkedSingle& l2) {
	//
}*/


void tratar_caso() {
	ListLinkedSingle *l1 = new ListLinkedSingle();
	ListLinkedSingle *l2 = new ListLinkedSingle();
	bool cero = true;

	while (cero) {
		int n;
		cin >> n;
		if (n == 0) {
			cero = false;
		}
		else {
			l1->push_back(n);
		}
	}
	cero = true;
	while (cero) {
		int n;
		cin >> n;
		if (n == 0) {
			cero = false;
		}
		else {
			l2->push_back(n);
		}
	}
	l1->merge(*l2);
	l1->display(std::cout);
	cout << endl;
	


}

int main() {
	
#ifndef DOMJUDGE
	std::ifstream in("ED/PRACTICA2/Text.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	int num_casos;
	cin >> num_casos;

	while (num_casos > 0) {
		tratar_caso();
		num_casos--;
	}


#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Visual Studio
	system("PAUSE");
#endif

	return 0;
}

/*@ </answer> */
