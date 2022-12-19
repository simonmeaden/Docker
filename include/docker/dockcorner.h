#ifndef DOCKCORNER_H
#define DOCKCORNER_H

#include "docker/abstractdockitem.h"
#include "docker/abstractdockwidget.h"
#include "docker/private/abstractdockitemprivate.h"

class DockCorner;

/*!
 * \ingroup docker
 * \class DockCorner dockcorner.h "includes/docker/dockcorner.h"
 * \brief The DockCorner class defines the appearance of the corners of the
 * dockwidget.
 *
 *
 */
class DockCornerPrivate;
class DockCorner : public AbstractDockItem
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(DockCorner)
public:
  /*!
   * \brief Constructor for a DockCorner specifying type, position and parent.
   *
   *  Type has three useable values, Box, VEdge and HEdge. None can have
   *  unexpected results depending on addition order.
   *
   *  * Box which specifies a blank box at the corner.
   *  * VEdge which allow the North/South items to reach the edges.
   *          East/West items butt against the North/South items.
   *  * HEdge which allow the West/East items to reach the edges.
   *          North/South items butt against the East/West items.
   *  * None No corner is specified and the layout will depend on
   *         addition order.
   *
   *  Position specifies which corner. Docker::DockPosition actually has nine possible
   *  values, but only four Docker::DockPosition::NorthEast, Docker::DockPosition::NorthWest,
   *  Docker::DockPosition::SouthEast and Docker::DockPosition::SouthWest are valid for a
   *  DockCorner. Using other values can have anomalous results.
   */
  DockCorner(Docker::CornerType type,
             Docker::DockPosition position,
             AbstractDockWidget* parent);

  //! Returns the Docker::DockPosition for this DockCorner.
  Docker::DockPosition dockPosition();
  //! Sets the Docker::DockPosition for this DockCorner.
  void setDockPosition(Docker::DockPosition position);

  //! Returns the CornerType for this DockCorner.
  Docker::CornerType type();
  //! Sets the CornerType for this DockCorner.
  void setType(Docker::CornerType type);

  //! Returns the size hint for this DockCorner.
  QSize sizeHint() const override;


  //! Clones the DockCorner.
  void clone(QObject* item) override;

protected:
  //! d_ptr constructor
  DockCorner(DockCornerPrivate& d);

private:

  //! Painter function for DockCorner.
  void paint(QPainter& painter) override;

  friend class HeaderWidget;
  friend class FooterWidget;
  friend class HeaderFooterWidget;
  friend class DockWidget;
  friend class DockWidgetPrivate;
};


#endif // DOCKCORNER_H
