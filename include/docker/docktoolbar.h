#ifndef DOCKTOOLBAR_H
#define DOCKTOOLBAR_H

#include <QFontMetrics>

#include "docker/abstractdockitem.h"

/*!
 * \ingroup docker
 * \class DockToolbar docktoolbar.h "includes/docker/docktoolbar.h"
 * \brief The DockToolbar class defines a DockToolbar object.
 *
 * DockToolbar's are similar to QToolbars in that you can add certain types of
 * widget to them, primarily certain types of ButtonWidget, a LabelWidget or a
 * ListWidget.
 *
 * \sa ButtonWidget
 * \sa DraggableButtonWidget
 * \sa ListButtonWidget
 * \sa LabelWidget
 * \sa ListWidget
 * \sa SeperatorWidget
 *
 */
class DockToolbarPrivate;
class DockToolbar
  : public AbstractDockItem
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(DockToolbar)
public:
  //! Constructor for DockToolbar
  explicit DockToolbar(Docker::DockPosition position, AbstractDockWidget* parent);

  /*!
   * \brief Adds an icon only ButtonWidget to the Header/Footer/Toolbar widget
   * with an optional tooltip.
   *
   * \return a pointer to the stored wrapper.
   */
  ButtonWidget* addIconButton(Docker::WidgetPosition pos,
                              QPixmap pixmap,
                              const QString& tooltip = QString());
  /*!
   * \brief Adds an draggable icon only ButtonWidget to the
   * Header/Footer/Toolbar widget with an optional tooltip.
   *
   * \return a pointer to the stored wrapper.
   */
  ButtonWidget* addDragIconButton(Docker::WidgetPosition pos,
                                  QPixmap pixmap,
                                  const QString& tooltip = QString());
  /*!
   * \brief Adds an icon only ListButtonWidget to the Header/Footer/Toolbar
   * widget with an optional tooltip.
   *
   * \return a pointer to the stored wrapper.
   */
  ButtonWidget* addIconListButton(Docker::WidgetPosition pos,
                                  QPixmap pixmap,
                                  const QString& tooltip = QString());

  /*!
   * \brief Adds an icon with text ButtonWidget to the Header/Footer/Toolbar
   * widget and an optional tooltip.
   *
   * \return a pointer to the stored wrapper.
   */
  ButtonWidget* addIconTextButton(Docker::WidgetPosition pos,
    QPixmap pixmap,
    const QString& text,
    Docker::Arrangement textPos = Docker::Arrangement::TextBelowIcon,
    const QString& tooltip = QString());
  /*!
   * \brief Adds an icon with text ListButtonWidget to the Header/Footer/Toolbar
   * widget and an optional tooltip.
   *
   * \return a pointer to the stored wrapper.
   */
  ButtonWidget* addIconTextListButton(
    Docker::WidgetPosition pos,
    QPixmap pixmap,
    const QString& text,
    Docker::Arrangement textPos = Docker::Arrangement::TextBelowIcon,
    const QString& tooltip = QString());

  /*!
   * \brief Adds an text only ButtonWidget to the Header/Footer/Toolbar widget
   * with an optional tooltip.
   *
   * \return a pointer to the stored wrapper.
   */
  ButtonWidget* addTextButton(Docker::WidgetPosition pos,
                              const QString& text,
                              const QString& tooltip = QString());
  /*!
   * \brief Adds an text only ListButtonWidget to the Header/Footer/Toolbar
   * widget with an optional tooltip.
   *
   * \return a pointer to the stored wrapper.
   */
  ButtonWidget* addTextListButton(Docker::WidgetPosition pos,
                                  const QString& text,
                                  const QString& tooltip = QString());

  /*!
   * \brief Adds a text label to the Header/Footer/Toolbar widget
   * with an optional tooltip.
   *
   * \return a pointer to the stored wrapper.
   */
  WidgetItem* addTextLabel(Docker::WidgetPosition pos,
                           const QString& text,
                           const QString& tooltip = QString());

  /*!
   * \brief addSpacer
   * \return
   */
  WidgetItem* addSeperator(Docker::WidgetPosition);

  /*!
   * \brief Adds a custom widget to the Header/Footer/Toolbar widget.
   */
  WidgetItem* addCustomWidget(CustomWidget* w);

  //! Returns the position of the toolbar.
  Docker::DockPosition dockPosition();
  //! sets the position of the toolbar.
  void setDockPosition(Docker::DockPosition position);

  //! Returns a size hint for this object.
  QSize sizeHint() const override;

  //! Paints the DockToolbar and all of it's child widgets.
  void paint(QPainter& painter) override;

  /*!
   * \brief Creates a clone of the DockToolbar into item if item is a
   * DockToolbar.
   */
  void clone(QObject* item) override;

protected:
  //! d_ptr constructor.
  DockToolbar(DockToolbarPrivate& d);

private:
  static const int WIDTH = 0;
  static const int HEIGHT = 0;

  friend class HeaderWidget;
  friend class FooterWidget;
  friend class DockWidget;
};

#endif // DOCKTOOLBAR_H
