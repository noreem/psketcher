#include "OccParallelLine2D.h"

OccParallelLine2D::OccParallelLine2D(Handle(AIS_InteractiveContext) ais_context, const Line2DPointer line1, const Line2DPointer line2):
OccPrimitiveBase(ais_context),
ParallelLine2D(line1,line2)
{
	GenerateAISObject();

	// Display the newly create ais_object
	Display();
}


void OccParallelLine2D::UpdateDisplay()
{
	// first, erase the pervious AIS_ParallelRelation from the display because we'll have to recreate it
	Erase();
	
	GenerateAISObject();

	Display();

	OccPrimitiveBase::UpdateDisplay();
}

void OccParallelLine2D::GenerateAISObject()
{
	// create the points needed to create the line segment
	double x1, y1, z1, x2, y2, z2;	
	line1_->Get3DLocations(x1, y1, z1, x2, y2, z2);

	double x3, y3, z3, x4, y4, z4;	
	line2_->Get3DLocations(x3, y3, z3, x4, y4, z4);

	oc_point1_.SetX(x1);
	oc_point1_.SetY(y1);
	oc_point1_.SetZ(z1);

	oc_point2_.SetX(x2);
	oc_point2_.SetY(y2);
	oc_point2_.SetZ(z2);

	oc_point3_.SetX(x3);
	oc_point3_.SetY(y3);
	oc_point3_.SetZ(z3);

	oc_point4_.SetX(x4);
	oc_point4_.SetY(y4);
	oc_point4_.SetZ(z4);

	// create the line segments (the AIS_ParallelRelation object needs to know where the lines are in order to display the parallel constraint)
	oc_shape1_ = BRepBuilderAPI_MakeEdge(oc_point1_,oc_point2_);
	oc_shape2_ = BRepBuilderAPI_MakeEdge(oc_point3_,oc_point4_);

	// define the plane that is needed by the AIS_parallelRelation object
	double coef_a, coef_b, coef_c, coef_d;
	line1_->GetSketchPlane()->GetABCD(coef_a,coef_b,coef_c,coef_d);
	oc_plane_ = new Geom_Plane(coef_a, coef_b, coef_c, coef_d);

	// create the interactive ais_object, this is what will actually be displayed
	ais_object_list_.push_back(new AIS_ParallelRelation(oc_shape1_,oc_shape2_,oc_plane_));
}
