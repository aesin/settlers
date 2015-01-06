#include "settlers.h"
namespace settlers 
{
GameState::GameState()
{
    m_board.CreateStandard();
    // code for testing
    m_players.resize(2);
    m_players[0].m_color = Qt::red;
    m_players[1].m_color = Qt::blue;
    m_current_player = 0;
    //
}

bool GameState::ResTrade(int id1, int id2, Resources* res1, Resources* res2)
{
    for (int res = 0; res < RESOURCES_NUMBER; res++) {
        m_players[id1].m_resources[res] -= (*res1)[res];
        m_players[id2].m_resources[res] += (*res1)[res];
    }
    if (res2 != nullptr) {
        for (int res = 0; res < RESOURCES_NUMBER; res++) {
            m_players[id2].m_resources[res] -= (*res2)[res];
            m_players[id1].m_resources[res] += (*res2)[res];
        }
    }
}

bool GameState::TryBuildRoad(int player, Edge& road, std::string& result)
{
    return true;
}

void GameState::BuildRoad(int player, Edge& road)
{
    Resources cost;
    cost[BRICK] = 1;
    cost[LUMBER] = 1;
    ResTrade(player, BANK, &cost);
    road.owner_id = player;
    //TODO: Reconsider longest track
}

bool GameState::TryBuildVillage(int player, Vertex& place, std::string& result)
{
    if (place.owner_id != -1) { 
        result="This place is occupied.";
        return false;
    }
    bool place_access = false;
    bool near_cities = false;
    for (int nb = 0; nb < place.neighbours.size(); nb++) {
        if (place.neighbours[nb].road.owner_id == player) place_access = true;
        if (place.neighbours[nb].dest.owner_id != -1) near_cities = true;
    }
    if (!place_access) {
        result="You can't build here.";
        return false;
    }
    if (near_cities) {
        result="There is a village or city nearby.";
        return false;
    }
    if((m_players[player].m_resources[BRICK] < 1) || (m_players[player].m_resources[LUMBER] < 1)) {
        result="You don't have enough resources.";
        return false;
    }
    return true;
}

void GameState::BuildVillage(int player, Vertex& place)
{
    Resources cost;
    cost[WOOL] = 1;
    cost[BRICK] = 1;
    cost[LUMBER] = 1;
    cost[GRAIN] = 1;
    ResTrade(player, BANK, &cost);
    place.owner_id = player;
    place.m_urban=VILLAGE;
    //TODO: Reconsider longest track if needed
    m_players[player].points++;
    //TODO: Check victory conditions
}

bool GameState::TryBuildCity(int player, Vertex& place, std::string& result)
{
    if((m_players[player].m_resources[ORE] < 3) || (m_players[player].m_resources[GRAIN] < 2)) {
        result="You don't have enough resources.";
        return false;
    }
    return true;
}

void GameState::BuildCity(int player, Vertex& place)
{
    Resources cost;
    cost[GRAIN] = 2;
    cost[ORE] = 3;
    ResTrade(player, BANK, &cost);
    place.m_urban=CITY;
    m_players[player].points++;
    //TODO: Check victory conditions
}


};