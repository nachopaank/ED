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
 * Estudiante 1:
 * Estudiante 2:
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>

using namespace std;

using jugador = std::string;

class Buscaminas
{
  // Implementar
public:
  Buscaminas() {}

  void anyadir_mina(int x, int y)
  {
    casillas.insert({-1,Casillas(x*y)});
  }
  void anyadir_jugador(jugador j)
  {
    if (jugadores.count(j)) {
      throw std::invalid_argument("Jugador existente");
    }
    jugadores.insert({j, InfoJugador(j)});
  }
  int explorar(jugador j, int x, int y)
  {
    const InfoJugador &InfoJ = buscar_jugador(j);
    const Casillas &cas = buscar_mina(x*y);
    //get la key desde casillas no se como
  }
  void bandera(jugador, int x, int y)
  {
  }
  int puntuacion(jugador)
  {
  }
  int num_minas()
  {
  }
  void bordes_tablero(int &min_x, int &min_y, int &max_x, int &max_y)
  {
  }
private:
  struct InfoJugador {
    std::string nombre;
    int puntuacion;
    InfoJugador(const std::string &nombre): nombre(nombre) { }
  };
  struct Casillas {
    int pos;
    int value;
    Casillas(const int &pos): pos(pos) { }
  }; 
  const InfoJugador &buscar_jugador(const std::string nombre) const {
    auto it_jugador = jugadores.find(nombre);
    if (it_jugador == jugadores.end()) {
      throw std::domain_error("Jugador no existente");
    } else {
      return it_jugador->second;
    }
  }
  const Casillas &buscar_mina(int pos) const {
    auto it_mina = casillas.find(pos);
    if (it_mina == casillas.end()) {
      throw std::domain_error("Mina no existente");
    } else {
      return it_mina->second;
    }
  }
  std::unordered_map<jugador, InfoJugador> jugadores;  
  std::unordered_map<int, Casillas> casillas; 

};

bool tratar_caso()
{
  // Implementar. Devolver false si al leer
  // se llega al fin del fichero, o true
  // en caso contrario.
  return false;
}

int main()
{
#ifndef DOMJUDGE
  std::ifstream in("ED/PRACTICA11/sample.in");
  auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

  while (tratar_caso())
  {
  }
#ifndef DOMJUDGE
  std::cin.rdbuf(cinbuf);
  // Descomentar si se trabaja en Windows
  system("PAUSE");
#endif
  return 0;
}
