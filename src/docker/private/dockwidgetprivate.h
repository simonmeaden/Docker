#ifndef DOCKWIDGETPRIVATE_H
#define DOCKWIDGETPRIVATE_H

#include "abstractdockwidgetprivate.h"
#include "docker/dockwidget.h"

class DockFooter;
class DockHeader;
class DockCorner;
class DockToolbar;

class DockWidgetPrivate : public AbstractDockWidgetPrivate
{
  Q_DECLARE_PUBLIC(DockWidget)
public:
  DockWidgetPrivate(DockWidget* parent);

//  QWidget* widget() const;
//  QWidget* setWidget(QWidget* widget);

  DockToolbar* addToolbar(Docker::DockPosition position);
  void removeToolbar(Docker::DockPosition position);
  void removeToolbar(DockToolbar* toolbar);
  void hideToolbar(Docker::DockPosition position);
  void hideToolbar(DockToolbar* toolbar);
  void showToolbar(Docker::DockPosition position);
  void showToolbar(DockToolbar* toolbar);

  DockFooter* addFooter();
  void removeFooter();
  void hideFooter();
  void showFooter();

  DockHeader* addHeader();
  void removeHeader();
  void hideHeader();
  void showHeader();

  bool moveToolbar(Docker::DockPosition newPosition, Docker::DockPosition oldPosition);

  void setCorner(Docker::DockPosition position, Docker::CornerType type);
  void setCorners(Docker::CornerType northWest,
                  Docker::CornerType northEast,
                  Docker::CornerType southWest,
                  Docker::CornerType southEast);

  void setCornerSize(Docker::DockPosition position, int width, int height);
  void setCornerWidth(Docker::DockPosition position, int width);
  void setCornerHeight(Docker::DockPosition position, int height);

  void paint(QPainter& painter);
  void hoverEnter(QPoint pos);
  void hoverLeave();
  void hoverMove(QPoint pos);

  void mousePress(QMouseEvent *event)  override;
  void mouseMove(QMouseEvent* event) override;
  void mouseRelease(QMouseEvent* event) override;

  DockHeader* header();
  DockFooter* footer();
  DockToolbar* northToolbar();
  DockToolbar* southToolbar();
  DockToolbar* westToolbar();
  DockToolbar* eastToolbar();

  void widgetWasClicked(QPoint);
  void setCorner(DockCorner* corner);
  DockCorner* corner(Docker::DockPosition position);

  AbstractDockWidget* clone(AbstractDockWidget* widget) override;

  //  void initGui();
  void calculateGeometry(const QRect& rect);
  DockToolbar* toolbarAt(Docker::DockPosition position);
  DockToolbar* toolbarTakeAt(Docker::DockPosition position);
  bool setToolbarAt(Docker::DockPosition position, DockToolbar* toolbar = nullptr);

private:
  DockFooter* m_footer = nullptr;
  DockHeader* m_header = nullptr;
  DockCorner* m_northWest = nullptr;
  DockCorner* m_northEast = nullptr;
  DockCorner* m_southWest = nullptr;
  DockCorner* m_southEast = nullptr;
  DockToolbar* m_northToolbar = nullptr;
  DockToolbar* m_southToolbar = nullptr;
  DockToolbar* m_eastToolbar = nullptr;
  DockToolbar* m_westToolbar = nullptr;
};

#endif // DOCKWIDGETPRIVATE_H
