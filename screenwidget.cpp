#include "screenwidget.h"
#include <qmutex.h>
#include <QApplication>
#include <QPainter>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QEvent>
#include <QDateTime>
#include <QStringList>
#include <QScreen>


#define STRDATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))

Screen::Screen(QSize size)
{
    maxWidth = size.width();
    maxHeight = size.height();

    startPos = QPoint(-1, -1);
    endPos = startPos;
    leftUpPos = startPos;
    rightDownPos = startPos;
    status = SELECT;
}

int Screen::width()
{
    return maxWidth;
}

int Screen::height()
{
    return maxHeight;
}

Screen::STATUS Screen::getStatus()
{
    return status;
}

void Screen::setStatus(STATUS status)
{
    this->status = status;
}

void Screen::setEnd(QPoint pos)
{
    endPos = pos;
    leftUpPos = startPos;
    rightDownPos = endPos;
    cmpPoint(leftUpPos, rightDownPos);
}

void Screen::setStart(QPoint pos)
{
    startPos = pos;
}

QPoint Screen::getEnd()
{
    return endPos;
}

QPoint Screen::getStart()
{
    return startPos;
}

QPoint Screen::getLeftUp()
{
    return leftUpPos;
}

QPoint Screen::getRightDown()
{
    return rightDownPos;
}

bool Screen::isInArea(QPoint pos)
{
    if (pos.x() > leftUpPos.x() && pos.x() < rightDownPos.x() && pos.y() > leftUpPos.y() && pos.y() < rightDownPos.y()) {
        return true;
    }

    return false;
}

void Screen::move(QPoint p)
{
    int lx = leftUpPos.x() + p.x();
    int ly = leftUpPos.y() + p.y();
    int rx = rightDownPos.x() + p.x();
    int ry = rightDownPos.y() + p.y();

    if (lx < 0) {
        lx = 0;
        rx -= p.x();
    }

    if (ly < 0) {
        ly = 0;
        ry -= p.y();
    }

    if (rx > maxWidth)  {
        rx = maxWidth;
        lx -= p.x();
    }

    if (ry > maxHeight) {
        ry = maxHeight;
        ly -= p.y();
    }

    leftUpPos = QPoint(lx, ly);
    rightDownPos = QPoint(rx, ry);
    startPos = leftUpPos;
    endPos = rightDownPos;
}

void Screen::cmpPoint(QPoint &leftTop, QPoint &rightDown)
{
    QPoint l = leftTop;
    QPoint r = rightDown;

    if (l.x() <= r.x()) {
        if (l.y() <= r.y()) {
            ;
        } else {
            leftTop.setY(r.y());
            rightDown.setY(l.y());
        }
    } else {
        if (l.y() < r.y()) {
            leftTop.setX(r.x());
            rightDown.setX(l.x());
        } else {
            QPoint tmp;
            tmp = leftTop;
            leftTop = rightDown;
            rightDown = tmp;
        }
    }
}

QScopedPointer<ScreenWidget> ScreenWidget::self;

ScreenWidget* ScreenWidget::Instance()
{
    if (self.isNull())
    {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if (self.isNull())
            self.reset(new ScreenWidget);
    }
    self.reset(new ScreenWidget);
    return self.data();
}

ScreenWidget::ScreenWidget(QWidget *parent) : QWidget(parent)
{
    menu = new QMenu(this);
    menu->addAction(QString("保存当前截图"), this, SLOT(saveScreen()));
    menu->addAction(QString("保存全屏截图"), this, SLOT(saveFullScreen()));
    menu->addAction(QString("截图另存为"), this, SLOT(saveScreenOther()));
    menu->addAction(QString("全屏另存为"), this, SLOT(saveFullOther()));
    menu->addAction(QString("退出截图"), this, SLOT(hide()));

    screen = new Screen(QApplication::desktop()->size());
    fullScreen = new QPixmap();
}

void ScreenWidget::paintEvent(QPaintEvent *)
{
    int x = screen->getLeftUp().x();
    int y = screen->getLeftUp().y();
    int w = screen->getRightDown().x() - x;
    int h = screen->getRightDown().y() - y;

    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(2);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    painter.drawPixmap(0, 0, *bgScreen);

    if (w != 0 && h != 0) {
        painter.drawPixmap(x, y, fullScreen->copy(x, y, w, h));
    }

    painter.drawRect(x, y, w, h);

    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.drawText(x + 2, y - 8, tr("截图范围：( %1 x %2 ) - ( %3 x %4 )  图片大小：( %5 x %6 )")
                     .arg(x).arg(y).arg(x + w).arg(y + h).arg(w).arg(h));
}

void ScreenWidget::showEvent(QShowEvent *)
{
    QPoint point(-1, -1);
    screen->setStart(point);
    screen->setEnd(point);

    QScreen *pscreen = QApplication::primaryScreen();
    *fullScreen = pscreen->grabWindow(QApplication::desktop()->winId(), 0, 0, screen->width(), screen->height());

    //设置透明度
    QPixmap pix(screen->width(), screen->height());
    pix.fill((QColor(160, 160, 160, 200)));
    bgScreen = new QPixmap(*fullScreen);
    QPainter p(bgScreen);
    p.drawPixmap(0, 0, pix);
}

void ScreenWidget::saveScreen()
{
    int x = screen->getLeftUp().x();
    int y = screen->getLeftUp().y();
    int w = screen->getRightDown().x() - x;
    int h = screen->getRightDown().y() - y;

    *fullScreen = fullScreen->copy(x, y, w, h);

    QString fileName("screenShot.png");
    fullScreen->copy(x, y, w, h).save(fileName, "png");
    close();
}

void ScreenWidget::saveFullScreen()
{
    QString fileName("screenShot.png");
//    QString fileName = QString("%1/full_%2.png").arg(qApp->applicationDirPath()).arg(STRDATETIME);
    fullScreen->save(fileName, "png");
    close();
}

void ScreenWidget::saveScreenOther()
{
    QString fileName("screenShot.png");

    int x = screen->getLeftUp().x();
    int y = screen->getLeftUp().y();
    int w = screen->getRightDown().x() - x;
    int h = screen->getRightDown().y() - y;

    fullScreen->copy(x, y, w, h).save(fileName, "png");
    close();
}

void ScreenWidget::saveFullOther()
{
    QString fileName("screenShot.png");
    if (fileName.length() > 0) {
        fullScreen->save(fileName, "png");
        close();
    }
}

void ScreenWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (screen->getStatus() == Screen::SELECT) {
        screen->setEnd(e->pos());
    } else if (screen->getStatus() == Screen::MOV) {
        QPoint p(e->x() - movPos.x(), e->y() - movPos.y());
        screen->move(p);
        movPos = e->pos();
    }

    this->update();
}

void ScreenWidget::mousePressEvent(QMouseEvent *e)
{
    int status = screen->getStatus();

    if (status == Screen::SELECT) {
        screen->setStart(e->pos());
    } else if (status == Screen::MOV) {
        if (screen->isInArea(e->pos()) == false) {
            screen->setStart(e->pos());
            screen->setStatus(Screen::SELECT);
        } else {
            movPos = e->pos();
            this->setCursor(Qt::SizeAllCursor);
        }
    }

    this->update();
}

void ScreenWidget::mouseReleaseEvent(QMouseEvent *)
{
    if (screen->getStatus() == Screen::SELECT) {
        screen->setStatus(Screen::MOV);
    } else if (screen->getStatus() == Screen::MOV) {
        this->setCursor(Qt::ArrowCursor);
    }
}

void ScreenWidget::contextMenuEvent(QContextMenuEvent *)
{
    this->setCursor(Qt::ArrowCursor);
    menu->exec(cursor().pos());
}
