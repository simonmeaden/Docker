#include "docker/dockwidget.h"

#include <algorithm>

#include <QDebug>

#include "docker/abstractdockitem.h"
#include "docker/dockcorner.h"
#include "docker/dockfooter.h"
#include "docker/dockheader.h"
#include "docker/docktoolbar.h"
#include "docker/private/abstractdockwidgetprivate.h"
#include "docker/private/dockwidgetprivate.h"

//====================================================================
//=== DockWidget
//====================================================================
DockWidget::DockWidget(QWidget* parent)
  : AbstractDockWidget(*new DockWidgetPrivate(this), parent)
{
  //  auto p = palette();
  //  p.setColor(QPalette::Window, QColor("red"));
  //  setPalette(p);
}

DockWidget::DockWidget(DockWidgetPrivate& d)
  : AbstractDockWidget(d)
{
}

void
DockWidget::calculateGeometry(const QRect& rect)
{
  Q_D(DockWidget);
  d->calculateGeometry(rect);
}

DockToolbar*
DockWidget::addToolbar(Docker::DockPosition position)
{
  Q_D(DockWidget);
  auto w = d->addToolbar(position);
  repaint();
  return w;
}

void
DockWidget::removeToolbar(Docker::DockPosition position)
{
  Q_D(DockWidget);
  d->removeToolbar(position);
  repaint();
}

void
DockWidget::removeToolbar(DockToolbar* toolbar)
{
  Q_D(DockWidget);
  d->removeToolbar(toolbar);
  repaint();
}

void
DockWidget::hideToolbar(Docker::DockPosition position)
{
  Q_D(DockWidget);
  d->hideToolbar(position);
}

void
DockWidget::hideToolbar(DockToolbar* toolbar)
{
  Q_D(DockWidget);
  d->hideToolbar(toolbar);
}

void
DockWidget::showToolbar(Docker::DockPosition position)
{
  Q_D(DockWidget);
  d->showToolbar(position);
}

void
DockWidget::showToolbar(DockToolbar* toolbar)
{
  Q_D(DockWidget);
  d->showToolbar(toolbar);
}

bool
DockWidget::moveToolbar(Docker::DockPosition newPosition,
                        Docker::DockPosition oldPosition)
{
  Q_D(DockWidget);
  return d->moveToolbar(newPosition, oldPosition);
}

void
DockWidget::resizeEvent(QResizeEvent* /*event*/)
{
  calculateGeometry(rect());
}

QWidget*
DockWidget::clone(QWidget* widget)
{
  auto anobject = qobject_cast<DockWidget*>(widget);
  if (anobject)
    return d_ptr->clone(anobject);
  return nullptr;
}

AbstractDockItem*
DockWidget::header()
{
  Q_D(DockWidget);
  return d->header();
}

AbstractDockItem*
DockWidget::footer()
{
  Q_D(DockWidget);
  return d->footer();
}

AbstractDockItem*
DockWidget::northToolbar()
{
  Q_D(DockWidget);
  return d->northToolbar();
}

AbstractDockItem*
DockWidget::southToolbar()
{
  Q_D(DockWidget);
  return d->southToolbar();
}

AbstractDockItem*
DockWidget::eastToolbar()
{
  Q_D(DockWidget);
  return d->eastToolbar();
}

AbstractDockItem*
DockWidget::westToolbar()
{
  Q_D(DockWidget);
  return d->westToolbar();
}

DockToolbar*
DockWidget::toolbarAt(Docker::DockPosition position)
{
  Q_D(DockWidget);
  return d->toolbarAt(position);
}

DockToolbar*
DockWidget::toolbarTakeAt(Docker::DockPosition position)
{
  Q_D(DockWidget);
  return d->toolbarTakeAt(position);
}

bool
DockWidget::setToolbarAt(Docker::DockPosition position, DockToolbar* toolbar)
{
  Q_D(DockWidget);
  return d->setToolbarAt(position, toolbar);
}

DockFooter*
DockWidget::addFooter()
{
  Q_D(DockWidget);
  return d->addFooter();
}

void
DockWidget::removeFooter()
{
  Q_D(DockWidget);
  return d->removeFooter();
}

void
DockWidget::hideFooter()
{
  Q_D(DockWidget);
  d->hideFooter();
}

void
DockWidget::showFooter()
{
  Q_D(DockWidget);
  d->showFooter();
}

DockHeader*
DockWidget::addHeader()
{
  Q_D(DockWidget);
  return d->addHeader();
}

void
DockWidget::removeHeader()
{
  Q_D(DockWidget);
  d->removeHeader();
}

void
DockWidget::hideHeader()
{
  Q_D(DockWidget);
  d->hideHeader();
}

void
DockWidget::showHeader()
{
  Q_D(DockWidget);
  d->showHeader();
}

void
DockWidget::setCorners(Docker::CornerType northWest,
                       Docker::CornerType northEast,
                       Docker::CornerType southWest,
                       Docker::CornerType southEast)
{
  Q_D(DockWidget);
  d->setCorners(northWest, northEast, southWest, southEast);
}

void
DockWidget::setCornerSize(Docker::DockPosition position, int width, int height)
{
  Q_D(DockWidget);
  d->setCornerSize(position, width, height);
}

void
DockWidget::setCornerSize(Docker::DockPosition position, QSize size)
{
  Q_D(DockWidget);
  d->setCornerSize(position, size.width(), size.height());
}

void
DockWidget::setCornerWidth(Docker::DockPosition position, int width)
{
  Q_D(DockWidget);
  d->setCornerWidth(position, width);
}

void
DockWidget::setCornerHeight(Docker::DockPosition position, int height)
{
  Q_D(DockWidget);
  d->setCornerHeight(position, height);
}

void
DockWidget::paintEvent(QPaintEvent* event)
{
  Q_D(DockWidget);
  AbstractDockWidget::paintEvent(event);
  QPainter painter(this);
  d->paint(painter);
}

void
DockWidget::hoverEnterEvent(QHoverEvent* event)
{
  Q_D(DockWidget);
  auto p = event->position().toPoint();
  d->hoverEnter(p);
}

void
DockWidget::hoverLeaveEvent(QHoverEvent* /*event*/)
{
  Q_D(DockWidget);
  d->hoverLeave();
}

void
DockWidget::hoverMoveEvent(QHoverEvent* event)
{
  Q_D(DockWidget);
  auto p = event->position().toPoint();
  d->hoverMove(p);
}

void
DockWidget::mousePressEvent(QMouseEvent* event)
{
  Q_D(DockWidget);
  d->mousePress(event);
}

void
DockWidget::mouseMoveEvent(QMouseEvent* event)
{
  Q_D(DockWidget);
  d->mouseMove(event);
}

void
DockWidget::mouseReleaseEvent(QMouseEvent* event)
{
  Q_D(DockWidget);
  d->mouseRelease(event);
}

//void
//DockWidget::dragEnterEvent(QDragEnterEvent* event)
//{
//  event->acceptProposedAction();
//}

//void
//DockWidget::dragMoveEvent(QDragMoveEvent* event)
//{
//  event->acceptProposedAction();
//}

//void DockWidget::dragLeaveEvent(QDragLeaveEvent *event)
//{
//  Q_D(DockWidget);
//  d->m_currentItem = nullptr;
//}

//void
//DockWidget::dropEvent(QDropEvent* event)
//{
//}

bool
DockWidget::event(QEvent* event)
{
  switch (event->type()) {
    case QEvent::HoverEnter:
      hoverEnterEvent(static_cast<QHoverEvent*>(event));
      return true;
      break;
    case QEvent::HoverLeave:
      hoverLeaveEvent(static_cast<QHoverEvent*>(event));
      return true;
      break;
    case QEvent::HoverMove:
      hoverMoveEvent(static_cast<QHoverEvent*>(event));
      return true;
      break;
    default:
      break;
  }
  return QWidget::event(event);
}

void
DockWidget::widgetWasClicked(QPoint pos)
{
  Q_D(DockWidget);
  d->widgetWasClicked(pos);
  // TODO So far only headers and footers have ListWidget's and
  // ListButtonWidgets.
}

void
DockWidget::setCorner(Docker::DockPosition position, Docker::CornerType type)
{
  Q_D(DockWidget);
  d->setCorner(position, type);
}

DockCorner*
DockWidget::corner(Docker::DockPosition position)
{
  Q_D(DockWidget);
  return d->corner(position);
}

void
DockWidget::setCorner(DockCorner* corner)
{
  Q_D(DockWidget);
  d->setCorner(corner);
}
