//
// Created by wzx on 18-11-5.
//

#include "../include/ImageRender.h"

#include <vtkMetaImageReader.h>
#include <vtkImageChangeInformation.h>
#include <vtkMatrix4x4.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorStyleImage.h>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>


using std::string;

ImageRender *ImageRender::New() {
    return new ImageRender;
}


ImageRender::ImageRender() {
    this->interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    this->reslice = vtkSmartPointer<vtkImageReslice>::New();
}


void ImageRender::setPath(const string &path) {
    this->path = path;
}

void ImageRender::load() {
    auto reader = vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(this->path.c_str());
//    reader->Update();

    auto changer = vtkSmartPointer<vtkImageChangeInformation>::New();
    changer->SetInputConnection(reader->GetOutputPort());
//    change the middle point of the image to origin point
    changer->SetCenterImage(1);
//    changer->Update();

    this->reslice->SetInputConnection(changer->GetOutputPort());

//    the changing matrix designed for reslice
    static double axialElements[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
    auto resliceMatrix = vtkSmartPointer<vtkMatrix4x4>::New();
    resliceMatrix->DeepCopy(axialElements);

//    slice the image
    this->reslice->SetInputConnection(changer->GetOutputPort());
    this->reslice->SetOutputDimensionality(2);
    this->reslice->SetResliceAxes(resliceMatrix);
    this->reslice->SetInterpolationModeToLinear();

//    build color table to map the color
    auto colorTable = vtkSmartPointer<vtkLookupTable>::New();
    colorTable->SetRange(0, 1000);
    colorTable->SetValueRange(0.0, 1.0);
    colorTable->SetSaturationRange(0.0, 0.0);
    colorTable->SetRampToLinear();
    colorTable->Build();

//    map the color
    auto colorMap = vtkSmartPointer<vtkImageMapToColors>::New();
    colorMap->SetLookupTable(colorTable);
    colorMap->SetInputConnection(this->reslice->GetOutputPort());

//    display the slice
    auto actor = vtkSmartPointer<vtkImageActor>::New();
    actor->GetMapper()->SetInputConnection(colorMap->GetOutputPort());
    auto render = vtkSmartPointer<vtkRenderer>::New();
    render->AddActor(actor);
//    black
    render->SetBackground(0, 0, 0);
    auto window = vtkSmartPointer<vtkRenderWindow>::New();
    window->AddRenderer(render);
    auto style = vtkSmartPointer<vtkInteractorStyleImage>::New();
    this->interactor->SetInteractorStyle(style);
    this->interactor->SetRenderWindow(window);

    this->interactor->Initialize();
}

void ImageRender::addObserver(vtkSmartPointer<ImageInteractionCallback> callback) {
//    LeftButtonReleaseEvent do not work if you just use interactor to add Observer
    this->interactor->GetInteractorStyle()->AddObserver(vtkCommand::MouseMoveEvent, callback);
    this->interactor->GetInteractorStyle()->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
    this->interactor->GetInteractorStyle()->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);
}

void ImageRender::start() {
    this->interactor->Start();
}

const vtkSmartPointer<vtkRenderWindowInteractor> &ImageRender::getInteractor() const {
    return interactor;
}

const vtkSmartPointer<vtkImageReslice> &ImageRender::getReslice() const {
    return reslice;
}






