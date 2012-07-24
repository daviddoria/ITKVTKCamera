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
  vtkRenderer* Renderer;

  /** The render window that the image is displayed in. */
  vtkRenderWindow* RenderWindow;

  /** The interactor style that is attached to the Renderer. */
  vtkInteractorStyleImage* InteractorStyle;

  double LeftToRight[3];
  double BottomToTop[3];
};

#endif
