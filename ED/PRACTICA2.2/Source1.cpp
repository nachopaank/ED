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
using namespace std;
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

 //COSTE DEL ALGORITMO
 //El coste de este algoritmo podemos decir de primeras que es lineal con respecto a la suma de la longitud de  de las dos listas ,ya que recorremos las dos listas en su totalidad
 //a continuaci�n desglosaremos el coste de las distintas partes del algoritmo para justificar esto ultimo descrbiendo los distintos bucles del programa
 //en primer lugar tenemos los costes de los constructores de copia que son lineales con respecto al tama�o de ambas listas
 //en segundo lugar para obtener el tama�o de las listas , el metodo size recorre ambas listas siendo lineal por tanto con respecto al tama�o de ambas listas
 //los tres bucles siguientes se ejecutan un numero de veces igual a la suma del tama�o de ambas listas , nunca sera superior a esta suma
 //y por ultimo tenemos el bucle que nos da la vuelta a la lista inv para que este ordenada ascendentemente
// como se coge aquel coste de orden mayor ,el coste quedaria 
//en el orden de O(l1.size()+l2.size()) donde l1 y l2 son las dos listas que queremos mezclar,size hace referencia al tama�o de cada lista,
 //por ello el coste es lineal con respecto a la suma los tama�os de ambas listas.





ListLinkedSingle merge_lists(const ListLinkedSingle& l1, const ListLinkedSingle& l2) {
	
		ListLinkedSingle *inv = new ListLinkedSingle();
		ListLinkedSingle *l11 = new ListLinkedSingle(l1);
		ListLinkedSingle *l22 = new ListLinkedSingle(l2);
		ListLinkedSingle *asc = new ListLinkedSingle();
		int i = 0, j = 0;
		int size1 = l11->size();
		int size2 = l22->size();
		while (i < size1 && j < size2) {
			int x = l11->front();
			int y = l22->front();
			if (x > y) {
				inv->push_front(l22->front());
				l22->pop_front();
				j++;
			}
			else {
				
				inv->push_front(l11->front());
				l11->pop_front();
				i++;
				
			}
		}
			while (i < size1) {
				inv->push_front(l11->front());
				l11->pop_front();
				i++;
		     }
			while (j < size2) {
				inv->push_front(l22->front());
				l22->pop_front();
				j++;
			}
			int sizetotal = size1 + size2;
			int s = 0;
			while(s < sizetotal) {
				asc->push_front(inv->front());
				inv->pop_front();
				s++;
			}
	
		return *asc;

}


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

	merge_lists(*l1, *l2).display(std::cout);
	cout << endl;



}


int main() {

#ifndef DOMJUDGE
	std::ifstream in("ED/PRACTICA2.2/Texto.txt");
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