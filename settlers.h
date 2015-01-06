#ifndef settlers_H
#define settlers_H
#include "objects.h"
#include <QObject>

namespace settlers 
{
enum GamePhase {PRE_GAME, STARTING_VILLAGE, PRE_ROLL, ROBBER, MAIN_PHASE, CONFIRMATION, PHASES_NUM};
const int BANK = -1;

class GameState : public QObject
{
    Q_OBJECT
public:
    GameState();
    ~GameState() {};

    bool ResTrade(int id1, int id2, Resources * res1, Resources * res2 = nullptr);
    bool TryBuildRoad(int player, Edge & road, std::string & result);
    void BuildRoad(int player, Edge & road);
    bool TryBuildVillage(int player, Vertex & place, std::string & result);
    void BuildVillage(int player, Vertex & place);
    bool TryBuildCity(int player, Vertex & place, std::string & result);
    void BuildCity(int player, Vertex & place);

    GameBoard m_board;
    GameSettings m_settings;
    DevelopmentCards m_dev_cards;
    Resources m_resources;
    std::vector<Player> m_players;
    int m_current_player;
private:

};

};
#endif //settlers_H