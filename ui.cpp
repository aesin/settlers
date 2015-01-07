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

GameWindow::GameWindow(GameState* game): QWidget(), m_game(game)
{
    m_scene = new QGraphicsScene(this);
    m_game_board_view = new GameBoardView(this);
    m_game_board_view->m_scene = m_scene;
    //m_view = new QGraphicsView(m_scene);
    m_game_board_view->setScene(m_scene);
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
    int cur_hex_num = 0;
    for (int row = 1; row <= h; row++)
    {
        int row_len = m_game->m_board.m_row_length[row];
        double hex_center_x = row_center_x - (row_len - 1) * std::sqrt(3) / 2 * kEdgeLen;
        for (int hex_n = 0; hex_n < row_len; hex_n++)
        {
            BoardHex * hex = new BoardHex(m_game->m_board.m_cells.data() + cur_hex_num, hex_poly, this);
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
        BoardEdge * edge = new BoardEdge(m_game->m_board.m_edges.data() + i, this);
        m_edges.push_back(edge);
        edge->setPen(QPen(QBrush(Qt::lightGray), kEdgeLen*0.2));
        edge->setToolTip(QString::number(edge->m_edge->id));
        m_scene->addItem(edge);
    }
    int vertices_number = m_game->m_board.m_vertices.size();
    for (int i = 0; i < vertices_number; i++) {
        BoardVertex * vertex = new BoardVertex(m_game->m_board.m_vertices.data() + i, kEdgeLen * 0.2, this);
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

    m_game_board_view->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
    m_game_board_view->m_default_board_size.setHeight(board_height);
    m_game_board_view->m_default_board_size.setWidth(board_width);
    //m_game_board_view->show();
    QSizePolicy size_policy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    QSizePolicy size_policy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
    size_policy.setHeightForWidth(true);
    //m_game_board_view->setSizePolicy(size_policy);
   
    
    QHBoxLayout *m_layout = new QHBoxLayout;
    m_layout->addWidget(m_game_board_view, 1);
    QPushButton *m_button = new QPushButton;
    m_button->setText("Random button");
    m_button->setSizePolicy(size_policy2);
    m_layout->addWidget(m_button);
    setLayout(m_layout);
    show();
    m_player_id = 1;
}

void BoardEdge::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_edge->owner_id == -1) {
        QString result;
        if (m_game_window->m_game->TryBuildRoad(m_game_window->m_player_id, *m_edge, result)) {
            QMessageBox confirm;
            //confirm.setText("Build road here?");
            QPushButton * conf = confirm.addButton("Yay!", QMessageBox::ActionRole);
            QPushButton * rej = confirm.addButton(QMessageBox::Abort);
            confirm.exec();
            if(confirm.clickedButton() == conf) {
                m_game_window->m_game->BuildRoad(m_game_window->m_player_id, *m_edge);
                setPen(QPen(m_game_window->m_game->m_players[m_game_window->m_player_id].m_color, pen().width()));
            }
        }
        else {
            QMessageBox warn;
            warn.setText(result);
            warn.exec();
        }
    }
}

void BoardVertex::updatecolor() {
    setBrush(QBrush((m_vertex->owner_id >= 0) ? m_game_window->m_game->m_players[m_vertex->owner_id].m_color : Qt::lightGray));
}

void BoardEdge::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

}

void BoardHex::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    QMessageBox test;
    test.setText("Face doubleclicked");
    test.exec();
}

void BoardVertex::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_vertex->owner_id == -1){
        QString result;
        if (m_game_window->m_game->TryBuildVillage(m_game_window->m_player_id, *m_vertex, result)) {
            QMessageBox confirm;
            //confirm.setText("Build village here?");
            QPushButton * conf = confirm.addButton("Yay!", QMessageBox::ActionRole);
            QPushButton * rej = confirm.addButton(QMessageBox::Abort);
            confirm.exec();
            if(confirm.clickedButton() == conf) {
                m_game_window->m_game->BuildVillage(m_game_window->m_player_id, *m_vertex);
                setBrush(QBrush(m_game_window->m_game->m_players[m_game_window->m_player_id].m_color));
            }
        }
        else {
            QMessageBox warn;
            warn.setText(result);
            warn.exec();
        }
    } else if ((m_vertex->owner_id == m_game_window->m_player_id) && (m_vertex->m_urban == VILLAGE)) {
        QString result;
        if (m_game_window->m_game->TryBuildCity(m_game_window->m_player_id, *m_vertex, result)) {
            QMessageBox confirm;
            //confirm.setText("Build city here?");
            QPushButton * conf = confirm.addButton("Yay!", QMessageBox::ActionRole);
            QPushButton * rej = confirm.addButton(QMessageBox::Abort);
            confirm.exec();
            if (confirm.clickedButton() == conf) {
                m_game_window->m_game->BuildCity(m_game_window->m_player_id, *m_vertex);
                QRectF newrect = rect();
                newrect.setTopLeft(1.75*newrect.topLeft());
                newrect.setBottomRight(1.75*newrect.bottomRight());
                setRect(newrect);
                //update(newrect);
            }
        }
        else {
            QMessageBox warn;
            warn.setText(result);
        }\
    }
}

void GameBoardView::resizeEvent(QResizeEvent* event)
{
    fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
    //QGraphicsView::resizeEvent(event);
}

int GameBoardView::heightForWidth(int w) const
{
    return w;//(m_scene->sceneRect().height()*w)/m_scene->sceneRect().width();
    printf("igot called \n");
}

QSize GameBoardView::sizeHint() const
{
    return m_default_board_size;
    //return QGraphicsView::sizeHint();
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

    
}
