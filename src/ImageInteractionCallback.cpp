//
// Created by wzx on 18-11-5.
//

#include <vtkImageData.h>
#include <vtkMatrix4x4.h>
#include <vtkInteractorStyle.h>

#include "../include/ImageInteractionCallback.h"


ImageInteractionCallback *ImageInteractionCallback::New() {
    return new ImageInteractionCallback;
}

ImageInteractionCallback::ImageInteractionCallback() {
    this->slicing = 0;
    this->reslice = nullptr;
    this->interactor = nullptr;
}


void ImageInteractionCallback::Execute(vtkObject *caller, unsigned long eventId, void *callData) {
//    get cursor position
    int lastPos[2];
    int currPos[2];
    this->interactor->GetLastEventPosition(lastPos);
    this->interactor->GetEventPosition(currPos);

    switch (eventId) {
        case LeftButtonPressEvent:
//            cout << "click" << endl;
            this->slicing = 1;
            break;

        case LeftButtonReleaseEvent:
//            cout << "release" << endl;
            this->slicing = 0;
            break;

        case MouseMoveEvent:
//            cout << "move" << endl;
//            extract slice
            if (this->slicing == 1) {
//                calculate length of slice
                int deltaY = lastPos[1] - currPos[1];
                this->reslice->Update();
                double sliceSpacing = this->reslice->GetOutput()->GetSpacing()[1];
                double sliceLength = deltaY * sliceSpacing;

//                move the center point that we are slicing through
                auto matrix = this->reslice->GetResliceAxes();
                double point[4] = {
                        0, 0, sliceLength, 1
                };
                double center[4];
//                add sliceLength to element(2,3)
                matrix->MultiplyPoint(point, center);
                matrix->SetElement(0, 3, center[0]);
                matrix->SetElement(1, 3, center[1]);
                matrix->SetElement(2, 3, center[2]);
                matrix->SetElement(3, 3, center[3]);

                this->interactor->Render();

            } else {
                auto style = vtkInteractorStyle::SafeDownCast(this->interactor->GetInteractorStyle());
                if (style) {
                    style->OnMouseMove();
                }
            }
            break;
        default:
            cout << eventId;
    }
}

void ImageInteractionCallback::setReslice(const vtkSmartPointer<vtkImageReslice> &reslice) {
    ImageInteractionCallback::reslice = reslice;
}

void ImageInteractionCallback::setInteractor(const vtkSmartPointer<vtkRenderWindowInteractor> &interactor) {
    ImageInteractionCallback::interactor = interactor;
}
