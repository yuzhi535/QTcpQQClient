#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QPoint>
#include <QSize>
#include <QMouseEvent>
#include <QMutex>
#include <QApplication>
#include <QPainter>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QEvent>
#include <QDateTime>
#include <QStringList>
#include <QScreen>
#include <QGraphicsView>

/**
 * @brief The Screen class
 * @target used for ScreenWidget
 */
class Screen
{
public:
    enum STATUS {SELECT, MOV, SET_W_H};
    Screen() {}
    Screen(QSize size);

    void setStart(QPoint pos);
    void setEnd(QPoint pos);
    QPoint getStart();
    QPoint getEnd();

    QPoint getLeftUp();
    QPoint getRightDown();

    STATUS getStatus();
    void setStatus(STATUS status);

    int width();
    int height();
    bool isInArea(QPoint pos);          // 检测pos是否在截图区域内
    void move(QPoint p);                // 按 p 移动截图区域

private:
    QPoint leftUpPos, rightDownPos;     //记录 截图区域 左上角、右下角
    QPoint startPos, endPos;            //记录 鼠标开始位置、结束位置
    int maxWidth, maxHeight;            //记录屏幕大小
    STATUS status;                      //三个状态: 选择区域、移动区域、设置width height

    void cmpPoint(QPoint &s, QPoint &e);//比较两位置，判断左上角、右下角
};

/**
 * @brief The ScreenWidget class
 * @target screenshot
 */
class ScreenWidget : public QWidget
{
    Q_OBJECT
public:
    static ScreenWidget* Instance();
    explicit ScreenWidget(QWidget *parent = nullptr);
    void showView();


protected:
    void contextMenuEvent(QContextMenuEvent* );
    void mousePressEvent(QMouseEvent* );
    void mouseMoveEvent(QMouseEvent* );
    void mouseReleaseEvent(QMouseEvent* );
    void paintEvent(QPaintEvent* );
    void showEvent(QShowEvent* );


private:
    static QScopedPointer<ScreenWidget> self;
    QMenu* menu;
    Screen* screen;
    QPixmap* fullScreen = nullptr;
    QPixmap* bgScreen;
    QPoint movPos;


private slots:
    void saveScreen();
    void saveFullScreen();
    void saveScreenOther();
    void saveFullOther();

signals:

};

#endif // SCREENWIDGET_H
