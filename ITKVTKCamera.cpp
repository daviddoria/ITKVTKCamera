#include "ITKVTKCamera.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleImage.h>

ITKVTKCamera::ITKVTKCamera() :Flipped(false)
{

}

void ITKVTKCamera::SetCameraPosition1()
{
  double leftToRight[3] = {-1,0,0};
  double bottomToTop[3] = {0,1,0};
  SetCameraPosition(leftToRight, bottomToTop);
}

void ITKVTKCamera::SetCameraPosition2()
{
  double leftToRight[3] = {-1,0,0};
  double bottomToTop[3] = {0,-1,0};

  SetCameraPosition(leftToRight, bottomToTop);
}

void ITKVTKCamera::SetCameraPosition(const double leftToRight[3], const double bottomToTop[3])
{
  this->InteractorStyle->SetImageOrientation(leftToRight, bottomToTop);

  this->Renderer->ResetCamera();
  this->Renderer->ResetCameraClippingRange();
  this->RenderWindow->Render();
}


void ITKVTKCamera::Flip()
{
  if(this->Flipped)
    {
    SetCameraPosition1();
    }
  else
    {
    SetCameraPosition2();
    }
  this->Flipped = !this->Flipped;
}

void ITKVTKCamera::SetInteractorStyle(vtkInteractorStyleImage* interactorStyle)
{
  this->InteractorStyle = interactorStyle;
}

void ITKVTKCamera::SetRenderer(vtkRenderer* renderer)
{
  this->Renderer = renderer;
}

void ITKVTKCamera::SetRenderWindow(vtkRenderWindow* renderWindow)
{
  this->RenderWindow = renderWindow;
}
