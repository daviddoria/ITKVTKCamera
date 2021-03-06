// ITK
#include "itkVectorImage.h"
#include "itkImageFileReader.h"

// VTK
#include <vtkVersion.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageMapper.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageSlice.h>

// Submodules
#include "ITKVTKHelpers/ITKVTKHelpers.h"

// Custom
#include "ITKVTKCamera.h"

// STL
#include <stdexcept>
/*
// Define interaction style
class CustomImageStyle : public vtkInteractorStyleImage
{
  public:
    static CustomImageStyle* New();
    vtkTypeMacro(CustomImageStyle, vtkInteractorStyleImage);

    virtual void OnKeyPress()
    {
      // Get the keypress
      vtkRenderWindowInteractor *rwi = this->Interactor;
      std::string key = rwi->GetKeySym();

      // Handle a "normal" key
      if(key == "a")
        {
        std::cout << "The a key was pressed." << std::endl;
        this->Camera->Flip();
        }

      // Forward events
      vtkInteractorStyleTrackballCamera::OnKeyPress();
    }

  ITKVTKCamera* Camera;
};
vtkStandardNewMacro(CustomImageStyle);*/

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    throw std::runtime_error("Required arguments: image.mha");
  }

  std::string imageFileName = argv[1];

  typedef itk::VectorImage<unsigned char, 2> ImageType;
  typedef itk::ImageFileReader<ImageType> ReaderType;

  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(imageFileName);
  reader->Update();

  vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();

  ITKVTKHelpers::ITKImageToVTKRGBImage(reader->GetOutput(), image);

  vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
  imageSliceMapper->SetInputData(image);
  vtkSmartPointer<vtkImageSlice> imageSlice = vtkSmartPointer<vtkImageSlice>::New();
  imageSlice->SetMapper(imageSliceMapper);

  // Setup renderers
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddViewProp(imageSlice);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetSize(300, 300);
  renderWindow->AddRenderer(renderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  ITKVTKCamera itkvtkCamera(style, renderer, renderWindow);
  itkvtkCamera.SetCameraPositionPNG();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
