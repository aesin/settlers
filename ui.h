#ifndef ui_H
#define ui_H
#include "settlers.h"
#include <QtGui>
#include <QObject>
#include <QGraphicsScene>
#include <QPolygonF>
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>
#include <QColor>

namespace settlers 
{
const std::vector<QColor> kCellColors = {Qt::darkRed, Qt::darkGreen, Qt::gray, Qt::green, Qt::cyan, Qt::black, Qt::darkYellow};
class GameWindow;

class BoardHex : public QGraphicsPolygonItem
{
public:
    BoardHex(Face * cell, GameWindow * game_window, QGraphicsItem * parent = 0)
            : QGraphicsPolygonItem (parent), m_cell(cell), m_game_window(game_window) { };
    BoardHex(Face * cell, const QPolygonF &polygon, GameWindow * game_window, QGraphicsItem *parent = 0)
            : QGraphicsPolygonItem(polygon, parent), m_cell(cell), m_game_window(game_window) { };
    void updatecolor(){
        setBrush(QBrush(kCellColors[m_cell->resource]));
    };
    Face * m_cell;
    GameWindow * m_game_window;
protected:
    void mouseReleaseEvent (QGraphicsSceneMouseEvent * event) {
        //event->accept();
        setBrush(QBrush(Qt::darkYellow));
        //QGraphicsPolygonItem::mouseReleaseEvent(event);
    };
    void MouseDoubleClickEvent (QGraphicsSceneMouseEvent * event);
    void mousePressEvent (QGraphicsSceneMouseEvent * event) {

    };
private:
    
};

class BoardVertex : public QGraphicsEllipseItem
{
public:
    BoardVertex(Vertex * vert,GameWindow * game_window,  QGraphicsItem * parent = 0) 
            : QGraphicsEllipseItem (parent), m_vertex(vert), m_game_window(game_window) { };
    BoardVertex(Vertex * vert, double rad, GameWindow * game_window, QGraphicsItem *parent = 0)
            : QGraphicsEllipseItem(-rad,-rad,2*rad,2*rad, parent), m_vertex(vert), m_game_window(game_window) { };
    void updatecolor(){
        setBrush(QBrush(Qt::lightGray));
    };
    Vertex * m_vertex;
    GameWindow * m_game_window;
protected:
    void mouseReleaseEvent (QGraphicsSceneMouseEvent * event) {
        //event->accept();
        setBrush(QBrush(Qt::darkYellow));
        //QGraphicsPolygonItem::mouseReleaseEvent(event);
    };
    void MouseDoubleClickEvent (QGraphicsSceneMouseEvent * event);
    void mousePressEvent (QGraphicsSceneMouseEvent * event) {
        
    };
private:
    
};

class BoardEdge : public QGraphicsLineItem
{
public:
    BoardEdge(Edge * edge, GameWindow * game_window, QGraphicsItem * parent = 0)
            : QGraphicsLineItem (parent), m_edge(edge), m_game_window(game_window) { };
    BoardEdge(Edge * edge, double x1, double y1, double x2, double y2, GameWindow * game_window, QGraphicsItem *parent = 0)
            : QGraphicsLineItem(x1,y1,x2,y2, parent), m_edge(edge), m_game_window(game_window) { };
    /*void updatecolor(){
        setBrush(QBrush(Qt::lightGray));
    };*/
    Edge * m_edge;
    GameWindow * m_game_window;
protected:
    void mouseReleaseEvent (QGraphicsSceneMouseEvent * event) ;/*{
        event->accept();
        setPen(QPen(QBrush(Qt::darkYellow), 20));
       // QGraphicsPolygonItem::mouseReleaseEvent(event);
    };*/
    void MouseDoubleClickEvent (QGraphicsSceneMouseEvent * event);
    void mousePressEvent (QGraphicsSceneMouseEvent * event) {
        event->accept();
    };
private:
    
};
    
class GameBoardView : public QGraphicsView
{
  Q_OBJECT
public:
    GameBoardView(QWidget* parent = 0) : QGraphicsView(parent) { };
    QGraphicsScene * m_scene;
    QSize m_default_board_size;
protected:
    void resizeEvent(QResizeEvent *event);
    QSize sizeHint () const;
    int heightForWidth(int w) const;
private:

};

class GameWindow : public QWidget//QGraphicsView//QObject
{
  Q_OBJECT
public:
    GameWindow (GameState * game);
    void Init();
/*protected:
    void mousePressEvent (QGraphicsSceneMouseEvent * event) {
        QMessageBox mbox;
        event->accept();
        mbox.setText("something happened");
        mbox.exec();
        //QGraphicsView::mouseReleaseEvent(event);
    };
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event) {
        QMessageBox mbox;
        event->accept();
        mbox.setText("something happened");
        mbox.exec();
        //QGraphicsView::mouseReleaseEvent(event);
    };*/
    int m_player_id;
    GameState * m_game;
protected:
   /* void resizeEvent(QResizeEvent *event);
    int heightForWidth(int w) const;*/
private:
    QGraphicsScene * m_scene;
    GameBoardView * m_game_board_view;
    std::vector<BoardHex*> m_cells;
    std::vector<BoardEdge*> m_edges;
    std::vector<BoardVertex*> m_vertices;
public slots:
    void Close();
};
    
class Menu : public QObject
{
    Q_OBJECT
public:
    Menu() {};
    virtual ~Menu();
    void Init(QApplication * m_app);
    QWidget m_main_window;
private:
    
public slots:
    void NewGame();
    void OpenGame(GameState * game);
signals:
    void Quit();
};

};
#endif //ui_H