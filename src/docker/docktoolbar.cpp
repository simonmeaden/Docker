#include "docker/docktoolbar.h"
#include "docker/docktypes.h"
#include "docker/private/abstractdockitemprivate.h"
#include "docker/widgetitem.h"

class DockToolbarPrivate : public AbstractDockItemPrivate
{
  Q_DECLARE_PUBLIC(DockToolbar)
public:
  explicit DockToolbarPrivate(Docker::DockPosition position,
                              AbstractDockWidget* parent,
                              AbstractDockItem* qptr);

  static const int WIDTH = 60;
  static const int HEIGHT = 60;

  Docker::DockPosition dockPosition();
  void setDockPosition(Docker::DockPosition position);

  QSize sizeHint() const;

  void paint(QPainter& painter);

protected:
  /*!
   * \brief Creates a clone of the DockToolbar into item if item is a
   * DockToolbar.
   */
  void clone(AbstractDockItem* item);
};

//====================================================================
//=== DockToolbarPrivate
//====================================================================
DockToolbarPrivate::DockToolbarPrivate(Docker::DockPosition position,
                                       AbstractDockWidget* parent,
                                       AbstractDockItem* qptr)
  : AbstractDockItemPrivate(position, parent, qptr)
{
}

Docker::DockPosition
DockToolbarPrivate::dockPosition()
{
  return m_dockPosition;
}

void
DockToolbarPrivate::setDockPosition(Docker::DockPosition position)
{
  m_dockPosition = position;
}

QSize
DockToolbarPrivate::sizeHint() const
{
  auto w = m_width;
  auto h = m_height;
  switch (m_dockPosition) {
    case Docker::North:
    case Docker::South: {
      for (auto widget : m_widgets) {
        auto s = widget->sizeHint();
        w += s.width();
        h = (h > s.height() ? h : s.height());
      }
      return QSize(w, h).grownBy(m_margins);
    }
    case Docker::East:
    case Docker::West: {
      for (auto widget : m_widgets) {
        auto s = widget->sizeHint();
        w = (w > s.width() ? w : s.width());
        h += s.height();
      }
      return QSize(w, h);
    }
    default:
      break;
  }
  return QSize();
}

void
DockToolbarPrivate::paint(QPainter& painter)
{
  if (m_visible) {
    AbstractDockItemPrivate::paint(painter);

    auto pen = painter.pen();
    pen.setColor(QColor(55, 56, 56));
    pen.setWidth(1);
    painter.setPen(pen);
    switch (m_dockPosition) {
      case Docker::West:
      case Docker::East:
        painter.drawLine(m_rect.x(), m_rect.y(), m_rect.width(), m_rect.y());
        painter.drawLine(m_rect.x(), m_rect.y(), m_rect.x(), m_rect.height());
        break;
      case Docker::North:
      case Docker::South:
        painter.drawLine(m_rect.x(), m_rect.y(), m_rect.x(), m_rect.height());
        painter.drawLine(m_rect.x(), m_rect.y(), m_rect.width(), m_rect.y());
        break;
      default:
        break;
    }
  }
}

void
DockToolbarPrivate::clone(AbstractDockItem* item)
{
  auto toolbar = qobject_cast<DockToolbar*>(item);
  if (toolbar) {
    AbstractDockItemPrivate::clone(toolbar);
  }
}

//====================================================================
//=== DockToolbar
//====================================================================
DockToolbar::DockToolbar(Docker::DockPosition position, AbstractDockWidget* parent)
  : AbstractDockItem(*new DockToolbarPrivate(position, parent, this))
{
  setPreferredSize(WIDTH, HEIGHT);
}

DockToolbar::DockToolbar(DockToolbarPrivate& d)
  : AbstractDockItem(d)
{
}

ButtonWidget*
DockToolbar::addIconButton(Docker::WidgetPosition pos,
                           QPixmap pixmap,
                           const QString& tooltip)
{
  Q_D(AbstractDockItem);
  return d->addIconButton(pos, pixmap,  tooltip);
}

ButtonWidget*
DockToolbar::addDragIconButton(Docker::WidgetPosition pos,
                               QPixmap pixmap,
                               const QString& tooltip)
{
  Q_D(AbstractDockItem);
  return d->addDragIconButton(pos, pixmap,  tooltip);
}

ButtonWidget*
DockToolbar::addIconListButton(Docker::WidgetPosition pos,
                               QPixmap pixmap,
                               const QString& tooltip)
{
  return d_ptr->addIconListButton(pos, pixmap,  tooltip);
}

ButtonWidget*
DockToolbar::addIconTextButton(Docker::WidgetPosition pos,
                               QPixmap pixmap,
                               const QString& text,
                               Docker::Arrangement textPos,
                               const QString& tooltip)
{
  return d_ptr->addIconTextButton(
    pos, pixmap, text, textPos, tooltip);
}

ButtonWidget*
DockToolbar::addIconTextListButton(Docker::WidgetPosition pos,
                                   QPixmap pixmap,
                                   const QString& text,
                                   Docker::Arrangement textPos,
                                   const QString& tooltip)
{
  return d_ptr->addIconTextListButton(
    pos, pixmap,  text, textPos, tooltip);
}

ButtonWidget*
DockToolbar::addTextButton(Docker::WidgetPosition pos,
                           const QString& text,
                           const QString& tooltip)
{
  return d_ptr->addTextButton(pos, text, tooltip);
}

ButtonWidget*
DockToolbar::addTextListButton(Docker::WidgetPosition pos,
                               const QString& text,
                               const QString& tooltip)
{
  return d_ptr->addTextListButton(pos, text, tooltip);
}

WidgetItem*
DockToolbar::addTextLabel(Docker::WidgetPosition pos,
                          const QString& text,
                          const QString& tooltip)
{
  return d_ptr->addTextLabel(pos, text, tooltip);
}

WidgetItem*
DockToolbar::addSeperator(Docker::WidgetPosition pos)
{
  return d_ptr->addSeperator(pos);
}

WidgetItem*
DockToolbar::addCustomWidget(CustomWidget* item)
{
  return d_ptr->addCustomWidget(item);
}

Docker::DockPosition
DockToolbar::dockPosition()
{
  return d_ptr->dockPosition();
}

void
DockToolbar::setDockPosition(Docker::DockPosition position)
{
  Q_D(DockToolbar);
  d->setDockPosition(position);
}

QSize
DockToolbar::sizeHint() const
{
  return d_ptr->sizeHint();
}

void
DockToolbar::paint(QPainter& painter)
{
  d_ptr->paint(painter);
}

void
DockToolbar::clone(QObject* item)
{
  auto awidget = qobject_cast<DockToolbar*>(item);
  if (awidget)
    d_ptr->clone(awidget);
}
