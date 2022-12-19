#ifndef DRAGGABLEBUTTONWIDGET_H
#define DRAGGABLEBUTTONWIDGET_H

#include "docker/buttonwidget.h"

class DraggableButtonWidgetPrivate;
class DraggableButtonWidget : public ButtonWidget
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(DraggableButtonWidget)
public:
  Q_INVOKABLE DraggableButtonWidget(AbstractDockWidget* parent);
  Q_INVOKABLE DraggableButtonWidget(const QString mimetype,
                                    AbstractDockWidget* parent);

  const QPixmap& dragPixmap();
  void setDragPixmap(const QPixmap& dragPixmap);

  const QByteArray data(const QString& mimeType) const;
  void setData(const QString& mimeType,const QByteArray &Data);

  const QString &mimeType() const;

protected:
  QString m_mimeType;
  QPixmap m_dragPixmap;
  QByteArray m_data;

  //! d_ptr constructor.
  DraggableButtonWidget(DraggableButtonWidgetPrivate& d);
};

#endif // DRAGGABLEBUTTONWIDGET_H
