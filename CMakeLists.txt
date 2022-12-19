cmake_minimum_required(VERSION 3.7)

project(Docker VERSION 0.1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} "")
add_library(Docker::Docker ALIAS Docker)

find_package(Qt6
  REQUIRED
  COMPONENTS
    Core
    Gui
    Widgets
    Network
    Xml
    Svg
    LinguistTools
  OPTIONAL_COMPONENTS
    Core5Compat
#  PATHS
#    /opt/Qt/6.4.1/gcc_64/lib
)
if (NOT Qt6_FOUND)
    find_package(Qt5
      REQUIRED
      COMPONENTS
        Core
        Gui
        Widgets
        Network
        Xml
        Svg
        LinguistTools
#      PATHS
#        /opt/Qt/5.15.2/gcc_64/lib
    )
endif()

qt_standard_project_setup()

target_sources(
    ${PROJECT_NAME}

  PRIVATE
    # These have to be added to get MOC to work correctly apparently
    # Not certain if there is a better way - yet.
    include/docker/abstractdockwidget.h
    include/docker/dockwidget.h
    include/docker/abstractdockitem.h
    include/docker/widgetitem.h
    include/docker/dockheader.h
    include/docker/dockfooter.h
    include/docker/docktoolbar.h
    include/docker/dockcorner.h
    include/docker/headerwidget.h
    include/docker/footerwidget.h
    include/docker/headerfooterwidget.h
    include/docker/widgetitem.h
    include/docker/seperatorwidget.h
    include/docker/labelwidget.h
    include/docker/buttonwidget.h
    include/docker/draggablebuttonwidget.h
    include/docker/docklistitem.h
    include/docker/listbuttonwidget.h
    include/docker/listwidget.h
    include/multisplitter/cloneableinterface.h
    include/multisplitter/multisplitter.h
    # end of MOC shit

    src/docker/abstractdockwidget.cpp
    src/docker/private/abstractdockwidgetprivate.h
    src/docker/private/abstractdockwidgetprivate.cpp
    src/docker/dockwidget.cpp
    src/docker/private/dockwidgetprivate.h
    src/docker/private/dockwidgetprivate.cpp
    src/docker/abstractdockitem.cpp
    src/docker/private/abstractdockitemprivate.h
    src/docker/private/abstractdockitemprivate.cpp
    src/docker/dockheader.cpp
    src/docker/dockfooter.cpp
    src/docker/docktoolbar.cpp
    src/docker/dockcorner.cpp
    src/docker/headerwidget.cpp
    src/docker/private/headerwidgetprivate.h
    src/docker/private/headerwidgetprivate.cpp
    src/docker/footerwidget.cpp
    src/docker/private/footerwidgetprivate.h
    src/docker/private/footerwidgetprivate.cpp
    src/docker/headerfooterwidget.cpp
    src/docker/private/headerfooterwidgetprivate.h
    src/docker/private/headerfooterwidgetprivate.cpp
    src/docker/widgetitem.cpp
    src/docker/private/widgetitemprivate.cpp
    src/docker/private/widgetitemprivate.h
    src/docker/seperatorwidget.cpp
    src/docker/private/seperatorwidgetprivate.cpp
    src/docker/private/seperatorwidgetprivate.h
    src/docker/labelwidget.cpp
    src/docker/private/labelwidgetprivate.cpp
    src/docker/private/labelwidgetprivate.h
    src/docker/buttonwidget.cpp
    src/docker/private/buttonwidgetprivate.cpp
    src/docker/private/buttonwidgetprivate.h
    src/docker/draggablebuttonwidget.cpp
    src/docker/private/draggablebuttonwidgetprivate.cpp
    src/docker/private/draggablebuttonwidgetprivate.h
    src/docker/docklistitem.cpp
    src/docker/listbuttonwidget.cpp
    src/docker/private/listbuttonwidgetprivate.cpp
    src/docker/private/listbuttonwidgetprivate.h
    src/docker/listwidget.cpp
    src/docker/private/listwidgetprivate.cpp
    src/docker/private/listwidgetprivate.h
    src/multisplitter/multisplitter.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        include
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(${PROJECT_NAME}
    PRIVATE 
        -Werror
)

target_compile_features(${PROJECT_NAME}
    PRIVATE 
        cxx_std_17
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Xml
        Qt${QT_VERSION_MAJOR}::Svg

        Utilities::Utilities
)

option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
  # Only build documentation when building in Release mode
  if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
  endif()
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
