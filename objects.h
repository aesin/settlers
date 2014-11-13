#ifndef objects_H
#define objects_H

#include <vector>

namespace board_objects{
enum GameResource {BRICKR, LUMBERR, ORER, WOOLR, GRAINR};
enum CellType {DESERTS, MOUNTAINS, FORESTS, HILLS, PASTURES, FIELDS};
enum PortType {NOPORT, COMMON, BRICK, LUMBER, ORE, WOOL, GRAIN};

class Vertex
{
public:
  
  int owner_id;
  PortType port_type;
  int id;
};

class Edge
{
public:
  int vertex1_id;
  int vertex2_id;
  int owner_id;
  int id;
};

class Face
{
public:
  std::vector<Vertex *> vertices;
  CellType resource;
  int face_number;
  int id;
};

class GameBoard
{
public:
    GameBoard();
    void Clear();
    void CreateStandard();
    ~GameBoard();
    
    std::vector<Vertex> m_vertices;
    std::vector<Edge> m_edges;
    std::vector<Face> m_cells;
private:
    bool CreateSymmetrical(std::vector<int> & row_length);
};


#endif // objects_H
