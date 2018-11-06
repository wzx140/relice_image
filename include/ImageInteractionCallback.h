//
// Created by wzx on 18-11-5.
//

#ifndef RELICE_MOUSE_IMAGEINTERACTIONCALLBACK_H
#define RELICE_MOUSE_IMAGEINTERACTIONCALLBACK_H


#include <vtkImageReslice.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>

/**
 * handle the mouse event
 */
class ImageInteractionCallback :public vtkCommand{
private:

    /**
     * the flag of slice
     */
    int slicing;

    /**
     * used to slice the image
     */
    vtkSmartPointer<vtkImageReslice> reslice;

    /**
     * the interactor window we need to refresh
     */
    vtkSmartPointer<vtkRenderWindowInteractor> interactor;

public:
    static ImageInteractionCallback *New();

    ImageInteractionCallback();

    int getSlicing() const;

    void setSlicing(int slicing);

    const vtkSmartPointer<vtkImageReslice> &getReslice() const;

    void setReslice(const vtkSmartPointer<vtkImageReslice> &reslice);

    const vtkSmartPointer<vtkRenderWindowInteractor> &getInteractor() const;

    void setInteractor(const vtkSmartPointer<vtkRenderWindowInteractor> &interactor);

private:
    void Execute(vtkObject *caller, unsigned long eventId, void *callData) override;
};


#endif //RELICE_MOUSE_IMAGEINTERACTIONCALLBACK_H
