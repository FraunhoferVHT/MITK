/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#ifndef OVERLAYMANAGER_H
#define OVERLAYMANAGER_H

#include "MitkExports.h"
#include <itkLightObject.h>
#include <vtkSmartPointer.h>
#include "mitkOverlay.h"
#include "mitkBaseRenderer.h"
#include "mitkBaseLayouter.h"
#include "mitkLocalStorageHandler.h"

// Microservices
#include <usServiceInterface.h>
#include <usServiceRegistration.h>
#include <usServiceProperties.h>
#include <usModuleContext.h>

namespace mitk {

/** \brief Microservice to update and manage Overlays and the respective Layouters. */
/** This microservice can be registered to several BaseRenderer instances in order to
 * call the update method of each Overlay during the rendering phase of the renderer.
*/
class MITK_CORE_EXPORT OverlayManager : public itk::LightObject {
public:
  typedef std::list<BaseRenderer*> BaseRendererList;
  typedef std::list<Overlay::Pointer> OverlayList;
  typedef std::map<const std::string,BaseLayouter::Pointer > LayouterMap;
  typedef std::map<const BaseRenderer*,LayouterMap > LayouterRendererMap;

  mitkClassMacro(OverlayManager, itk::LightObject);
  itkNewMacro(OverlayManager);

  void AddOverlay(Overlay* overlay);
  void RemoveOverlay(Overlay* overlay);

  /** \brief Clears the manager of all Overlays.*/
  void RemoveAllOverlays();
  void UnregisterMicroservice();
  static const std::string PROP_ID;
  /** \brief Adds the overlay to the layouter specified by identifier and renderer*/
  void SetLayouter(Overlay* overlay, const char* identifier, BaseRenderer* renderer);
  void UpdateLayouts(BaseRenderer* renderer);
  /** \brief Returns the Layouter specified by renderer and the identifier*/
  BaseLayouter::Pointer GetLayouter(BaseRenderer* renderer, const std::string identifier);
  /** \brief Add a layouter to provide it with the use of the SetLayouter method*/
  void AddLayouter(BaseLayouter* layouter);
  static OverlayManager::Pointer GetServiceInstance(std::string ID = "0");
  std::string GetID();

  void AddBaseRenderer(BaseRenderer* renderer);
  /** \brief The layout of each Overlay will be prepared and the properties of each Overlay is updated.*/
  void UpdateOverlays(BaseRenderer *baseRenderer);

protected:

  /** \brief explicit constructor which disallows implicit conversions */
  explicit OverlayManager();

  ~OverlayManager();

private:

  OverlayList m_OverlayList;

  BaseRendererList m_BaseRendererList;

  LayouterRendererMap m_LayouterMap;

  /** \brief copy constructor */
  OverlayManager( const OverlayManager &);

  /** \brief assignment operator */
  OverlayManager &operator=(const OverlayManager &);

  std::string RegisterMicroservice();

  us::ServiceRegistration<Self> m_Registration;

  std::string m_id;

};

} // namespace mitk

US_DECLARE_SERVICE_INTERFACE(mitk::OverlayManager, "org.mitk.services.OverlayManager")
#endif // OVERLAYMANAGER_H


