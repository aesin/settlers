#include "objects.h"

namespace board_objects{
    
Vertex::Vertex(): owner_id(-1), port_type(NOPORT)
{
}

Edge::Edge(): owner_id(-1)
{
}

Face::Face()
{
}
    
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
    for(int i = 0; i < cells_num; i++) m_cells[i].id=i;    
    for(int i = 0; i < vertices_num; i++) m_vertices[i].id=i;    
    for(int i = 0; i < edges_num; i++) m_edges[i].id=i;
    int cur_edge_num = 0;
    int cur_vertex_num = 0;
    int cur_hex_num = 0;
    for(int row = 1; row <= rows - 1; row++)
    {
        int row_vertex_num = cur_vertex_num;
        int cur_length = row_length[row];
        int prev_length = row_length[row - 1];
        int add_ver = std::max(cur_length - prev_length, 0);
        cur_vertex_num += add_ver;
        for(int i = 0; i <= prev_length * 2; i++)
        {
            if(i < prev_length * 2) m_cells[cur_hex_num - prev_length + (i / 2)].vertices[4 - (i % 2)] = &m_vertices[cur_vertex_num];
            if(i % 2 == 0){
                m_edges[cur_edge_num].a_id = cur_vertex_num;
                if(i>0) 
                {
                    m_cells[cur_hex_num - prev_length + (i / 2) - 1].vertices[2] = &m_vertices[cur_vertex_num];
                    m_edges[cur_edge_num].b_id = m_cells[cur_hex_num - prev_length + (i / 2) - 1].vertices[1] -> id;
                }
                else 
                {
                    m_edges[cur_edge_num].b_id = m_cells[cur_hex_num - prev_length + (i / 2)].vertices[5] -> id;
                }
                cur_edge_num++;
            }
            cur_vertex_num++;
        }
        cur_vertex_num += add_ver;
        
        row_vertex_num += std::max(prev_length - cur_length, 0);
        for(int i = 0; i < cur_length; i++)
        {
            m_cells[cur_hex_num].vertices[5] = &m_vertices[row_vertex_num + 2 * i];
            m_cells[cur_hex_num].vertices[0] = &m_vertices[row_vertex_num + 2 * i + 1];
            m_cells[cur_hex_num].vertices[1] = &m_vertices[row_vertex_num + 2 * i + 2];
            cur_hex_num++;            
        }
        
        for(int i = cur_vertex_num - 2 * std::max(cur_length, prev_length); i <= cur_vertex_num; i++)
        {
            m_edges[cur_edge_num].a_id = i-1;
            m_edges[cur_edge_num].b_id = i;
            cur_edge_num++;
        }
    }
  
}

void GameBoard::CreateStandard()
{
    int standard[] = {0, 3, 4, 5, 4, 3, 0};
    std::vector<int> standard_size(standard, standard + 7);
    CreateSymmetrical(standard_size);
}

};
