#include "objects.h"
#include <QObject>

namespace settlers 
{
class GameState //: public QObject
{
    //Q_OBJECT
public:
    GameState() {};
    ~GameState() {};
    GameBoard m_board;
    GameSettings m_settings;
    DevelopmentCards m_dev_cards;
    std::vector<int> m_resources;
    std::vector<Player> m_players;
    
};
};