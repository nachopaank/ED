/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 * Indica el nombre y apellidos de los componentes del
 * grupo:
 *
 * Nombre 1:
 * Nombre 2:
 * ---------------------------------------------------
 */


#include <strstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

class Date {
public:  
  Date(){
    dia = 1;
    mes = 1;
    anyo = 1970;
  }
  Date(int day, int month, int year){
    dia = day;
    mes = month;
    anyo = year;
  }
  
  bool operator<(const Date &other) const{
    if (anyo < other.anyo){
        return true;
    }
    else if (anyo == other.anyo){
      if(mes < other.mes){
        return true;
      }
      else if (mes== other.mes){
        if(dia < other.dia){
          return true;
        }
      }
    }
    return false;
  }
  bool operator<=(const Date &other) const;
  
  void read(std::istream &in){
    char barra = '/';
    in >> dia >> barra >> mes >> barra >> anyo;
}
  
private:
  int dia;
  int mes;
  int anyo;
  // ...
};
std::istream & operator>>(std::istream &in, Date &f) {
  f.read(in);
  return in;
}


class FamilyTree {
public:
  FamilyTree(): root(nullptr){
  }
  bool myroot;
   void read(std::istream &in){
    Date myDate;
    int childs;
    myDate.read(in);
    std::vector<FamilyTreeNode *> Aux;
    if(myroot){
      root = new FamilyTreeNode{myDate,Aux};
      myroot = false;
    }
    in >> childs;
    std::vector<FamilyTreeNode *> Child;
    for(int i = 0;i < childs;i++){
      Child.push_back(new FamilyTreeNode{myDate,Aux});
      read(in);
    }


  }
bool nonsense(){
  for(int i = 0; i < root->children.size(); i++){
    if(root->children[i]->date < root->date){
      return false;
    }
  }
  return true;
}

private:
  struct FamilyTreeNode {
    Date date;
    std::vector<FamilyTreeNode *> children;  
  };
  FamilyTreeNode *root;
};

std::istream & operator>>(std::istream &in, FamilyTree &f) {
  f.read(in);
  return in;
}



using namespace std;

void tratar_caso() {
  // ...
  FamilyTree myTree = FamilyTree();
  myTree.myroot = true;
  myTree.read(cin);      
  if(myTree.nonsense()){
    cout << "NO" << endl;
  }
  else {
    cout << "SI" <<endl;
  }

}


int main() {
#ifndef DOMJUDGE
  std::ifstream in("Text.txt");
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
  // system("PAUSE");
#endif

  return 0;
}
