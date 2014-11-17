#include "ui.h"
#include <QPointF>
#include <QBrush>
#include <QColor>
#include <Qt>
#include <QLineF>
namespace settlers 
{
Menu::~Menu()
{
    
}

void GameWindow::Close()
{
    //TODO: save
    delete m_game;
}

GameWindow::GameWindow(GameState* game): QGraphicsView(), m_game(game)
{
    m_scene = new QGraphicsScene;
    //m_view = new QGraphicsView(m_scene);
    setScene(m_scene);
}

void GameWindow::Init()
{
    m_scene -> addText("Test");
    int h = m_game -> m_board.m_row_length.size() - 2;
    int w = 0;
    for(int x = 1; x <= h; x++) 
    {
        w = std::max(w, m_game->m_board.m_row_length[x]);
    }
    const double kEdgeLen = 100;
    double board_width = (std::sqrt(3) * w + 2) * kEdgeLen;
    double board_height = (1.5 * h + 2.5) * kEdgeLen; 
    double row_center_x = board_width / 2;
    double row_center_y = 2 * kEdgeLen;
    m_scene -> setSceneRect(0, 0, board_width, board_height);
    m_scene -> setFocus();
    QPolygonF hex_poly;
    for (int i = 0; i <= 6; i++) hex_poly << QPointF(kEdgeLen * sin(M_PI * (i%6)/3), -kEdgeLen * cos(M_PI * (i%6)/3));
    for(int j = 0; j < 6; j++) {
        printf("%lf    %lf\n", hex_poly[j].x(), hex_poly[j].y());
    }
    int cur_hex_num = 0;
    for (int row = 1; row <= h; row++)
    {
        int row_len = m_game->m_board.m_row_length[row];
        double hex_center_x = row_center_x - (row_len - 1) * std::sqrt(3) / 2 * kEdgeLen;
        for (int hex_n = 0; hex_n < row_len; hex_n++)
        {
            BoardHex * hex = new BoardHex(m_game->m_board.m_cells.data() + cur_hex_num, hex_poly);
            m_cells.push_back(hex);
            cur_hex_num++;
            hex->setBrush(QBrush(Qt::darkGreen));
            hex->setToolTip(QString::number(hex->m_cell->id));
            hex->updatecolor();
            m_scene->addItem(hex);
            hex->setPos(hex_center_x, row_center_y);
            hex_center_x += std::sqrt(3) * kEdgeLen;
        }
        row_center_y += 1.5 * kEdgeLen;
    }
    int edges_number = m_game->m_board.m_edges.size();
    for (int i = 0; i < edges_number; i++) {
        BoardEdge * edge = new BoardEdge(m_game->m_board.m_edges.data() + i);
        m_edges.push_back(edge);
        edge->setPen(QPen(QBrush(Qt::lightGray), kEdgeLen*0.2));
        edge->setToolTip(QString::number(edge->m_edge->id));
        m_scene->addItem(edge);
    }
    int vertices_number = m_game->m_board.m_vertices.size();
    for (int i = 0; i < vertices_number; i++) {
        BoardVertex * vertex = new BoardVertex(m_game->m_board.m_vertices.data() + i, kEdgeLen * 0.2);
        m_vertices.push_back(vertex);
        vertex->updatecolor();
        vertex->setToolTip(QString::number(vertex->m_vertex->id));
        m_scene->addItem(vertex);
    }
    for (int i = 0; i < m_cells.size(); i++) {
        Face * cur_cell = m_cells[i]->m_cell;
        for(int j = 0; j < 6; j++) {
            int cur_vert_id = cur_cell->vertices[j]->id;
            m_vertices[cur_vert_id]->setPos(m_cells[i]->pos() + hex_poly[j]);
        }
    }
    for (int i = 0; i < edges_number; i++) {
        int a = m_edges[i]->m_edge->a_id;
        int b = m_edges[i]->m_edge->b_id;
        if((a>=0)&&(b>=0)) m_edges[i]->setLine(QLineF(m_vertices[a]->pos(), m_vertices[b]->pos()));
        //m_edges[i]->setPos(m_vertices[a]->pos());
    }

    show();
    
    
}

void Menu::NewGame()
{
    GameState * game = new GameState;
    OpenGame(game);
}

void Menu::OpenGame(GameState* game)
{
    GameWindow * game_window = new GameWindow(game);
    game_window->Init();
}

void Menu::Init(QApplication *m_app)
{
    QVBoxLayout *m_layout = new QVBoxLayout;
    QPushButton *m_button_new = new QPushButton;
    QPushButton *m_button_show = new QPushButton;
    QPushButton *m_button_quit = new QPushButton;
    m_button_new->setText("New game");
    m_button_quit->setText("Exit");
    m_layout->addWidget(m_button_new);
    m_layout->addWidget(m_button_show);
    m_layout->addWidget(m_button_quit);
    QObject::connect(m_button_quit, SIGNAL(clicked()), this, SIGNAL(Quit()));
    QObject::connect(m_button_new, SIGNAL(clicked()), this, SLOT(NewGame()));

    //QObject::connect(m_button_quit, SIGNAL(clicked()), m_app, SLOT(quit()));
    m_main_window.setLayout(m_layout);
    //q_main_window.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //q_main_window.resize(400, 400);
    //q_main_window.move(1000, 500);
    m_main_window.show();
        
}

    
};