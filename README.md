## ClippingPlaneWidget

A single project made in [VTK] to handle a `vtkPlaneWidget` as a clipping plane. It uses 1 plane which is manipulated using the widget (scale, rotate and translated). At the beginning is placed around 1 actor.

A [vtkClipPolyData] is used with a clip function defined as a `vtkPlane`, extracted from the `vtkPlaneWidget`. Also, a callback (i.e. `vtkCommand::InteractionEvent` type) is used to update on real time the clipped area, using a C++ lambda function.

### Installation

[Cmake] is required to create the project with the *CMake GUI* or with the `cmake` command.

>To do: close the clipped area with new polydata


[VTK]: <https://www.vtk.org/>
[vtkClipPolyData]: <https://www.vtk.org/doc/nightly/html/classvtkClipPolyData.html>
[Cmake]: <https://cmake.org/>