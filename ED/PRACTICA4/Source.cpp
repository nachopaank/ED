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

/*@ <answer>
 * Comienza poniendo el nonmbre de los/as componentes del grupo:
 *
 *  Estudiante 1:
 *  Estudiante 2:
 *@ </answer> */

/*
 * Implementa las operaciones pedidas en el ejercicio al final de
 * este fichero, entre las etiquetas.
 */


#include <iostream>
#include <cassert>
#include <fstream>
#include <string>

// TAD de las pilas implementadas mediante listas enlazadas

template<typename T>
class Stack {
public:
  Stack(): top_node(nullptr) { }
  Stack(const Stack &other)
    : top_node(copy_nodes_from(other.top_node)) { }

  ~Stack() {
    free_nodes_from(top_node);
  }

  Stack & operator=(const Stack &other) {
    if (this != &other) {
      free_nodes_from(top_node);
      top_node = copy_nodes_from(other.top_node);
    }
    return *this;
  }

  void push(const T &elem) {
    top_node = new Node{ elem, top_node };
  }

  void pop() {
    assert (top_node != nullptr);
    Node *target = top_node;
    top_node = top_node->next;
    delete target;
  }

  T & top() {
    assert (top_node != nullptr);
    return top_node->value;
  }

  const T & top() const {
    assert (top_node != nullptr);
    return top_node->value;
  }

  bool empty() const {
    return (top_node == nullptr);
  }


private:
  struct Node {
    T value;
    Node *next;
  };

  Node * copy_nodes_from(Node *other);
  void free_nodes_from(Node *other);

  Node *top_node;
};

template<typename T>
typename Stack<T>::Node * Stack<T>::copy_nodes_from(Node *other) {
  if (other == nullptr) {
    return nullptr;
  } else {
    Node *first = new Node{ other->value, nullptr };
    Node *last = first;
    Node *current = other->next;
    while (current != nullptr) {
      Node *new_node = new Node { current->value, nullptr };
      last->next = new_node;
      current = current->next;
      last = new_node;
    }
    return first;
  }
}

template<typename T>
void Stack<T>::free_nodes_from(Node *other) {
  Node *current = other;
  while (current != nullptr) {
    Node *next = current->next;
    delete current;
    current = next;
  }
}

// TAD de las colas implementadas mediante listas enlazadas

template<typename T>
class Queue {
public:
  Queue(): front_node(nullptr), back_node(nullptr) { }
  Queue(const Queue &other) { 
    copy_nodes_from(other.front_node);
  }

  ~Queue() {
    free_nodes_from(front_node);
  }

  Queue & operator=(const Queue &other) {
    if (this != &other) {
      free_nodes_from(front_node);
      copy_nodes_from(other.front_node);
    }
    return *this;
  }

  void push(const T &elem) {
    Node *new_node = new Node { elem, nullptr };
    if (back_node == nullptr) {
      back_node = new_node;
      front_node = new_node;
    } else {
      back_node->next = new_node;
      back_node = new_node;
    }
  }

  void pop() {
    assert (front_node != nullptr);
    Node *target = front_node;
    front_node = front_node->next;
    if (back_node == target) {
      back_node = nullptr;
    }
    delete target;
  }

  T & front() {
    assert (front_node != nullptr);
    return front_node->value;
  }

  const T & front() const {
    assert (front_node != nullptr);
    return front_node->elem;
  }

  bool empty() const {
    return (front_node == nullptr);
  }


private:
  struct Node {
    T value;
    Node *next;
  };

  void copy_nodes_from(Node *other);
  void free_nodes_from(Node *other);

  Node *front_node;
  Node *back_node;
};


template<typename T>
void Queue<T>::copy_nodes_from(Node *other) {
  if (other == nullptr) {
    front_node = nullptr;
    back_node = nullptr;
  } else {
    front_node = new Node { other->value, nullptr };
    back_node = front_node;
    Node *current = other->next;
    while (current != nullptr) {
      Node *new_node = new Node { current->value, nullptr };
      back_node->next = new_node;
      current = current->next;
      back_node = new_node;
    }
  }
}

template<typename T>
void Queue<T>::free_nodes_from(Node *other) {
  Node *current = other;
  while (current != nullptr) {
    Node *next = current->next;
    delete current;
    current = next;
  }
}


// --------------------------------------------------------------------
/*@ <answer> */

using namespace std;

// Completa aquí la implementación de la función pedida.

Queue<char> infix_to_postfix(Queue<char> &infix) {
  // ...
	Queue<char> output;	
	Stack<char> simbolos;
	while(!infix.empty()){
		char x = infix.front();
		infix.pop();
		if(x=='('){
			simbolos.push(x);
		}
		else if(x==')'){
			while(!simbolos.empty() && simbolos.top() != '('){
				output.push(simbolos.top());
				simbolos.pop();

			}
			if(simbolos.top() == '('){
				simbolos.pop();
			}
		}
		else if(x=='+'){
			while(!simbolos.empty() && simbolos.top() != '('){
				output.push(simbolos.top());
				simbolos.pop();
			}
			simbolos.push(x);
		}else if(x=='*'){
			while(!simbolos.empty() && simbolos.top() == '*'){
				output.push(simbolos.top());
				simbolos.pop();
			}
			simbolos.push(x);
		}
		else {
			output.push(x);
		}	
	}

	while(!simbolos.empty()){
		output.push(simbolos.top());
		simbolos.pop();
	}
	return output;
}

/*@ </answer> */
// --------------------------------------------------------------------


// Toda modificación que hagáis a partir de aquí abajo no será
// corregida.

// Si váis a modificar algo, el cambio *no* debe ser sustancial.
//
// Por ejemplo, podéis cambiar el nombre del fichero de entrada "sample.in" por otro,
// o podéis comentar la línea system("PAUSE").


bool tratar_caso() {
  // Leemos la cadena de entrada
  string cadena;
  getline(cin, cadena);

  // Si al leer nos encontramos un fin de fichero, devolvemos false.
  if (cin.eof()) { return false; }

  // Leemos la cadena de entrada, y metemos los caracteres en la cola
  Queue<char> input;
  for (char c: cadena) {
    input.push(c);
  }

  // Llamamos a la funcíón infix_to_postfix
  Queue<char> result = infix_to_postfix(input);

  // Sacamos, uno a uno, los elementos de la cola devuelta por infix_to_postfix.
  while (!result.empty()) {
    cout << result.front();
    result.pop();
  }
  
  // Imprimimos un salto de línea.
  cout << "\n";
  return true;
}


int main() {
#ifndef DOMJUDGE
  std::ifstream in("Text.txt");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (tratar_caso()) { }

#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  system("PAUSE");
#endif

  return 0;
}
