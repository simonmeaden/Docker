#include "docker/dockheader.h"
#include "docker/abstractdockwidget.h"
#include "docker/listwidget.h"
#include "docker/private/abstractdockitemprivate.h"
#include "docker/widgetitem.h"

class DockHeader;
class DockHeaderPrivate : public AbstractDockItemPrivate
{
  Q_DECLARE_PUBLIC(DockHeader)
public:
  explicit DockHeaderPrivate(AbstractDockWidget* parent,
                             AbstractDockItem* item);

  QSize sizeHint() const;

  void paint(QPainter& painter);
  WidgetItem* addListWidget(Docker::WidgetPosition pos,
                            const QString& tooltip = QString());
  void clone(AbstractDockItem* item);

protected:
private:
  static const int HEIGHT = 26;
  static const int WIDTH = 26;
};

//====================================================================
//=== DockHeaderPrivate
//====================================================================
DockHeaderPrivate::DockHeaderPrivate(AbstractDockWidget* parent,
                                     AbstractDockItem* item)
  : AbstractDockItemPrivate(Docker::North, parent, item)
{
  setPreferredSize(WIDTH, HEIGHT);
}

QSize
DockHeaderPrivate::sizeHint() const
{
  auto w = m_width;
  auto h = m_height;
  for (auto widget : m_widgets) {
    auto s = widget->sizeHint();
    w += s.width();
    h = (h > s.height() ? h : s.height());
  }
  return QSize(w, h);
}

void
DockHeaderPrivate::paint(QPainter& painter)
{
  if (m_visible) {
    AbstractDockItemPrivate::paint(painter);

    auto pen = painter.pen();
    pen.setColor(QColor(55, 56, 56));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(m_rect.x(), m_rect.y(), m_rect.x(), m_rect.height());
    painter.drawLine(m_rect.x(), m_rect.y(), m_rect.width(), m_rect.y());
  }
}

void
DockHeaderPrivate::clone(AbstractDockItem* item)
{
  if (item) {
    AbstractDockItemPrivate::clone(item);
  }
}

WidgetItem*
DockHeaderPrivate::addListWidget(Docker::WidgetPosition pos, const QString& tooltip)
{
  auto widget = new ListWidget(m_parentDocker, q_ptr);
  widget->setTooltip(tooltip);
  int height = 0;
  auto textRect = widget->textRect();
  auto fm = m_parentDocker->fontMetrics();
  textRect.setHeight(fm.height());
  widget->setTextRect(textRect);
  height = widget->topMargin() + fm.height() + widget->bottomMargin();
  m_maxWidgetHeight = std::max(height, m_maxWidgetHeight);

  widget->setType(Docker::List);
  widget->setWidgetPosition(pos);
  m_widgets.append(widget);

  setPreferredSize(m_maxWidgetWidth, m_maxWidgetHeight);
  calcMaxWidgetSizes();
  q_ptr->connect(widget,
                 &WidgetItem::widgetChanged,
                 q_ptr,
                 &AbstractDockItem::calcMaxWidgetSizes);
  return widget;
}

//====================================================================
//=== DockHeader
//====================================================================
DockHeader::DockHeader(AbstractDockWidget* parent)
  : AbstractDockItem(*new DockHeaderPrivate(parent, this))
{
  setPreferredSize(WIDTH, HEIGHT);
}

DockHeader::DockHeader(DockHeaderPrivate& d)
  : AbstractDockItem(d)
{
}

ButtonWidget*
DockHeader::addIconButton(Docker::WidgetPosition pos,
                          QPixmap pixmap,
                          const QString& tooltip)
{
  Q_D(AbstractDockItem);
  return d->addIconButton(pos, pixmap, tooltip);
}

ButtonWidget*
DockHeader::addDragIconButton(Docker::WidgetPosition pos,
                              QPixmap pixmap,
                              const QString& tooltip)
{
  Q_D(AbstractDockItem);
  return d->addIconButton(pos, pixmap, tooltip);
}

ButtonWidget*
DockHeader::addIconListButton(Docker::WidgetPosition pos,
                              QPixmap pixmap,
                              const QString& tooltip)
{
  return d_ptr->addIconListButton(pos, pixmap, tooltip);
}

ButtonWidget*
DockHeader::addIconTextButton(Docker::WidgetPosition pos,
                              QPixmap pixmap,
                              const QString& text,
                              Docker::Arrangement textPos,
                              const QString& tooltip)
{
  return d_ptr->addIconTextButton(pos, pixmap, text, textPos, tooltip);
}

ButtonWidget*
DockHeader::addIconTextListButton(Docker::WidgetPosition pos,
                                  QPixmap pixmap,
                                  const QString& text,
                                  Docker::Arrangement textPos,
                                  const QString& tooltip)
{
  return d_ptr->addIconTextListButton(pos, pixmap, text, textPos, tooltip);
}

ButtonWidget*
DockHeader::addTextButton(Docker::WidgetPosition pos,
                          const QString& text,
                          const QString& tooltip)
{
  return d_ptr->addTextButton(pos, text, tooltip);
}

ButtonWidget*
DockHeader::addTextListButton(Docker::WidgetPosition pos,
                              const QString& text,
                              const QString& tooltip)
{
  return d_ptr->addTextListButton(pos, text, tooltip);
}

WidgetItem*
DockHeader::addTextLabel(Docker::WidgetPosition pos,
                         const QString& text,
                         const QString& tooltip)
{
  return d_ptr->addTextLabel(pos, text, tooltip);
}

WidgetItem*
DockHeader::addSeperator(Docker::WidgetPosition pos)
{
  return d_ptr->addSeperator(pos);
}

WidgetItem*
DockHeader::addCustomWidget(CustomWidget* item)
{
  return d_ptr->addCustomWidget(item);
}

QSize
DockHeader::sizeHint() const
{
  return d_ptr->sizeHint();
}

void
DockHeader::paint(QPainter& painter)
{
  d_ptr->paint(painter);
}

void
DockHeader::clone(QObject* item)
{
  auto anobject = qobject_cast<DockHeader*>(item);
  if (anobject)
    d_ptr->clone(anobject);
}

WidgetItem*
DockHeader::addListWidget(Docker::WidgetPosition pos, const QString& tooltip)
{
  Q_D(DockHeader);
  return d->addListWidget(pos, tooltip);
}
