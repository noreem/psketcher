#ifndef OccSketchH
#define OccSketchH

#include "../ConstraintSolver/Sketch.h"
#include "OccPrimitives.h"

class OccSketch : public Sketch
{
	public:
		// constructor
		OccSketch(Handle(AIS_InteractiveContext) ais_context, VectorPointer normal, VectorPointer up, PointPointer base, bool grid_snap = false);
	
		// method to generate a gp_Ax3 object for the current SketchPlane
		gp_Ax3 Get_gp_Ax3();

		// accessor methods
		bool GetGridSnap() {return grid_snap_;}
		void SetGridSnap(bool grid_snap) {grid_snap_ = grid_snap;}
		Handle(AIS_InteractiveContext) GetAISContext() {return ais_context_;}

		// methods for adding primitives to the sketch
		OccPoint2DPointer AddPoint2D ( double s, double t, bool s_free, bool t_free);
		OccArc2DPointer AddArc2D (double s_center, double t_center, double theta_1, double theta_2, double radius, bool s_center_free, bool t_center_free, bool theta_1_free, bool theta_2_free, bool radius_free);
		OccLine2DPointer AddLine2D (const Point2DPointer point1, const Point2DPointer point2);
		OccDistancePoint2DPointer AddDistancePoint2D(const Point2DPointer point1, const Point2DPointer point2, double distance);
		OccDistancePoint2DPointer AddDistancePoint2D(const Point2DPointer point1, const Point2DPointer point2);
		OccParallelLine2DPointer AddParallelLine2D(const Line2DPointer line1, const Line2DPointer line2);
		OccAngleLine2DPointer AddAngleLine2D(const Line2DPointer line1, const Line2DPointer line2, double angle);
		OccTangentEdge2DPointer AddTangentEdge2D(Edge2DBasePointer edge1, EdgePointNumber point_num_1, Edge2DBasePointer edge2, EdgePointNumber point_num_2);

	private:
		Handle(AIS_InteractiveContext) ais_context_;
		bool grid_snap_;
};
typedef boost::shared_ptr<OccSketch> OccSketchPointer;


#endif //OccSketchH