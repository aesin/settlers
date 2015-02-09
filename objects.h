#ifndef objects_H
#define objects_H

#include <vector>
#include <string>
#include <QColor>

namespace settlers{
enum GameResource {BRICK = 0, LUMBER, ORE, WOOL, GRAIN, RESOURCES_NUMBER, NONE};
enum CellType {DESERTS, MOUNTAINS, FORESTS, HILLS, PASTURES, FIELDS, CELL_TYPES_NUMBER};
enum PortType {PORT_NOPORT, PORT_COMMON, PORT_BRICK, PORT_LUMBER, PORT_ORE, PORT_WOOL, PORT_GRAIN};
enum Urbanization {NOTHING, VILLAGE, CITY};

class DevelopmentCards
{
    int knight;
    int monopoly;
    int road_building;
    int year_of_plenty;
    int victory_point;
};

class Resources{
public:
    Resources(): m_resources(RESOURCES_NUMBER, 0) {}
    int& operator[] (int x) {return m_resources[x];}
    const int& operator[] (int x) const {return m_resources[x];}
private:
    std::vector<int> m_resources;
};

class Player
{
public:
    Player() {}
    int m_player_id;
    std::string m_player_name;
    QColor m_color;
    std::vector<int> m_cities_id;
    std::vector<int> m_roads_id;
    DevelopmentCards m_dev_cards;
    Resources m_resources;
    int points;
};
class Vertex;
class Edge;
class Face;

class Vertex
{
public:
  Vertex();
  int owner_id;
  PortType port_type;
  Urbanization m_urban;
  int id;
  
  class RoadTo{
  public:
      RoadTo(Vertex& vert, Edge& edge): dest(vert), road(edge) {}
      Vertex & dest;
      Edge & road;
  };
  std::vector<RoadTo> neighbours;
};

class Edge
{
public:
    Edge();
    int a_id;
    int b_id;
    int owner_id;
    int id;
};

class Face
{
public:
    Face();
    std::vector<Vertex *> vertices;
    GameResource resource;
    int harvest_number;
    int id;
};

class GameBoard
{
public:
    GameBoard() {}
    void Clear();
    void CreateStandard();
    ~GameBoard() {}

    std::vector<Vertex> m_vertices;
    std::vector<Edge> m_edges;
    std::vector<Face> m_cells;
    std::vector<int> m_row_length;
private:
    bool CreateSymmetrical(std::vector<int> & row_length);
    std::vector<int> m_spin_map;
};

class GameSettings
{
public:
    bool infinite_resources;
};


}

#endif // objects_H
