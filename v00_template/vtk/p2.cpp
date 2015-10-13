#include "vtkPolyDataMapper.h"
#include "vtkBYUReader.h"
#include "vtkAxesActor.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkTransform.h"
#include "vtkTransformFilter.h"
#include "utils.h"
#include "pathconfig.h"
int main()
{
  VTK_CREATE(vtkBYUReader, krava);
  filePathBuilder fpath;
  krava->SetGeometryFileName(fpath.filePath("cow.g").c_str());

  VTK_CREATE(vtkPolyDataMapper, mapper);
  mapper->SetInputConnection(krava->GetOutputPort());
  
  VTK_CREATE(vtkActor, krava_actor_original);
  krava_actor_original->SetMapper(mapper);
  krava_actor_original->GetProperty()->SetColor(0.96,0.87,0.7);
  krava_actor_original->GetProperty()->SetRepresentationToWireframe();
  
  
  VTK_CREATE(vtkAxesActor, axes);
  VTK_CREATE(vtkAxesActor, cow2axes);
  cow2axes->AxisLabelsOff();
  
  
  VTK_CREATE(vtkRenderer, ren);
  ren->AddActor(krava_actor_original);
  ren->AddActor(cow2axes);
  vtkCamera* camera = ren->GetActiveCamera();
  ren->SetBackground(.1,.2,.3);
  
  VTK_CREATE(vtkRenderWindow, renw);
  renw->AddRenderer(ren);
  
  VTK_CREATE(vtkInteractorStyleTrackballCamera, style);
  
  VTK_CREATE(vtkRenderWindowInteractor, iren);
  iren->SetRenderWindow(renw);
  iren->SetInteractorStyle(style);
  iren->Initialize();
  iren->Start();
  
  return 0;
}
