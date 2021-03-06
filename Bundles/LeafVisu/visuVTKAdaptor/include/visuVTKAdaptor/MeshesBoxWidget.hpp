/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVTKADAPTOR_MESHESBOXWIDGET_HPP__
#define __VISUVTKADAPTOR_MESHESBOXWIDGET_HPP__

#include "visuVTKAdaptor/config.hpp"

#include <fwCom/Connection.hpp>
#include <fwCom/Slot.hpp>
#include <fwCom/Slots.hpp>

#include <fwData/Composite.hpp>

#include <fwRenderVTK/IVtkAdaptorService.hpp>

#ifndef ANDROID

class vtkBoxWidget2;
class vtkCommand;
class vtkPolyData;
class vtkAssembly;
class vtkActor;

namespace visuVTKAdaptor
{

/**
 * @brief   Create a Box widget around the meshes contained in the composite.
 * @class   MeshesBoxWidget
 *
 * @date    2010.
 */
class VISUVTKADAPTOR_CLASS_API MeshesBoxWidget : public ::fwRenderVTK::IVtkAdaptorService
{

public:

    fwCoreServiceClassDefinitionsMacro ( (MeshesBoxWidget)(::fwRenderVTK::IVtkAdaptorService) );

    VISUVTKADAPTOR_API MeshesBoxWidget() throw();

    VISUVTKADAPTOR_API virtual ~MeshesBoxWidget() throw();

    /// Updates meshes transformation matrix from vtk box widget transform
    void updateFromVtk();

    /**
     * @brief Returns proposals to connect service slots to associated object signals,
     * this method is used for obj/srv auto connection
     *
     * Connect Composite::s_ADDED_OBJECTS_SIG to this::s_ADD_OBJECTS_SLOT
     * Connect Composite::s_CHANGED_OBJECTS_SIG to this::s_CHANGE_OBJECTS_SLOT
     * Connect Composite::s_REMOVED_OBJECTS_SIG to this::s_REMOVE_OBJECTS_SLOT
     */
    VISUVTKADAPTOR_API virtual KeyConnectionsType getObjSrvConnections() const;

protected:

    VISUVTKADAPTOR_API void doStart() throw(fwTools::Failed);
    VISUVTKADAPTOR_API void doConfigure() throw(fwTools::Failed);
    VISUVTKADAPTOR_API void doSwap() throw(fwTools::Failed);
    VISUVTKADAPTOR_API void doUpdate() throw(fwTools::Failed);
    VISUVTKADAPTOR_API void doStop() throw(fwTools::Failed);

    /// Updates vtk transformation from data meshes
    void updateMeshTransform();

    /// Updates map from composite meshes
    void updateMeshMapFromComposite(::fwData::Composite::ContainerType objects);

private:

    /**
     * @name Slots methods
     * @{
     */
    /// Slot: Updates the matrices
    void updateMatrices();

    /// Slot: add objects
    void addObjects(::fwData::Composite::ContainerType objects);

    /// Slot: change objects
    void changeObjects(::fwData::Composite::ContainerType newObjects, ::fwData::Composite::ContainerType oldObjects);

    /// Slot: remove objects
    void removeObjects(::fwData::Composite::ContainerType objects);
    /**
     * @}
     */

    typedef std::map< std::string, ::fwCom::Connection > ConnectionMapType;
    typedef std::map< std::string, vtkActor* > MeshMapType;

    MeshMapType m_meshMap;
    ConnectionMapType m_connections;

    vtkAssembly * m_assembly;
    vtkCommand* m_boxWidgetCommand;
    vtkBoxWidget2* m_vtkBoxWidget;
};




} //namespace visuVTKAdaptor

#endif // ANDROID

#endif // __VISUVTKADAPTOR_MESHESBOXWIDGET_HPP__
