#include <QMouseEvent>

#include <cmath>
#include <QtGui>

#include "Ark3DWidget.h"
#include "../QtBinding/QtPrimitives.h"
#include "../InteractiveConstructors/QtEventProperties.h"
#include "Point2DEditDialog.h"

Ark3DWidget::Ark3DWidget(QGraphicsScene * scene, QWidget * parent) :
QGraphicsView(scene, parent)
{
	interactive_primitive_ = 0;

	GenerateDefaultSketch();

	setInteractive(true);  // allow selections and other mouse interactions
	setDragMode(QGraphicsView::RubberBandDrag);	
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate); // update whole scene at a time
	setRenderHints(QPainter::Antialiasing); // enable antialiasing
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse); 

	// turn off scroll bars (the mouse will be used to pan the scene)
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//setMouseTracking(true);

/*
	// create the python interpretor instance
	PyImport_AppendInittab( "ark3d_module", &initark3d_module );
	Py_Initialize();
	//init_ark3d_module();
	PyRun_SimpleString("import ark3d_module \n");
	PyRun_SimpleString("import sys \n");
	PyRun_SimpleString("sys.path.append('./src/PythonBinding/') \n");
	PyRun_SimpleString("import ark3d_module \n");
	
	PyRun_SimpleString("point1 =  ark3d_module.CreatePoint(0.0,1.0,2.0) \n");
	PyRun_SimpleString("print point1.GetYDOF().GetValue() \n");
*/
}

Ark3DWidget::~Ark3DWidget()
{
	if(interactive_primitive_ != 0)
		delete interactive_primitive_;
}

void Ark3DWidget::select()
{
	if(current_sketch_.get() != 0)
		current_sketch_->ApplySelectionMask(All);

	// delete any interactive primitives that were in the process of being constructed
	delete interactive_primitive_;
	interactive_primitive_ = 0;
}

void Ark3DWidget::paintEvent        ( QPaintEvent* e )
{
	QGraphicsView::paintEvent(e);
}

void Ark3DWidget::resizeEvent       ( QResizeEvent* e )
{
	QGraphicsView::resizeEvent(e);
}

void Ark3DWidget::mousePressEvent   ( QMouseEvent* e )
{
	if(interactive_primitive_ != 0 && !(e->button() & Qt::MidButton))
	{
		MouseEventPropertiesPointer event_props(new QtMouseEventProperties((MouseButtonEventType)ButtonPress,e,this));
		bool finished = false;

		switch (e->button() && !(e->button() & Qt::MidButton)) {
			case Qt::LeftButton:
				QGraphicsView::mousePressEvent(e);
				finished = interactive_primitive_->LeftButtonDown(event_props);
				break;
			case Qt::MidButton:   finished = interactive_primitive_->MiddleButtonDown(event_props); break;
			case Qt::RightButton: finished = interactive_primitive_->RightButtonDown(event_props); break;
			default:              finished = false; 
		}

		if(finished)
		{
			// The interactive primitive is finished, so allow it to create its object and then clean it up
			interactive_primitive_->CreateObject();
			delete interactive_primitive_;
			interactive_primitive_ = 0;
			// @fixme redraw();
			emit sketchActionFinished();
		}
	} else if (e->button() & Qt::MidButton) {
		// begin pan event and change cursor to a hand to convey this to the user
		QGraphicsView::mousePressEvent(e);
		setCursor(Qt::SizeAllCursor);
	} else {
		QGraphicsView::mousePressEvent(e);
	}

	previous_mouse_position_ = e->pos();
}

void Ark3DWidget::mouseReleaseEvent ( QMouseEvent* e )
{
	
	if(interactive_primitive_ != 0 && !((e->button() & Qt::MidButton)))
	{
		MouseEventPropertiesPointer event_props(new QtMouseEventProperties((MouseButtonEventType)ButtonRelease,e,this));
		bool finished = false;

		switch (e->button()) {
			case Qt::LeftButton:
				QGraphicsView::mouseReleaseEvent(e); // allow the user to select an object
				finished = interactive_primitive_->LeftButtonUp(event_props); 
				break;
			case Qt::MidButton:   finished = interactive_primitive_->MiddleButtonUp(event_props); break;
			case Qt::RightButton: finished = interactive_primitive_->RightButtonUp(event_props); break;
			default:              finished = false;
		}

		if(finished)
		{
			// The interactive primitive is finished, so allow it to create its object and then clean it up
			interactive_primitive_->CreateObject();
			delete interactive_primitive_;
			interactive_primitive_ = 0;
			// @fixme redraw();
			emit sketchActionFinished();
		}
	} else if (e->button() & Qt::MidButton) {
		// pan event has ended to reset cursor to its default
		unsetCursor();
	} else {
		QGraphicsView::mouseReleaseEvent(e);
	}

}

void Ark3DWidget::mouseMoveEvent    ( QMouseEvent* e )
{	
	if(interactive_primitive_ != 0 && !(e->buttons() & Qt::MidButton))
	{
		if(e->buttons() & Qt::LeftButton)
			QGraphicsView::mouseMoveEvent(e); // allows selection hinting to occur

		QGraphicsView::mouseMoveEvent(e);
		MotionEventPropertiesPointer event_props(new QtMotionEventProperties(e,this));
		if(interactive_primitive_->MouseMove(event_props))
		{
			// The interactive primitive is finished, so allow it to create its object and then clean it up
			interactive_primitive_->CreateObject();
			delete interactive_primitive_;
			interactive_primitive_ = 0;
			// @fixme redraw();
			emit sketchActionFinished();
		}
	} else if(e->buttons() & Qt::MidButton) {
		// translate the scene rectangle when the middle mouse button is pressed and moved
		//QPointF delta = mapToScene(e->pos()) - mapToScene(previous_mouse_position_);
		
		QPointF delta = (e->pos()) - (previous_mouse_position_);
		
		//std::cout << "(x,y) = (" << delta.x() << ", " << delta.y() << ")"<< std::endl;
		
		horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
		verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());

	} else {
		QGraphicsView::mouseMoveEvent(e);
	}
	previous_mouse_position_ = e->pos();
}

// Wheel event causes the scene to zoon in or out
void Ark3DWidget::wheelEvent        ( QWheelEvent* e )
{
	double numDegrees = -e->delta()/8.0;
	double numSteps = numDegrees / 15.0;
	double factor = std::pow(1.125, numSteps);
	scale(factor, factor);
}

void Ark3DWidget::leaveEvent		   ( QEvent * e)
{
	QGraphicsView::leaveEvent(e);
}

void Ark3DWidget::GenerateDefaultSketch()
{
	// create the current Ark3D sketch
	VectorPointer normal( new Vector(0.0,0.0,1.0));
	VectorPointer up( new Vector(0.0,1.0,0.0));
	PointPointer base( new Point(0.0,0.0,0.0));
	current_sketch_ = QtSketchPointer(new QtSketch(scene(),normal, up, base));
}

void Ark3DWidget::GenerateTestSketch()
{
	Point2DPointer point1 = current_sketch_->AddPoint2D(0.0,0.0,false,false);  // none of the dof's can vary
	Point2DPointer point2 = current_sketch_->AddPoint2D(10.0,0.0,true,false);  // only x dof can vary
	Point2DPointer point3 = current_sketch_->AddPoint2D(10.0,10.0,true,true);  // x and y dof's can vary

	Arc2DPointer arc1 = current_sketch_->AddArc2D(1.5,6.0,(mmcPI/2.0)*.8,(mmcPI)*1.2,2.0,true,true,true,true,false);

	Line2DPointer line1 = current_sketch_->AddLine2D(point1,point2);
	Line2DPointer line2 = current_sketch_->AddLine2D(point2,point3);
	Line2DPointer line3 = current_sketch_->AddLine2D(point3,arc1->GetPoint1());
	Line2DPointer line4 = current_sketch_->AddLine2D(arc1->GetPoint2(),point1);

	// These 5 constraints will fully constrain the four free DOF's defined about
	ConstraintEquationBasePointer constraint1 = current_sketch_->AddDistancePoint2D(point1,point2,6.0);
	ConstraintEquationBasePointer constraint2 = current_sketch_->AddDistancePoint2D(point2,point3,12.0);
	ConstraintEquationBasePointer constraint3 = current_sketch_->AddParallelLine2D(line1,line3);
	ConstraintEquationBasePointer constraint4 = current_sketch_->AddParallelLine2D(line2,line4);
	ConstraintEquationBasePointer constraint5 = current_sketch_->AddAngleLine2D(line1,line2,mmcPI/2.0,false);
	//ConstraintEquationBasePointer constraint8 = current_sketch_->AddAngleLine2D(line2,line3,mmcPI/2.0,false);

	ConstraintEquationBasePointer constraint6 = current_sketch_->AddTangentEdge2D(line3,Point2,arc1,Point1);
	ConstraintEquationBasePointer constraint7 = current_sketch_->AddTangentEdge2D(line4,Point1,arc1,Point2);
	
	// create an edge loop
	EdgeLoop2DPointer edge_loop1(new EdgeLoop2D());
	edge_loop1->AddEdge(line1);
	edge_loop1->AddEdge(line2);
	edge_loop1->AddEdge(line3);
	edge_loop1->AddEdge(arc1);
	edge_loop1->AddEdge(line4);
	std::cout << "Is loop valid: " << edge_loop1->IsLoopValid() << std::endl;

	//current_sketch_->ApplySelectionMask(Points);
	//current_sketch_->ApplySelectionMask(Edges);

	fitExtents();
}

void Ark3DWidget::SolveConstraints() 
{
	if(current_sketch_.get() != 0)
	{
		current_sketch_->SolveConstraints();
		current_sketch_->UpdateDisplay();
	}
}

void Ark3DWidget::ExecutePythonScript()
{
/*
    FILE *fp = fopen ("./src/PythonScripts/test_sketch.py", "r+");
    PyRun_SimpleFile (fp, "./src/PythonScripts/test_sketch.py");
		fclose(fp);
*/
}

void Ark3DWidget::MakeLine() 
{
	if(interactive_primitive_ != 0) delete interactive_primitive_;
	interactive_primitive_ = new Line2DConstructor(current_sketch_);
}

void Ark3DWidget::MakePolyLine() {;}

void Ark3DWidget::MakeArc()
{
	if(interactive_primitive_ != 0) delete interactive_primitive_;
	interactive_primitive_ = new Arc2DConstructor(current_sketch_);
}

void Ark3DWidget::MakePoint() 
{
	if(interactive_primitive_ != 0) delete interactive_primitive_;
	interactive_primitive_ = new Point2DConstructor(current_sketch_);
}

void Ark3DWidget::MakeDistanceConstraint() 
{
	if(interactive_primitive_ != 0) delete interactive_primitive_;
	interactive_primitive_ = new DistancePoint2DConstructor(current_sketch_);
}

void Ark3DWidget::MakeAngleConstraint() 
{
	if(interactive_primitive_ != 0) delete interactive_primitive_;
	interactive_primitive_ = new AngleLine2DConstructor(current_sketch_);
}

void Ark3DWidget::MakeTangentConstraint()
{
	if(interactive_primitive_ != 0) delete interactive_primitive_;
	interactive_primitive_ = new TangentEdge2DConstructor(current_sketch_);
}


void Ark3DWidget::MakeParallelConstraint()
{
	if(interactive_primitive_ != 0) delete interactive_primitive_;
	interactive_primitive_ = new ParallelLine2DConstructor(current_sketch_);
}

// double clicking causes the currently selected item to span its edit dialog
void Ark3DWidget::mouseDoubleClickEvent ( QMouseEvent * event )
{
	if(interactive_primitive_ == 0 && !(event->modifiers() & Qt::ShiftModifier))
	{
		// edit the selected item (only edit if not in multi-select mode

		// first, make sure that a primitive is selected
		std::vector<PrimitiveBasePointer> primitive_list = current_sketch_->GetSelectedPrimitives();
		if(primitive_list.size() >= 1 )
		{
			if(dynamic_cast<QtPoint2D*>(primitive_list[0].get()) != 0)
			{
				QtPoint2DPointer selected_point = boost::dynamic_pointer_cast<QtPoint2D>(primitive_list[0]);
			
				// create the point edit dialog
				Point2DEditDialog *point_edit_dialog = new Point2DEditDialog(selected_point, this);
				connect(point_edit_dialog, SIGNAL(modelChanged()), this, SLOT(modelChanged()));
				point_edit_dialog->show();
			} 
		}

	} else {
		QGraphicsView::mouseDoubleClickEvent(event);
	}
}

// This slot is called whenever the model changes
// This slot will handle updating the display and the undo history
void Ark3DWidget::modelChanged()
{
	current_sketch_->UpdateDisplay();
}

void Ark3DWidget::fitExtents()
{
	QRectF rect = scene()->itemsBoundingRect();
	std::cout << "bounding rect " << rect.x() << ", " << rect.y() << ", " << rect.width() << ", " << rect.height() << std::endl;
	fitInView(rect,Qt::KeepAspectRatio);
}

void Ark3DWidget::drawBackground ( QPainter * painter, const QRectF & rect )
{
	// resize the scene rectangle to twice the visible rectangle which is passed to this function
	QRectF scene_rect;
	
	QPointF center_point = rect.center(); // current centerpoint of rectangle
	QSizeF size = rect.size(); // current size of rectangle
	size.setWidth(size.width()*2.0);
	size.setHeight(size.height()*2.0);
	scene_rect.setSize(size);  // scale rectangle, top left corner will not move
	scene_rect.moveCenter(center_point); // move center of rectangle back to the original center
	
	// finally, set the scene rectangle
	setSceneRect(scene_rect);

	// let the base class do its thing
	QGraphicsView::drawBackground(painter, rect);
}

void Ark3DWidget::SelectUnderMouse(QMouseEvent *e, bool multi_select)
{


}

void Ark3DWidget::keyReleaseEvent ( QKeyEvent * event )
{
	if(event->key() == Qt::Key_Delete)
	{
		current_sketch_->DeleteSelected();
	} else {
		// not handling the event, call the base class implementation
		QGraphicsView::keyReleaseEvent(event);
	}
}
