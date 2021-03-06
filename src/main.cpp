#include <vtkSmartPointer.h>

#include "../include/ImageRender.h"

int main(int argc, char **argv) {
    auto render = vtkSmartPointer<ImageRender>::New();
    render->setPath("res/brain.mhd");
    render->load();

    auto callback = vtkSmartPointer<ImageInteractionCallback>::New();
    callback->setReslice(render->getReslice());
    callback->setInteractor(render->getInteractor());

    render->addObserver(callback);
    render->start();
    return 0;
}

