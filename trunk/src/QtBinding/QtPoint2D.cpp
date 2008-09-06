#include <QtGui>

#include "QtPoint2D.h"

QtPoint2D::QtPoint2D (QGraphicsItem * parent,double s, double t, SketchPlanePointer sketch_plane, bool s_free, bool t_free) :
QtPrimitiveBase(parent),
Point2D(s,t,sketch_plane,s_free,t_free)
{
	SetProperties(PointPrimitive);
	SetSelectedProperties(SelectedPointPrimitive);
	SetMouseHoverProperties(HoverPointPrimitive);

	setZValue(GetProperties().GetZ());

	double x_position, y_position, z_position;

	Get3DLocation(x_position, y_position, z_position);

	// Display the newly create ais_object
	Display();
}

QtPoint2D::QtPoint2D (QGraphicsItem * parent, DOFPointer s, DOFPointer t, SketchPlanePointer sketch_plane) :
QtPrimitiveBase(parent),
Point2D(s,t,sketch_plane)
{
	SetProperties(PointPrimitive);
	SetSelectedProperties(SelectedPointPrimitive);
	SetMouseHoverProperties(HoverPointPrimitive);

	setZValue(GetProperties().GetZ());

	double x_position, y_position, z_position;

	Get3DLocation(x_position, y_position, z_position);

	// Display the newly create ais_object
	Display();
}

void QtPoint2D::UpdateDisplay()
{
	double x_position, y_position, z_position;

	Get3DLocation(x_position, y_position, z_position);


	QtPrimitiveBase::UpdateDisplay();
}

QRectF QtPoint2D::boundingRect() const
{
	QRectF rect(QPointF(GetSValue(),-GetTValue()),
 				QPointF(GetSValue(),-GetTValue()));
	
	// increase the size of the box to account for the actual radius of the point that represents the circle
	// @fixme if the user zooms out or if the model has a large length scale, the bounding box wont contain the whole point
	rect.adjust(-GetBoundingRectPad(),-GetBoundingRectPad(),GetBoundingRectPad(),GetBoundingRectPad());
	
	return rect;
}

void QtPoint2D::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */) 
{
	DisplayProperties current_properties;

	// @fixme the way constraint_properties is defined in the following if statement block will prevent the user from changing the display properties of the point constraints at run time since the DisplayProperties constructor is used to set these properties
	DisplayProperties constraint_properties;

	if(option->state & QStyle::State_MouseOver && IsSelectable())
	{
		current_properties = GetMouseHoverProperties();
		constraint_properties = DisplayProperties(HoverAnnotation);
	} else if (option->state & QStyle::State_Selected) {
		current_properties = GetSelectedProperties();
		constraint_properties = DisplayProperties(SelectedAnnotation);
	} else {
		current_properties = GetProperties();
		constraint_properties = DisplayProperties(Annotation);
	}

	painter->setPen(current_properties.GetPen(option->levelOfDetail));
	painter->setBrush(current_properties.GetBrush());	

	QPainterPath point_path;
	PaintPointAndSelectionPath(painter, option, GetSValue(), -GetTValue(),point_path);

	// if point is constrained, draw the constraints
	if(! SIsFree() || ! TIsFree())
	{
		painter->setPen(constraint_properties.GetPen(option->levelOfDetail));
		painter->setBrush(constraint_properties.GetBrush());
		
		double radius = 5.0/option->levelOfDetail;

		if((! SIsFree() && ! GetSDOF()->IsDependent() )  && (! TIsFree() && ! GetTDOF()->IsDependent() ))
		{
			QRectF rect(QPointF(GetSValue()-radius,-(GetTValue()-radius)),
			QPointF(GetSValue()+radius,-(GetTValue()+radius)));
			painter->setBrush(Qt::NoBrush);
			painter->drawEllipse(rect);

		} else if((! SIsFree() && ! GetSDOF()->IsDependent() )) {

			painter->drawLine(QPointF(GetSValue()-radius,-(GetTValue()-radius)),
			QPointF(GetSValue()-radius,-(GetTValue()+radius)));

			painter->drawLine(QPointF(GetSValue()+radius,-(GetTValue()-radius)),
			QPointF(GetSValue()+radius,-(GetTValue()+radius)));

		} else if((! TIsFree() && ! GetTDOF()->IsDependent() )) {

			painter->drawLine(QPointF(GetSValue()+radius,-(GetTValue()+radius)),
			QPointF(GetSValue()-radius,-(GetTValue()+radius)));

			painter->drawLine(QPointF(GetSValue()-radius,-(GetTValue()-radius)),
			QPointF(GetSValue()+radius,-(GetTValue()-radius)));
		}
	}
	

	current_shape_ = point_path;
}
