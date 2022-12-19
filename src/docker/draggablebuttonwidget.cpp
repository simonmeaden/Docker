#include "docker/draggablebuttonwidget.h"
#include "docker/private/draggablebuttonwidgetprivate.h"

DraggableButtonWidget::DraggableButtonWidget(AbstractDockWidget* parent)
  : ButtonWidget(*new DraggableButtonWidgetPrivate(parent, this))
{
}

DraggableButtonWidget::DraggableButtonWidget(const QString mimetype,
                                             AbstractDockWidget* parent)
  : ButtonWidget(*new DraggableButtonWidgetPrivate(parent, this))
  , m_mimeType(mimetype)
{
}

DraggableButtonWidget::DraggableButtonWidget(DraggableButtonWidgetPrivate& d)
  : ButtonWidget(d)
{
}

const QPixmap&
DraggableButtonWidget::dragPixmap()
{
  if (m_dragPixmap.isNull()) {
    return pixmap();
  }
  return m_dragPixmap;
}

void
DraggableButtonWidget::setDragPixmap(const QPixmap& dragPixmap)
{
  m_dragPixmap = dragPixmap;
}

const QByteArray
DraggableButtonWidget::data(const QString& mimeType) const
{
  if (mimeType == m_mimeType)
    return m_data;
  return QByteArray();
}

void
DraggableButtonWidget::setData(const QString& mimeType, const QByteArray& Data)
{
  m_mimeType = mimeType;
  m_data = Data;
}

const QString &DraggableButtonWidget::mimeType() const
{
  return m_mimeType;
}
