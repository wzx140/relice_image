//
// Created by wzx on 18-11-5.
//

#include <vtkImageData.h>
#include "../include/ImageInteractionCallback.h"

ImageInteractionCallback *ImageInteractionCallback::New() {
    return new ImageInteractionCallback;
}

ImageInteractionCallback::ImageInteractionCallback() {
    this->slicing = 0;
    this->reslice = vtkSmartPointer<vtkImageReslice>::New();
    this->interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
}


void ImageInteractionCallback::Execute(vtkObject *caller, unsigned long eventId, void *callData) {
//    get cursor position
    int lastPos[2];
    int currPos[2];
    this->interactor->GetLastEventPosition(lastPos);
    this->interactor->GetEventPosition(currPos);

    switch (eventId) {
        case LeftButtonPressEvent:
            this->slicing = 1;

        case LeftButtonReleaseEvent:
            this->slicing = 0;

        case MouseMoveEvent:
//            extract slice
            if (this->slicing) {
//                calculate length of slice
                int deltaY = lastPos[1] - currPos[1];
                this->reslice->Update();
                double sliceSpacing = this->reslice->GetOutput()->GetSpacing()[1];
                double sliceLength = deltaY * sliceSpacing;
            }
    }
}

int ImageInteractionCallback::getSlicing() const {
    return slicing;
}

void ImageInteractionCallback::setSlicing(int slicing) {
    ImageInteractionCallback::slicing = slicing;
}

const vtkSmartPointer<vtkImageReslice> &ImageInteractionCallback::getReslice() const {
    return reslice;
}

void ImageInteractionCallback::setReslice(const vtkSmartPointer<vtkImageReslice> &reslice) {
    ImageInteractionCallback::reslice = reslice;
}

const vtkSmartPointer<vtkRenderWindowInteractor> &ImageInteractionCallback::getInteractor() const {
    return interactor;
}

void ImageInteractionCallback::setInteractor(const vtkSmartPointer<vtkRenderWindowInteractor> &interactor) {
    ImageInteractionCallback::interactor = interactor;
}
