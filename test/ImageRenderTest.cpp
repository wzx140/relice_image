//
// Created by wzx on 18-11-5.
//

#include <gtest/gtest.h>

#include "../include/ImageRender.h"

class ImageRenderTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        render = vtkSmartPointer<ImageRender>::New();
    }

    vtkSmartPointer<ImageRender> render;
};

TEST_F(ImageRenderTest, loadAndStart) {
    render->setPath("../res/brain.mhd");
    render->load();
    render->start();
}


