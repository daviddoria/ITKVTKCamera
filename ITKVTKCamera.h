#ifndef ITKVTKCamera_H
#define ITKVTKCamera_H

class vtkRenderer;
class vtkRenderWindow;
class vtkInteractorStyleImage;

class ITKVTKCamera
{
  void Flip();

  void SetCameraPosition1();
  void SetCameraPosition2();

private:
  void SetCameraPosition(const double leftToRight[3], const double bottomToTop[3]);
  
  vtkRenderer* Renderer;
  vtkRenderWindow* RenderWindow;
  vtkInteractorStyleImage* InteractorStyle;
  
  bool Flipped;
};

#endif
