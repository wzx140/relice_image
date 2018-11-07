//
// Created by wzx on 18-11-5.
//
#include <gtest/gtest.h>
#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>

#include "../include/ImageRender.h"

class ImageInteractionCallbackTest : public ::testing::Test {

protected:
    vtkSmartPointer<ImageInteractionCallback> callback;
    vtkSmartPointer<ImageRender> render;

    virtual void SetUp() {
        this->render = vtkSmartPointer<ImageRender>::New();
        this->render->setPath("res/brain.mhd");
        this->render->load();

        this->callback = vtkSmartPointer<ImageInteractionCallback>::New();
    }
};

TEST_F(ImageInteractionCallbackTest, Multiply) {
    auto matrix = vtkSmartPointer<vtkMatrix4x4>::New();
    double temp[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 3,
            0, 0, 0, 1
    };
    matrix->DeepCopy(temp);
    double point[4] = {
            0, 0, 5, 1
    };
    double center[4];
    matrix->MultiplyPoint(point, center);
    matrix->SetElement(0, 3, center[0]);
    matrix->SetElement(1, 3, center[1]);
    matrix->SetElement(2, 3, center[2]);
    matrix->SetElement(3, 3, center[3]);
    matrix->Print(std::cout);
}

TEST_F(ImageInteractionCallbackTest, callback) {
    this->callback->setReslice(render->getReslice());
    this->callback->setInteractor(render->getInteractor());

    this->render->addObserver(callback);
    this->render->start();
}
