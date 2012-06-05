#include "ITKVTKCamera.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleImage.h>

ITKVTKCamera::ITKVTKCamera()
{
  SharedConstructor();
}

void ITKVTKCamera::SharedConstructor()
{
  this->Flipped = false;

  this->LeftToRight[0] = -1;
  this->LeftToRight[1] = 0;
  this->LeftToRight[2] = 0;

  this->BottomToTop[0] = 0;
  this->BottomToTop[1] = 1;
  this->BottomToTop[2] = 0;
}

ITKVTKCamera::ITKVTKCamera(vtkInteractorStyleImage* interactorStyle, vtkRenderer* renderer, vtkRenderWindow* renderWindow)
{
  SharedConstructor();
  SetRenderer(renderer);
  SetInteractorStyle(interactorStyle);
  SetRenderWindow(renderWindow);
}

void ITKVTKCamera::FlipVertically()
{
  this->BottomToTop[1] = -1.0f * this->BottomToTop[1];
  SetCameraPosition(this->LeftToRight, this->BottomToTop);
}

void ITKVTKCamera::FlipHorizontally()
{
  this->LeftToRight[0] = -1.0f * this->LeftToRight[0];
  SetCameraPosition(this->LeftToRight, this->BottomToTop);
}

void ITKVTKCamera::SetCameraPosition1()
{
  this->LeftToRight[0] = -1;
  this->LeftToRight[1] = 0;
  this->LeftToRight[2] = 0;

  this->BottomToTop[0] = 0;
  this->BottomToTop[1] = 1;
  this->BottomToTop[2] = 0;
  SetCameraPosition(this->LeftToRight, this->BottomToTop);
}

void ITKVTKCamera::SetCameraPosition2()
{
  this->LeftToRight[0] = -1;
  this->LeftToRight[1] = 0;
  this->LeftToRight[2] = 0;

  this->BottomToTop[0] = 0;
  this->BottomToTop[1] = -1;
  this->BottomToTop[2] = 0;

  SetCameraPosition(this->LeftToRight, this->BottomToTop);
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
