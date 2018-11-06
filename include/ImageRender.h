//
// Created by wzx on 18-11-5.
//

#ifndef RELICE_MOUSE_IMAGERENDER_H
#define RELICE_MOUSE_IMAGERENDER_H

#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkImageReslice.h>

#include "ImageInteractionCallback.h"

/**
 * render the image
 */
class ImageRender : public vtkObject {
private:

    /**
     * the path to load the image
     */
    std::string path;

    /**
     * the interactor window class ImageInteractionCallback may use to refresh
     */
    vtkSmartPointer<vtkRenderWindowInteractor> interactor;

    /**
     *used to slice the image, class ImageInteractionCallback may use it to update the slice
     */
    vtkSmartPointer<vtkImageReslice> reslice;

public:
    static ImageRender *New();

    ImageRender();

    /**
     * set the path of the image
     * @param path must have a prefix of "../"
     */
    void setPath(const std::string &path);

    /**
     * load the data, in order to pass the data to interactor
     */
    void load();

    /**
     * add observer to listen mouse event
     * @param callback the object must inherit vtkCommand
     */
    void addObserver(vtkSmartPointer<ImageInteractionCallback> callback);

    /**
     * start to display in window
     */
    void start();

    const vtkSmartPointer<vtkRenderWindowInteractor> &getInteractor() const;

    const vtkSmartPointer<vtkImageReslice> &getReslice() const;
};


#endif //RELICE_MOUSE_IMAGERENDER_H
