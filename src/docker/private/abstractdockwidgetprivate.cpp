#include "docker/private/abstractdockwidgetprivate.h"
#include "docker/abstractdockitem.h"
#include "docker/abstractdockwidget.h"
#include "docker/draggablebuttonwidget.h"
#include "docker/listbuttonwidget.h"
#include "docker/listwidget.h"
#include "utilities/x11colors.h"

#include <CuteLogger/Logger.h>

AbstractDockWidgetPrivate::AbstractDockWidgetPrivate(
  AbstractDockWidget* dockWidget)
  : q_ptr(dockWidget)
  , m_parent(dockWidget)
  , m_backColor(QColorConstants::X11::grey25)
  , m_hoverBackColor(QColorConstants::X11::grey43)
  , m_selectedColor(QColorConstants::X11::grey18)
  , m_spacerColor(QColorConstants::X11::DimGrey)
  , m_layout(new QHBoxLayout)
{
}

const QColor&
AbstractDockWidgetPrivate::textColor() const
{
  return m_textColor;
}

void
AbstractDockWidgetPrivate::setTextColor(const QColor& newTextColor)
{
  m_textColor = newTextColor;
}

const QColor&
AbstractDockWidgetPrivate::spacerColor() const
{
  return m_spacerColor;
}

void
AbstractDockWidgetPrivate::setSpacerColor(const QColor& newSpacerColor)
{
  m_spacerColor = newSpacerColor;
}

const QRect&
AbstractDockWidgetPrivate::availableRect() const
{
  return m_availableRect;
}

void
AbstractDockWidgetPrivate::setAvailableRect(const QRect& availableRect)
{
  m_availableRect = availableRect;
}

void
AbstractDockWidgetPrivate::checkForOpenListWidgets(AbstractDockItem* item)
{
  if (item) {
    for (auto widget : item->widgets()) {
      auto lw = qobject_cast<ListWidget*>(widget);
      if (lw && lw->isVisible()) {
        lw->hideWidget();
      }
      auto lbw = qobject_cast<ListButtonWidget*>(widget);
      if (lbw && lbw->isVisible()) {
        lbw->hideWidget();
      }
    }
  }
}

AbstractDockWidget*
AbstractDockWidgetPrivate::clone(AbstractDockWidget* widget)
{
  widget->setBackColor(m_backColor);
  widget->setHoverBackColor(m_hoverBackColor);
  widget->setSelectedColor(m_selectedColor);
  widget->setTextColor(m_textColor);
  widget->setSpacerColor(m_spacerColor);
  widget->setLayout(new QHBoxLayout);
  return widget;
}

QWidget*
AbstractDockWidgetPrivate::setCentralWidget(QWidget* widget)
{
  if (widget == m_centralWidget)
    return widget;

  auto oldWidget = m_centralWidget;
  if (oldWidget) {
    m_layout->removeWidget(oldWidget);
  }
  m_centralWidget = widget;
  m_centralWidget->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Expanding);
  m_layout->addWidget(m_centralWidget);
  return oldWidget;
}

const QBrush&
AbstractDockWidgetPrivate::backColor() const
{
  return m_backColor;
}

void
AbstractDockWidgetPrivate::setBackColor(const QBrush& newBackColor)
{
  m_backColor = newBackColor;
}

const QBrush&
AbstractDockWidgetPrivate::hoverBackColor() const
{
  return m_hoverBackColor;
}

void
AbstractDockWidgetPrivate::setHoverBackColor(const QBrush& newHoverBackColor)
{
  m_hoverBackColor = newHoverBackColor;
}

const QBrush&
AbstractDockWidgetPrivate::selectedColor() const
{
  return m_selectedColor;
}

void
AbstractDockWidgetPrivate::setSelectedColor(const QBrush& newSelectedColor)
{
  m_selectedColor = newSelectedColor;
}

bool
AbstractDockWidgetPrivate::dockItemHoverCheck(AbstractDockItem* item,
                                              QPoint pos)
{
  Q_Q(AbstractDockWidget);
  if (item) {
    auto widgets = item->widgets();
    for (auto& w : widgets) {
      if (w->rect().contains(pos)) {
        if (m_hoverItem && w != m_hoverItem) {
          m_hoverItem->setHoverOver(false);
          QToolTip::hideText();
          m_hoverItem = nullptr;
        }
        w->setHoverOver(true);
        if (!w->tooltip().isEmpty()) {
          QToolTip::showText(
            q->mapToGlobal(pos), w->tooltip(), q_ptr, w->rect());
        }
        m_hoverItem = w;
        return true;
      }
    }
  }
  return false;
}

void
AbstractDockWidgetPrivate::mousePressCheck(AbstractDockItem* item,
                                           QMouseEvent* event)
{
  Q_Q(AbstractDockWidget);
  auto widgets = item->widgets();
  auto pos = event->pos();
  auto buttons = event->buttons();

  for (auto& w : widgets) {
    if (w->rect().contains(pos)) {
      if (w->isEnabled()) {
        switch (w->type()) {
          case Docker::Button: {
            auto bl = w->rect().bottomLeft();
            emit w->widgetClicked(bl);
            w->setSelected(true);
            return;
          }
          case Docker::DragButton: {
            auto dragBtn = qobject_cast<DraggableButtonWidget*>(w);
            if (dragBtn) {
              if (buttons.testFlag(Qt::LeftButton)) {
                m_dragStartPosition = pos;
                LOG_DEBUG() << QString("pos: %1, %2").arg(pos.x(), pos.y());
              }
              auto bl = w->rect().bottomLeft();
              emit w->widgetClicked(bl);
              w->setSelected(true);
            }
            m_currentItem = w;
            return;
          }
          case Docker::MenuButton: {
            auto listWidget = qobject_cast<ListButtonWidget*>(w);
            if (listWidget && listWidget->isVisible()) {
              listWidget->hideWidget();
            } else {
              w->setSelected(true);
              if (listWidget) {
                listWidget->showList();
              }
            }
            return;
          }
          case Docker::List: {
            auto listWidget = qobject_cast<ListWidget*>(w);
            if (listWidget && listWidget->isVisible()) {
              listWidget->hideWidget();
            } else {
              w->setSelected(true);
              if (listWidget) {
                listWidget->showList();
              }
            }
            return;
          }
          default:
            break;
        }
      }
    }
  }

  if (q->rect().contains(pos)) {
    for (auto widget : widgets) {
      auto lbw = qobject_cast<ListButtonWidget*>(widget);
      if (lbw && lbw->isVisible()) {
        lbw->hideWidget();
      }
      auto lw = qobject_cast<ListWidget*>(widget);
      if (lw && lw->isVisible()) {
        lw->hideWidget();
      }
    }
  }
}

void
AbstractDockWidgetPrivate::mouseMoveCheck(AbstractDockItem* /*item*/,
                                          QMouseEvent* event)
{
  // TODO
  if (!(event->buttons() & Qt::LeftButton))
    return;

  if ((event->pos() - m_dragStartPosition).manhattanLength() <
      QApplication::startDragDistance())
    return;

  if (m_currentItem) {
    auto dragBtn = qobject_cast<DraggableButtonWidget*>(m_currentItem);
    if (dragBtn) {
      m_currentItem = nullptr;
      LOG_DEBUG() << "";
      auto hotSpot = event->position().toPoint() - dragBtn->rect().topLeft();
      auto drag = new QDrag(m_parent);
      auto mimeData = new QMimeData;
      auto mimetype = dragBtn->mimeType();
      mimeData->setData(mimetype, dragBtn->data(mimetype));
      drag->setMimeData(mimeData);
      drag->setPixmap(dragBtn->dragPixmap());
      drag->setHotSpot(hotSpot);
      drag->exec(Qt::MoveAction);
    }
  }
}

void
AbstractDockWidgetPrivate::mouseReleaseCheck(AbstractDockItem* /*item*/,
                                             QMouseEvent* /*event*/)
{
  LOG_DEBUG() << "Empty";
  //  // TODO
  //  if (m_currentItem) {
  //    m_currentItem = nullptr;
  //  }
}
