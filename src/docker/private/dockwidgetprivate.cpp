#include "docker/private/dockwidgetprivate.h"
#include "docker/dockcorner.h"
#include "docker/dockfooter.h"
#include "docker/dockheader.h"
#include "docker/docktoolbar.h"
#include "docker/widgetitem.h"

DockWidgetPrivate::DockWidgetPrivate(DockWidget* parent)
  : AbstractDockWidgetPrivate(parent)
{
}

void
DockWidgetPrivate::calculateGeometry(const QRect& rect)
{
  auto eastWidth = 0;
  auto eastHeight = rect.height();
  auto eastX = 0;
  auto eastY = 0;
  auto westWidth = 0;
  auto westHeight = rect.height();
  auto westX = 0;
  auto westY = 0;
  auto northHeight = 0;
  auto northToolbarHeight = 0;
  auto headerY = 0;
  auto headerHeight = 0;
  auto northWidth = rect.width();
  auto northX = 0;
  auto southWidth = rect.width();
  auto southHeight = 0;
  auto southX = 0;
  auto southY = rect.height();
  auto footerHeight = 0;
  auto footerY = 0;
  auto southToolbarHeight = 0;
  auto southToolbarY = 0;

  if (m_northToolbar) {
    northToolbarHeight = m_northToolbar->sizeHint().height();
    northHeight += northToolbarHeight;
  }

  if (m_header) {
    headerHeight = m_header->sizeHint().height();
    northHeight += headerHeight;
    headerY = northToolbarHeight;
  }

  if (m_footer) {
    footerHeight = m_footer->sizeHint().height();
    southHeight = footerHeight;
    southY -= footerHeight;
    footerY = southY;
  }

  if (m_southToolbar) {
    southToolbarHeight = m_southToolbar->sizeHint().height();
    southHeight += southToolbarHeight;
    southY -= southToolbarHeight;
    southToolbarY = southY;
  }

  if (m_eastToolbar) {
    eastWidth += m_eastToolbar->sizeHint().width();
    eastX = rect.width() - eastWidth;
  }

  if (m_westToolbar) {
    westWidth += m_westToolbar->sizeHint().width();
  }

  if (m_northEast) {
    switch (m_northEast->type()) {
      case Docker::Box: {
        m_northEast->calculateGeometry(
          QRect(rect.x() + rect.width() - eastWidth,
                rect.y(),
                eastWidth,
                northHeight));
        northWidth -= eastWidth;
        eastHeight -= northHeight;
        eastX = rect.width() - eastWidth;
        eastY = northHeight;
        break;
      }
      case Docker::VEdge: {
        m_northEast->calculateGeometry(
          QRect(rect.width(), rect.y(), 0, northHeight));
        eastHeight -= northHeight;
        eastX = rect.width() - eastWidth;
        eastY = northHeight;
        break;
      }
      case Docker::HEdge: {
        m_northEast->calculateGeometry(
          QRect(rect.width() - eastWidth, rect.y(), eastWidth, 0));
        northWidth -= eastWidth;
        eastX = rect.width() - eastWidth;
        break;
      }
      case Docker::None:
        break;
    }
  }

  if (m_northWest) {
    switch (m_northWest->type()) {
      case Docker::Box: {
        m_northWest->calculateGeometry(
          QRect(rect.x(), rect.y(), westWidth, northHeight));
        northWidth -= westWidth;
        northX = westWidth;
        westHeight -= northHeight;
        westY = northHeight;
        break;
      }
    case Docker::VEdge: {
        m_northWest->calculateGeometry(
          QRect(rect.x(), rect.y(), 0, northHeight));
        northX = westWidth;
        break;
      }
    case Docker::HEdge: {
        m_northWest->calculateGeometry(QRect(rect.x(), rect.y(), westWidth, 0));
        northWidth -= westWidth;
        northX = westWidth;
        break;
      }
    case Docker::None:
        break;
    }
  }

  if (m_southEast) {
    switch (m_southEast->type()) {
    case Docker::Box: {
        m_southEast->calculateGeometry(
          QRect(rect.x(), rect.height() - southHeight, eastWidth, southHeight));
        southWidth -= eastWidth;
        eastHeight -= southHeight;
        break;
      }
    case Docker::VEdge: {
        m_southEast->calculateGeometry(
          QRect(rect.width(), rect.height() - southHeight, 0, southHeight));
        eastHeight -= southHeight;
        break;
      }
    case Docker::HEdge: {
        m_southEast->calculateGeometry(QRect(
          rect.width() - eastWidth, rect.height() - southHeight, eastWidth, 0));
        southWidth -= eastWidth;
        break;
      }
    case Docker::None:
        break;
    }
  }

  if (m_southWest) {
    switch (m_southWest->type()) {
    case Docker::Box: {
        m_southWest->calculateGeometry(
          QRect(rect.x(), rect.height() - southHeight, westWidth, southHeight));
        southWidth -= westWidth;
        southX = westWidth;
        westHeight -= southHeight;
        break;
      }
    case Docker::VEdge: {
        m_southWest->calculateGeometry(
          QRect(rect.x(), rect.height() - southHeight, 0, southHeight));
        westHeight -= southHeight;
        break;
      }
    case Docker::HEdge: {
        m_southWest->calculateGeometry(
          QRect(rect.x(), rect.height() - southHeight, westWidth, 0));
        southX = westWidth;
        southWidth -= westWidth;
        break;
      }
    case Docker::None:
        break;
    }
  }

  if (m_westToolbar) {
    m_westToolbar->calculateGeometry(
      QRect(westX, westY, westWidth, westHeight));
  }

  if (m_eastToolbar) {
    m_eastToolbar->calculateGeometry(
      QRect(eastX, eastY, eastWidth, eastHeight));
  }

  if (m_northToolbar) {
    m_northToolbar->calculateGeometry(
      QRect(northX, 0, northWidth, northToolbarHeight));
  }

  if (m_header) {
    m_header->calculateGeometry(
      QRect(northX, headerY, northWidth, headerHeight));
  }

  if (m_southToolbar) {
    m_southToolbar->calculateGeometry(
      QRect(southX, southToolbarY, southWidth, southToolbarHeight));
  }

  if (m_footer) {
    m_footer->calculateGeometry(
      QRect(southX, footerY, southWidth, footerHeight));
  }

  if (m_northEast) {
    switch (m_northEast->type()) {
    case Docker::Box: {
        m_northEast->calculateGeometry(QRect(eastX, 0, eastWidth, northHeight));
        break;
      }
    case Docker::VEdge: {
        m_northEast->calculateGeometry(QRect(rect.y(), 0, 0, northHeight));
        break;
      }
    case Docker::HEdge: {
        m_northEast->calculateGeometry(QRect(eastX, 0, eastWidth, 0));
        break;
      }
    case Docker::None:
        break;
    }
  }

  if (m_northWest) {
    switch (m_northWest->type()) {
    case Docker::Box: {
        m_northWest->calculateGeometry(QRect(westX, 0, westWidth, northHeight));
        break;
      }
    case Docker::VEdge: {
        m_northWest->calculateGeometry(QRect(westX, 0, 0, northHeight));
        break;
      }
    case Docker::HEdge: {
        m_northWest->calculateGeometry(QRect(westX, 0, westWidth, 0));
        break;
      }
    case Docker::None:
        break;
    }
  }

  if (m_southEast) {
    switch (m_southEast->type()) {
    case Docker::Box: {
        m_southEast->calculateGeometry(
          QRect(eastX, southY, eastWidth, southHeight));
        break;
      }
    case Docker::VEdge: {
        m_southEast->calculateGeometry(QRect(rect.y(), southY, 0, southHeight));
        break;
      }
    case Docker::HEdge: {
        m_southEast->calculateGeometry(QRect(eastX, southY, eastWidth, 0));
        break;
      }
    case Docker::None:
        break;
    }
  }

  if (m_southWest) {
    switch (m_southWest->type()) {
    case Docker::Box: {
        m_southWest->calculateGeometry(
          QRect(westX, southY, westWidth, southHeight));
        break;
      }
    case Docker::VEdge: {
        m_southWest->calculateGeometry(QRect(westX, southY, 0, southHeight));
        break;
      }
    case Docker::HEdge: {
        m_southWest->calculateGeometry(QRect(westX, southY, westWidth, 0));
        break;
      }
    case Docker::None:
        break;
    }
  }

  auto availableRect = this->availableRect();
  availableRect.setHeight(rect.height() - northHeight - southHeight);
  availableRect.setWidth(rect.width() - eastWidth - westWidth);
  availableRect.moveTopLeft(QPoint(westWidth, northHeight));
  this->setAvailableRect(availableRect);

  if (m_centralWidget) {
    m_layout->setContentsMargins(
      westWidth, northHeight, eastWidth, southHeight);
  }
}

// void
// DockWidgetPrivate::initGui()
//{
//   auto f = font();
//   f.setPointSize(8);
//   setFont(f);

//  m_layout = new QHBoxLayout;
//  setLayout(m_layout);
//}

DockToolbar*
DockWidgetPrivate::addToolbar(Docker::DockPosition position)
{
  auto toolbar = toolbarAt(position);
  if (toolbar)
    return toolbar;

  toolbar = new DockToolbar(position, q_ptr);
  setToolbarAt(position, toolbar);

  return toolbar;
}

void
DockWidgetPrivate::removeToolbar(Docker::DockPosition position)
{
  toolbarTakeAt(position);
}

void
DockWidgetPrivate::removeToolbar(DockToolbar* toolbar)
{
  if (toolbar) {
    toolbarTakeAt(toolbar->dockPosition());
    toolbar = nullptr;
  }
}

void
DockWidgetPrivate::hideToolbar(Docker::DockPosition position)
{
  auto toolbar = toolbarAt(position);
  if (toolbar) {
    toolbar->setVisible(false);
  }
}

void
DockWidgetPrivate::hideToolbar(DockToolbar* toolbar)
{
  if (toolbar) {
    toolbar->setVisible(false);
  }
}

void
DockWidgetPrivate::showToolbar(Docker::DockPosition position)
{
  auto toolbar = toolbarAt(position);
  showToolbar(toolbar);
}

void
DockWidgetPrivate::showToolbar(DockToolbar* toolbar)
{
  if (toolbar) {
    toolbar->setVisible(true);
  }
}

bool
DockWidgetPrivate::moveToolbar(Docker::DockPosition newPosition,
                               Docker::DockPosition oldPosition)
{
  auto oldbar = toolbarAt(oldPosition);
  if (!oldbar)
    return false;

  auto newbar = toolbarAt(newPosition);
  if (!newbar)
    return false;

  setToolbarAt(oldPosition);
  auto b = setToolbarAt(newPosition, oldbar);
  newbar->deleteLater();
  return b;
}

AbstractDockWidget*
DockWidgetPrivate::clone(AbstractDockWidget* widget)
{
  DockWidget* w = qobject_cast<DockWidget*>(widget);
  if (!widget)
    w = new DockWidget(q_ptr);
  AbstractDockWidgetPrivate::clone(widget);
  if (m_header)
    m_header->clone(w->header());

  if (m_footer)
    m_footer->clone(w->footer());

  if (m_northToolbar)
    m_northToolbar->clone(w->northToolbar());

  if (m_southToolbar)
    m_southToolbar->clone(w->southToolbar());

  if (m_westToolbar)
    m_westToolbar->clone(w->westToolbar());

  if (m_eastToolbar)
    m_eastToolbar->clone(w->eastToolbar());

  if (m_northWest)
    m_northWest->clone(w->m_northWest);

  if (m_northEast)
    m_northEast->clone(w->m_northEast);

  if (m_southWest)
    m_southWest->clone(w->m_southWest);

  if (m_southEast)
    m_southEast->clone(w->m_southEast);

  return w;
}

DockHeader*
DockWidgetPrivate::header()
{
  if (m_header)
    return m_header;
  return nullptr;
}

DockFooter*
DockWidgetPrivate::footer()
{
  if (m_footer)
    return m_footer;
  return nullptr;
}

DockToolbar*
DockWidgetPrivate::northToolbar()
{
  if (m_northToolbar)
    return m_northToolbar;
  return nullptr;
}

DockToolbar*
DockWidgetPrivate::southToolbar()
{
  if (m_southToolbar)
    return m_southToolbar;
  return nullptr;
}

DockToolbar*
DockWidgetPrivate::eastToolbar()
{
  if (m_southToolbar)
    return m_eastToolbar;
  return nullptr;
}

DockToolbar*
DockWidgetPrivate::westToolbar()
{
  if (m_westToolbar)
    return m_westToolbar;
  return nullptr;
}

DockToolbar*
DockWidgetPrivate::toolbarAt(Docker::DockPosition position)
{
  switch (position) {
    case Docker::North:
      return m_northToolbar;
    case Docker::South:
      return m_southToolbar;
    case Docker::East:
      return m_eastToolbar;
    case Docker::West:
      return m_westToolbar;
    default:
      return nullptr;
  }
}

DockToolbar*
DockWidgetPrivate::toolbarTakeAt(Docker::DockPosition position)
{
  DockToolbar* toolbar = nullptr;
  switch (position) {
    case Docker::North:
      toolbar = m_northToolbar;
      m_northToolbar->deleteLater();
      m_northToolbar = nullptr;
      break;
    case Docker::South:
      toolbar = m_southToolbar;
      m_southToolbar->deleteLater();
      m_southToolbar = nullptr;
      break;
    case Docker::East:
      toolbar = m_eastToolbar;
      m_eastToolbar->deleteLater();
      m_eastToolbar = nullptr;
      break;
    case Docker::West:
      toolbar = m_westToolbar;
      m_westToolbar->deleteLater();
      m_westToolbar = nullptr;
      break;
    default:
      break;
  }
  return toolbar;
}

bool
DockWidgetPrivate::setToolbarAt(Docker::DockPosition position, DockToolbar* toolbar)
{
  switch (position) {
    case Docker::North:
      m_northToolbar = toolbar;
      break;
    case Docker::South:
      m_southToolbar = toolbar;
      break;
    case Docker::East:
      m_eastToolbar = toolbar;
      break;
    case Docker::West:
      m_westToolbar = toolbar;
      break;
    default:
      return false;
  }
  return true;
}

DockFooter*
DockWidgetPrivate::addFooter()
{
  if (!m_footer) {
    m_footer = new DockFooter(q_ptr);
  }
  return m_footer;
}

void
DockWidgetPrivate::removeFooter()
{
  if (m_footer) {
    m_footer->deleteLater();
    m_footer = nullptr;
  }
}

void
DockWidgetPrivate::hideFooter()
{
  if (m_footer)
    m_footer->setVisible(false);
}

void
DockWidgetPrivate::showFooter()
{
  if (m_footer)
    m_footer->setVisible(true);
}

DockHeader*
DockWidgetPrivate::addHeader()
{
  if (!m_header) {
    m_header = new DockHeader(q_ptr);
  }
  return m_header;
}

void
DockWidgetPrivate::removeHeader()
{
  if (m_header) {
    m_header->deleteLater();
    m_header = nullptr;
    //    repaint();
  }
}

void
DockWidgetPrivate::hideHeader()
{
  if (m_header)
    m_header->setVisible(false);
}

void
DockWidgetPrivate::showHeader()
{
  if (m_header)
    m_header->setVisible(true);
}

void
DockWidgetPrivate::setCorners(Docker::CornerType northWest,
                              Docker::CornerType northEast,
                              Docker::CornerType southWest,
                              Docker::CornerType southEast)
{
  if (northWest != Docker::None) {
    m_northWest = new DockCorner(northWest, Docker::NorthEast, q_ptr);
  }
  if (northEast != Docker::None) {
    m_northEast = new DockCorner(northEast, Docker::NorthWest, q_ptr);
  }
  if (southWest != Docker::None) {
    m_southWest = new DockCorner(southWest, Docker::SouthEast, q_ptr);
  }
  if (southEast != Docker::None) {
    m_southEast = new DockCorner(southEast, Docker::SouthWest, q_ptr);
  }
}

void
DockWidgetPrivate::setCornerSize(Docker::DockPosition position, int width, int height)
{
  auto c = corner(position);
  if (c) {
    c->setWidth(width);
    c->setHeight(height);
  }
}

// void
// DockWidgetPrivate::setCornerSize(Docker::DockPosition position, QSize size)
//{
//   setCornerSize(position, size.width(), size.height());
// }

void
DockWidgetPrivate::setCornerWidth(Docker::DockPosition position, int width)
{
  auto c = corner(position);
  if (c) {
    c->setWidth(width);
  }
}

void
DockWidgetPrivate::setCornerHeight(Docker::DockPosition position, int height)
{
  auto c = corner(position);
  if (c) {
    c->setHeight(height);
  }
}

void
DockWidgetPrivate::paint(QPainter& painter)
{
  if (m_northToolbar)
    m_northToolbar->paint(painter);

  if (m_southToolbar)
    m_southToolbar->paint(painter);

  if (m_eastToolbar)
    m_eastToolbar->paint(painter);

  if (m_westToolbar)
    m_westToolbar->paint(painter);

  if (m_footer)
    m_footer->paint(painter);

  if (m_header)
    m_header->paint(painter);

  if (m_northEast)
    m_northEast->paint(painter);

  if (m_northWest)
    m_northWest->paint(painter);

  if (m_southEast)
    m_southEast->paint(painter);

  if (m_southWest)
    m_southWest->paint(painter);
}

void
DockWidgetPrivate::hoverEnter(QPoint pos)
{
  if (m_footer) {
    if (dockItemHoverCheck(m_footer, pos)) {
      return;
    }
  }
  if (m_header) {
    if (dockItemHoverCheck(m_header, pos)) {
      return;
    }
  }
  if (dockItemHoverCheck(m_eastToolbar, pos)) {
    return;
  }

  if (dockItemHoverCheck(m_westToolbar, pos)) {
    return;
  }

  if (dockItemHoverCheck(m_southToolbar, pos)) {
    return;
  }

  if (dockItemHoverCheck(m_northToolbar, pos)) {
    return;
  }
}

void
DockWidgetPrivate::hoverLeave()
{
  if (m_hoverItem) {
    m_hoverItem->setHoverOver(false);
    QToolTip::hideText();
    m_hoverItem = nullptr;
  }
}

void
DockWidgetPrivate::hoverMove(QPoint pos)
{
  if (m_footer) {
    if (dockItemHoverCheck(m_footer, pos)) {
      return;
    }
  }
  if (m_header) {
    if (dockItemHoverCheck(m_header, pos)) {
      return;
    }
  }
  if (dockItemHoverCheck(m_eastToolbar, pos)) {
    return;
  }

  if (dockItemHoverCheck(m_westToolbar, pos)) {
    return;
  }

  if (dockItemHoverCheck(m_southToolbar, pos)) {
    return;
  }

  if (dockItemHoverCheck(m_northToolbar, pos)) {
    return;
  }
}

void
DockWidgetPrivate::mousePress(QMouseEvent* event)
{
  if (m_footer) {
    mousePressCheck(m_footer, event);
  }
  if (m_header) {
    mousePressCheck(m_header, event);
  }
  if (m_northToolbar) {
    mousePressCheck(m_northToolbar, event);
  }
  if (m_southToolbar) {
    mousePressCheck(m_southToolbar, event);
  }
  if (m_eastToolbar) {
    mousePressCheck(m_eastToolbar, event);
  }
  if (m_westToolbar) {
    mousePressCheck(m_westToolbar, event);
  }
}

void DockWidgetPrivate::mouseMove(QMouseEvent *event)
{
  if (m_footer) {
    mouseMoveCheck(m_footer, event);
  }
  if (m_header) {
    mouseMoveCheck(m_header, event);
  }
  if (m_northToolbar) {
    mouseMoveCheck(m_northToolbar, event);
  }
  if (m_southToolbar) {
    mouseMoveCheck(m_southToolbar, event);
  }
  if (m_eastToolbar) {
    mouseMoveCheck(m_eastToolbar, event);
  }
  if (m_westToolbar) {
    mouseMoveCheck(m_westToolbar, event);
  }
}

void DockWidgetPrivate::mouseRelease(QMouseEvent *event)
{
  if (m_footer) {
    mouseReleaseCheck(m_footer, event);
  }
  if (m_header) {
    mouseReleaseCheck(m_header, event);
  }
  if (m_northToolbar) {
    mouseReleaseCheck(m_northToolbar, event);
  }
  if (m_southToolbar) {
    mouseReleaseCheck(m_southToolbar, event);
  }
  if (m_eastToolbar) {
    mouseReleaseCheck(m_eastToolbar, event);
  }
  if (m_westToolbar) {
    mouseReleaseCheck(m_westToolbar, event);
  }
}

void
DockWidgetPrivate::widgetWasClicked(QPoint /*pos*/)
{
  if (m_header) {
    checkForOpenListWidgets(m_header);
  }
  if (m_footer) {
    checkForOpenListWidgets(m_footer);
  }
  // TODO So far only headers and footers have ListWidget's and
  // ListButtonWidgets.
}

void
DockWidgetPrivate::setCorner(Docker::DockPosition position, Docker::CornerType type)
{
  switch (position) {
    case Docker::NorthEast: {
      m_northEast = new DockCorner(type, position, q_ptr);
      break;
    }
    case Docker::NorthWest: {
      m_northWest = new DockCorner(type, position, q_ptr);
      break;
    }
    case Docker::SouthEast: {
      m_southEast = new DockCorner(type, position, q_ptr);
      break;
    }
    case Docker::SouthWest: {
      m_southWest = new DockCorner(type, position, q_ptr);
      break;
    }
    default:
      break;
  }
}

DockCorner*
DockWidgetPrivate::corner(Docker::DockPosition position)
{
  switch (position) {
    case Docker::NorthEast:
      return m_northEast;
    case Docker::NorthWest:
      return m_northWest;
    case Docker::SouthEast:
      return m_southEast;
    case Docker::SouthWest:
      return m_southWest;
    default:
      return nullptr;
  }
}

void
DockWidgetPrivate::setCorner(DockCorner* corner)
{
  switch (corner->dockPosition()) {
    case Docker::NorthEast:
      m_northEast = corner;
      break;
    case Docker::NorthWest:
      m_northWest = corner;
      break;
    case Docker::SouthEast:
      m_southEast = corner;
      break;
    case Docker::SouthWest:
      m_southWest = corner;
      break;
    default:
      break;
  }
}
