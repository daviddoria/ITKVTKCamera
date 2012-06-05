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
  ITKVTKCamera(vtkInteractorStyleImage* interactorStyle, vtkRenderer* renderer, vtkRenderWindow* renderWindow);

  /** Initializations performed by all constructors. */
  void SharedConstructor();

  void Flip();

  void FlipVertically();
  void FlipHorizontally();

  void SetCameraPosition1();
  void SetCameraPosition2();

  // These functions are provided in case the default constructor must be used.
  // That would happen in the case where a ITKVTKCamera object object was stored
  // as a non-pointer member.
  void SetInteractorStyle(vtkInteractorStyleImage* interactorStyle);
  void SetRenderer(vtkRenderer* renderer);
  void SetRenderWindow(vtkRenderWindow* renderWindow);

private:
  void SetCameraPosition(const double leftToRight[3], const double bottomToTop[3]);

  vtkRenderer* Renderer;
  vtkRenderWindow* RenderWindow;
  vtkInteractorStyleImage* InteractorStyle;

  bool Flipped;

  double LeftToRight[3];
  double BottomToTop[3];
};

#endif
