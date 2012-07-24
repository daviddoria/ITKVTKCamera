#include "ITKVTKCamera.h"

// VTK
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleImage.h>

// STL
#include <stdexcept>

ITKVTKCamera::ITKVTKCamera() : Renderer(NULL), RenderWindow(NULL), InteractorStyle(NULL)
{
  SharedConstructor();
}

void ITKVTKCamera::SharedConstructor()
{
  this->LeftToRight[0] = -1;
  this->LeftToRight[1] = 0;
  this->LeftToRight[2] = 0;

  this->BottomToTop[0] = 0;
  this->BottomToTop[1] = 1;
  this->BottomToTop[2] = 0;
}

ITKVTKCamera::ITKVTKCamera(vtkInteractorStyleImage* interactorStyle, vtkRenderer* renderer,
                           vtkRenderWindow* renderWindow)
{
  Initialize(interactorStyle, renderer, renderWindow);
  SharedConstructor();

  SetCameraPosition(this->LeftToRight, this->BottomToTop);
}

void ITKVTKCamera::Initialize(vtkInteractorStyleImage* interactorStyle, vtkRenderer* renderer,
                              vtkRenderWindow* renderWindow)
{
  SetRenderer(renderer);
  SetRenderWindow(renderWindow);
  SetInteractorStyle(interactorStyle);
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

void ITKVTKCamera::SetCameraPositionPNG()
{
  this->LeftToRight[0] = 1;
  this->LeftToRight[1] = 0;
  this->LeftToRight[2] = 0;

  this->BottomToTop[0] = 0;
  this->BottomToTop[1] = -1;
  this->BottomToTop[2] = 0;
  SetCameraPosition(this->LeftToRight, this->BottomToTop);
}

void ITKVTKCamera::SetCameraPositionMHA()
{
  this->LeftToRight[0] = 1;
  this->LeftToRight[1] = 0;
  this->LeftToRight[2] = 0;

  this->BottomToTop[0] = 0;
  this->BottomToTop[1] = 1;
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

void ITKVTKCamera::FlipBoth()
{
  FlipHorizontally();
  FlipVertically();
}

void ITKVTKCamera::SetInteractorStyle(vtkInteractorStyleImage* interactorStyle)
{
  this->InteractorStyle = interactorStyle;
  if(this->Renderer)
  {
    // Without this line, if the image has not been clicked, the camera is not affected
    interactorStyle->SetCurrentRenderer(this->Renderer);
  }
  else
  {
    throw std::runtime_error("ITKVTKCamera::SetInteractorStyle:\
                              renderer must be set before interactorStyle!");
  }
}

void ITKVTKCamera::SetRenderer(vtkRenderer* renderer)
{
  this->Renderer = renderer;
}

void ITKVTKCamera::SetRenderWindow(vtkRenderWindow* renderWindow)
{
  this->RenderWindow = renderWindow;
}
