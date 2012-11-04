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

#ifndef ITKVTKCamera_H
#define ITKVTKCamera_H

class vtkRenderer;
class vtkRenderWindow;
class vtkInteractorStyleImage;

/** This class is responsible for setting up the view of an image, typically
  * to switch between ITK and VTK coordinate systems.
  */
class ITKVTKCamera
{
public:
  /** Default constructor. It is better to use the other constructor if possible. */
  ITKVTKCamera();

  /** This constructor provides all of the information necessary. */
  ITKVTKCamera(vtkInteractorStyleImage* interactorStyle, vtkRenderer* renderer,
               vtkRenderWindow* renderWindow);

  /** Initialize everything. */
  void Initialize(vtkInteractorStyleImage* interactorStyle, vtkRenderer* renderer,
                  vtkRenderWindow* renderWindow);

  /** Initializations performed by all constructors. */
  void SharedConstructor();

  /** Flip the image in both dimensions. */
  void FlipBoth();

  /** Flip the image vertically. */
  void FlipVertically();

  /** Flip the image horizontally. */
  void FlipHorizontally();

  /** Set the camera position so that PNG files read with ITK are displayed right-side-up. */
  void SetCameraPositionPNG();

  /** Set the camera position so that MHA files read with ITK are displayed right-side-up. */
  void SetCameraPositionMHA();

  // These functions are provided in case the default constructor must be used.
  // That would happen in the case where a ITKVTKCamera object object was stored
  // as a non-pointer member.
  /** Set the interactor style that is attached to the Renderer. */
  void SetInteractorStyle(vtkInteractorStyleImage* interactorStyle);

  /** Set the Renderer that the image is displayed in. */
  void SetRenderer(vtkRenderer* renderer);

  /** Set the render window that the image is displayed in. */
  void SetRenderWindow(vtkRenderWindow* renderWindow);

private:
  /** Set the camera to a specific position. */
  void SetCameraPosition(const double leftToRight[3], const double bottomToTop[3]);

  /** The Renderer that the image is displayed in. */
  vtkRenderer* Renderer = nullptr;

  /** The render window that the image is displayed in. */
  vtkRenderWindow* RenderWindow = nullptr;

  /** The interactor style that is attached to the Renderer. */
  vtkInteractorStyleImage* InteractorStyle = nullptr;

  double LeftToRight[3];
  double BottomToTop[3];
};

#endif
