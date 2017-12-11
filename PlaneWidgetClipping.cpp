#include <vtkPlaneWidget.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkPlane.h>
#include <vtkCallbackCommand.h>
#include <vtkClipPolyData.h>
#include <vtkProperty.h>
#include <vtkActor.h>
 
int main(int, char *[])
{  
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetThetaResolution(32);
  sphereSource->SetPhiResolution(32);
  sphereSource->Update();

  // clipping structure
  vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
  vtkSmartPointer<vtkClipPolyData> clipperPoly = vtkSmartPointer<vtkClipPolyData>::New();
  clipperPoly->SetInputConnection(sphereSource->GetOutputPort());
  clipperPoly->SetClipFunction(plane);
  clipperPoly->InsideOutOn();

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
 
  //render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  //mapper
  vtkSmartPointer<vtkDataSetMapper> selectMapper = vtkSmartPointer<vtkDataSetMapper>::New();
  selectMapper->SetInputConnection(clipperPoly->GetOutputPort());

  vtkSmartPointer<vtkActor> selectActor = vtkSmartPointer<vtkActor>::New();
  selectActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
  selectActor->SetMapper(selectMapper);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  //widget placed on the actor
  vtkSmartPointer<vtkPlaneWidget> planeWidget = vtkSmartPointer<vtkPlaneWidget>::New();
  planeWidget->SetInteractor(renderWindowInteractor);
  planeWidget->PlaceWidget(selectActor->GetBounds());
  //interaction
  auto interactionFcn = [](vtkObject* caller, long unsigned int eventId, void* clientData, void* callData) {
    vtkSmartPointer<vtkPlaneWidget> planeWidget = reinterpret_cast<vtkPlaneWidget*>(caller);
    vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
    planeWidget->GetPlane(plane);
    
    vtkClipPolyData* clipperPoly = static_cast<vtkClipPolyData*>(clientData);
    clipperPoly->SetClipFunction(plane);
  };
  vtkSmartPointer<vtkCallbackCommand> interactionCallback = vtkSmartPointer<vtkCallbackCommand>::New();
  interactionCallback->SetCallback(interactionFcn);
  interactionCallback->SetClientData(clipperPoly);  //pass the clipper to update it
  planeWidget->AddObserver(vtkCommand::InteractionEvent, interactionCallback);

  // Add the actor
  renderer->AddActor(selectActor);

  // Generate a camera
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> cameraStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  renderWindowInteractor->SetInteractorStyle(cameraStyle);
  renderer->ResetCamera();

  planeWidget->On();

  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}