/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVTKADAPTOR_IMAGESPROBECURSOR_HPP__
#define __VISUVTKADAPTOR_IMAGESPROBECURSOR_HPP__

#include <fwData/TransferFunction.hpp>

#include <fwComEd/helper/MedicalImageAdaptor.hpp>

#include <fwRenderVTK/IVtkAdaptorService.hpp>

class vtkCommand;
class vtkActor;
class vtkActor2D;
class vtkTextMapper;
class vtkPolyData;
class vtkPolyDataMapper;

namespace visuVTKAdaptor
{

/**
 * @brief   Draw pixel information from images given by id in composite.
 * @class   ImagesProbeCursor
 *
 * @date    2010.
 */
class VISUVTKADAPTOR_CLASS_API ImagesProbeCursor : public  ::fwComEd::helper::MedicalImageAdaptor,
                                                   public ::fwRenderVTK::IVtkAdaptorService
{

public:
    fwCoreServiceClassDefinitionsMacro ( (ImagesProbeCursor)(::fwRenderVTK::IVtkAdaptorService) );

    VISUVTKADAPTOR_API ImagesProbeCursor() throw();

    VISUVTKADAPTOR_API virtual ~ImagesProbeCursor() throw();

    VISUVTKADAPTOR_API void updateView( double world[3] );

    VISUVTKADAPTOR_API void setVisibility( bool visibility );

    VISUVTKADAPTOR_API void StartImagesProbeCursor();

protected:

    VISUVTKADAPTOR_API void doStart() throw(fwTools::Failed);
    VISUVTKADAPTOR_API void doStop() throw(fwTools::Failed);

    /**
     * @code{.xml}
       <adaptor id="GENERIC_UID_ImagesProbeCursor" class="::visuVTKAdaptor::ImagesProbeCursor" objectId="self">
         <config renderer="default" picker="myPicker">
             <image objectId="myRefImage" name="background" />
             <image objectId="myObject" name="working" />
         </config>
       </adaptor>
       @endcode
     */
    VISUVTKADAPTOR_API void doConfigure() throw(fwTools::Failed);
    VISUVTKADAPTOR_API void doSwap() throw(fwTools::Failed);
    VISUVTKADAPTOR_API void doUpdate() throw(fwTools::Failed);

    void buildTextActor();
    void buildPolyData();

    void computeCrossExtremity( const int probeSlice[3], double worldCross[4][3] );

    typedef std::pair< std::string, std::string > ImagesIdPair;
    std::vector< ImagesIdPair > m_imagesId;
    double m_priority;

    vtkCommand *m_vtkObserver;

    vtkActor2D    * m_textActor; // rendering defect using a vtkTextActor
    vtkTextMapper * m_textMapper;

    vtkPolyData         *m_cursorPolyData;
    vtkPolyDataMapper   *m_cursorMapper;
    vtkActor            *m_cursorActor;



};




} //namespace visuVTKAdaptor

#endif // __VISUVTKADAPTOR_IMAGESPROBECURSOR_HPP__
