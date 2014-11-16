#include "objects.h"

namespace settlers{
    
Vertex::Vertex(): owner_id(-1), port_type(PORT_NOPORT)
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
        if(prev_length > 0)
        {
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
        }
        cur_vertex_num += add_ver;
        
        row_vertex_num += std::max(prev_length - cur_length, 0);
        for(int i = 0; i < cur_length; i++)
        {
            m_cells[cur_hex_num].vertices.resize(6);
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
    int standard_spin[] = {7, 3, 0, 12, 8, 4, 1, 16, 13, 9, 5, 2, 17, 14, 10, 6, 18, 15, 11};
    int standard_symmetry[] = {2, 1, 0, 6, 5, 4, 3, 11, 10, 9, 8, 7, 15, 14, 13, 12, 18, 17, 16};
    int default_harvest_number[] = {6, 2, 5, 3, 4, 9, 10, 8, 5, 0, 11, 8, 10, 6, 3, 4, 9, 12, 11};
    int side_vertices[] = {0, 1, 2, 3, 4, 5, 6, 14, 15, 25, 26, 37, 36, 46, 45, 53, 52, 51, 50, 49, 48, 47, 39, 38, 28, 27, 16, 17, 7, 8};
    std::vector<int> standard_size(standard, standard + 7);
    CreateSymmetrical(standard_size);
    m_spin_map = std::vector<int>(standard_spin, standard_spin + 19);
    int random_motion_seed = 0;//TODO: make it random
    int random_motion[19];
    for(int i = 0; i < 19; i++) random_motion[i] = i;
    if(random_motion_seed % 2) for(int i = 0; i < 19; i++) random_motion[i] = standard_symmetry[random_motion[i]];
    for(int j = 0; j < random_motion_seed / 2; j++) 
    {
        for(int i = 0; i < 19; i++) random_motion[i] = standard_spin[random_motion[i]];
    }
    for(int i = 0; i < 19; i++) m_cells[i].harvest_number = default_harvest_number[random_motion[i]];
    std::vector<int> board_sides;
    for(int i = 0; i < 6; i++) board_sides.push_back(i);
    //TODO: make it random
    PortType single_port[] = {PORT_ORE, PORT_COMMON, PORT_LUMBER};
    PortType double_port[] = {PORT_WOOL, PORT_BRICK, PORT_GRAIN};
    for(int i = 0; i < 6; i++){
        int side_first_vertex = i * 5;
        if(board_sides[i] % 2)
        {
            m_vertices[side_vertices[side_first_vertex + 2]].port_type = single_port[i / 2];
            m_vertices[side_vertices[side_first_vertex + 3]].port_type = single_port[i / 2];
        }
        else
        {
            m_vertices[side_vertices[side_first_vertex]].port_type = PORT_COMMON;
            m_vertices[side_vertices[side_first_vertex + 1]].port_type = PORT_COMMON;
            m_vertices[side_vertices[side_first_vertex + 3]].port_type = double_port[i / 2];
            m_vertices[side_vertices[side_first_vertex + 4]].port_type = double_port[i / 2];
        }
    }
    std::vector<GameResource> standard_recources;
    for(int i=0; i<4; i++) standard_recources.push_back(WOOL);
    for(int i=0; i<4; i++) standard_recources.push_back(LUMBER);
    for(int i=0; i<4; i++) standard_recources.push_back(GRAIN);
    for(int i=0; i<3; i++) standard_recources.push_back(BRICK);
    for(int i=0; i<3; i++) standard_recources.push_back(ORE);
    //TODO: shuffle
    for(int i=0; i<9; i++) m_cells[i].resource = standard_recources[i];
    m_cells[9].resource = NONE;
    for(int i=10; i<19; i++) m_cells[i].resource = standard_recources[i-1];
}

};
