//
// Created by wzx on 18-11-5.
//
#include <gtest/gtest.h>
#include <vtkSmartPointer.h>
#include <vtkMetaImageReader.h>
#include <vtkImageReslice.h>
#include <vtkImageData.h>
#include <vtkRenderWindowInteractor.h>

#include "../include/ImageInteractionCallback.h"

class ImageInteractionCallbackTest : public ::testing::Test {

protected:
    vtkSmartPointer<ImageInteractionCallback> callback;

    virtual void SetUp() {
        auto reader = vtkSmartPointer<vtkMetaImageReader>::New();
        reader->SetFileName("../res/brain.mhd");
        reader->Update();

        auto reslice = vtkSmartPointer<vtkImageReslice>::New();
        reslice->SetInputData(reader->GetOutput());

        auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

        callback = vtkSmartPointer<ImageInteractionCallback>::New();
        callback->setReslice(reslice);
        callback->setInteractor(interactor);
    }
};

TEST_F(ImageInteractionCallbackTest, New) {
    EXPECT_STREQ("1", "ImageInteractionCallback");
}
