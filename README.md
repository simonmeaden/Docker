# Docker
A QtCreater style editor layout.
======================================================

Defines a set of QWidget's that emulate, sort of, the QtCreator style editor layout.

Each allow the addition of any of left, right, top or botton toolbars

There are three primary widgets:

- DockerWidget
    This allows optional header or footer and/or one or more of a left, right, top or 
    botton toolbars to be added.

- HeaderWidget
    This comes with a header and optionally any of the toolbars.

- FooterWidget
    This comes with a footer and optionally any of the toolbars.

Toolbars, headers and footers can have any number of widgets added form the following
list.

- ButtonWidget
    These come in several varieties:
    - A simple text button
    - An icon button
    - A button with both text and icon.
        The text can be either above, below or to the left ot right.
    - A list button
    - A draggable button
- A ListWidget, similar to a ListWidget
- A LabelWidget, similar to a QLabel
- A SeperatorWidget
- A CustomWidget. 
    This actually does nothing but can be used a a base for your own custom
    widget classes.
    




