#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkStructuredGrid.h>
#include "utils.h"

vtkSmartPointer<vtkStructuredGrid> createGrid(const int& dimx, const int& dimy)
{
    VTK_CREATE(vtkStructuredGrid, grid);
    VTK_CREATE(vtkPoints, points);


    // TODO
    double x0{0.}, y0{0.}, x1{3.14}, y1{2.};
    double x{x0}, y{y0};
    // donja linija y(x) = sin(x)
    // gornja linija: y(x) = y1

    for(unsigned int j = 0; j < dimy; j++)
    {
        y += 1.0;
        for(unsigned int i = 0; i < dimx; i++)
        {
            //x += .5;
            //points->InsertNextPoint(x, y,0);
		double dx = (x1-x0)/dimx;
		x = x0+i*dx;
		y0 = sin(x);
		double dy = (y1-sin(x))/dimy;
		y = y0+j*dy;
	        points->InsertNextPoint(x, y,0);
        }
    }
    grid->SetDimensions(dimx,dimy,1);
    grid->SetPoints(points);
    return grid;
}

int main()
{
    // Create a mapper and actor
    VTK_CREATE(vtkDataSetMapper, mapper);
    vtkSmartPointer<vtkStructuredGrid> g = createGrid(6,10);
#if VTK_MAJOR_VERSION <= 5
    mapper->SetInputConnection(g->GetProducerPort());
#else
    mapper->SetInputData(g);
#endif

    VTK_CREATE(vtkActor, g_actor);
    g_actor->SetMapper(mapper);
    g_actor->GetProperty()->SetRepresentationToWireframe();

    VTK_CREATE(vtkRenderer, ren);
    ren->AddActor(g_actor);

    ren->SetBackground(.1,.2,.3);

    VTK_CREATE(vtkRenderWindow, renw);
    renw->AddRenderer(ren);

    VTK_CREATE(vtkInteractorStyleTrackballCamera, style);

    VTK_CREATE(vtkRenderWindowInteractor, iren);
    iren->SetRenderWindow(renw);
    iren->SetInteractorStyle(style);
    iren->Initialize();
    iren->Start();
    return 0;
}
