#include "objects.h"

namespace board_objects{

void GameBoard::Clear()
{
    m_cells.clear();
    m_edges.clear();
    m_vertices.clear();
}

bool GameBoard::CreateSymmetrical(std::vector<int> & row_length)
{
    Clear();
    int rows = row_length.size();
    if (rows < 3) return false;
    if((row_length[0] != 0)||(row_length[rows - 1] != 0)) return false;
    int cells_num = 0;
    int vertices_num = 0;
    int edges_num = 0;
    for(int row = 1; row <= rows - 1; row++)
    {
        int cur_length = row_length[row];
		int prev_length = row_length[row - 1];
		if((cur_length != 0)&&(prev_length != 0)&&((cur_length - prev_length) % 2 == 0)) return false;
		cells_num += cur_length;
		vertices_num += 2 * std::max(cur_length, prev_length) + 1;
		edges_num += 2 * std::max(cur_length, prev_length) + cur_length + 1;
    }
    m_cells.resize(cells_num);
    m_vertices.resize(vertices_num);
    m_edges.resize(edges_num);
    int cur_edge = 0;
    int cur_vertex = 0;
    int cur_face = 0;
    for(int row = 1; row <= rows - 1; row++)
    {
		int cur_length = row_length[row];
		int prev_length = row_length[row - 1];
		for(int i = 0; i < cur_length - prev_length; i++)
		{
			m_vertices[cur_vertex].id = cur_vertex;
			m_vertices[cur_vertex].port_type = NOPORT;
			
					
		}
    }
  
}
}
