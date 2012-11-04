/*=========================================================================
 *
 *  Copyright David Doria 2012 daviddoria@gmail.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "ITKVTKCamera.h"

// VTK
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleImage.h>

// STL
#include <stdexcept>

ITKVTKCamera::ITKVTKCamera()
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
