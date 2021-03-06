/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVTKADAPTOR_PLANEINTERACTOR_HPP__
#define __VISUVTKADAPTOR_PLANEINTERACTOR_HPP__

#ifndef ANDROID

#include "visuVTKAdaptor/config.hpp"

#include <fwComEd/helper/MedicalImageAdaptor.hpp>

#include <fwData/TransferFunction.hpp>

#include <fwRenderVTK/IVtkAdaptorService.hpp>


class vtkCommand;

namespace visuVTKAdaptor
{

class VISUVTKADAPTOR_CLASS_API PlaneInteractor : public ::fwComEd::helper::MedicalImageAdaptor,
                                                 public ::fwRenderVTK::IVtkAdaptorService
{

public:

    fwCoreServiceClassDefinitionsMacro ( (PlaneInteractor)(::fwRenderVTK::IVtkAdaptorService) );

    VISUVTKADAPTOR_API PlaneInteractor() throw();

    VISUVTKADAPTOR_API virtual ~PlaneInteractor() throw();

    VISUVTKADAPTOR_API void switchPlaneNormal();

    VISUVTKADAPTOR_API void pushPlane(double factor);

    VISUVTKADAPTOR_API void deselectPlane();

protected:

    VISUVTKADAPTOR_API void doStart() throw(fwTools::Failed);
    VISUVTKADAPTOR_API void doStop() throw(fwTools::Failed);

    VISUVTKADAPTOR_API void doConfigure() throw(fwTools::Failed);
    VISUVTKADAPTOR_API void doSwap() throw(fwTools::Failed);
    // redraw all (stop then restart sub services)
    VISUVTKADAPTOR_API void doUpdate() throw(fwTools::Failed);

    vtkCommand *m_vtkObserver;
    double m_priority;
};




} //namespace visuVTKAdaptor

#endif // ANDROID

#endif // __VISUVTKADAPTOR_PLANEINTERACTOR_HPP__
