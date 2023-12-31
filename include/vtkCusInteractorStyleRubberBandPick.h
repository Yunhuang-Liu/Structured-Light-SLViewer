#ifndef vtkCusInteractorStyleRubberBandPick_h
#define vtkCusInteractorStyleRubberBandPick_h

#include "vtkRenderItem.h"
#include "vtkProcessEngine.h"

#include "vtkInteractionStyleModule.h" // For export macro
#include "vtkInteractorStyleTrackballCamera.h"

#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkCellData.h>
#include <vtkVertex.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPolyVertex.h>
#include <vtkDataSetMapper.h>
#include <vtkAreaPicker.h>
#include <vtkPlanes.h>
#include <vtkExtractGeometry.h>
#include <vtkProp3DCollection.h>
#include <vtkClipDataSet.h>

#include <QObject>
#include <QString>
#include <QVariant>

class vtkUnsignedCharArray;

class VTKProcessEngine;

class vtkCusInteractorStyleRubberBandPick
  : public vtkInteractorStyleTrackballCamera
{
public:
  static vtkCusInteractorStyleRubberBandPick* New();
  vtkTypeMacro(vtkCusInteractorStyleRubberBandPick, vtkInteractorStyleTrackballCamera);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  void clip(const bool isClipInner, double& progressVal);

  void cancelClip();

  void StartSelect();

  void stopSelect();

  void enablePointInfoMode(const bool isEnable);

  void bindStatusBar(QObject* statusBar);

  void bindRenderItem(VTKRenderItem* renderItem);

  void bindVtkProcessEngine(VTKProcessEngine* engine);

  void bindCloudActor(vtkActor* cloudActor);
  ///@{
  /**
   * Event bindings
   */
  void OnMouseMove() override;
  void OnLeftButtonDown() override;
  void OnLeftButtonUp() override;
  void OnRightButtonDown() override;
  ///@}

protected:
  vtkCusInteractorStyleRubberBandPick();
  ~vtkCusInteractorStyleRubberBandPick() override;

  virtual void Pick();

  int StartPosition[2];
  int EndPosition[2];

  int Moving;
  int CurrentMode;

private:
  vtkCusInteractorStyleRubberBandPick(const vtkCusInteractorStyleRubberBandPick&) = delete;
  void operator=(const vtkCusInteractorStyleRubberBandPick&) = delete;
  void singlePick();
  void areaPick();
  QObject* __statusBar;
  vtkNew<vtkActor> __highlightPoint;
  vtkNew<vtkActor> __areaSelectedPoints;
  VTKRenderItem* __renderItem;
  VTKProcessEngine* __processEngine;
  vtkActor* __cloudActor;
  vtkNew<vtkUnstructuredGrid> __cloudData;
  bool __pointInfoEnable;
};

#endif //!vtkCusInteractorStyleRubberBandPick_h
