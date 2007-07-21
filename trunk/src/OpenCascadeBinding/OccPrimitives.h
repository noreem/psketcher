#ifndef OccPrimitivesH
#define OccPrimitivesH

#include "../ConstraintSolver/Primitives.h"
#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <AIS_Point.hxx>
#include <AIS_Line.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Geom_Plane.hxx>

// OccPrimitiveBase class
class OccPrimitiveBase
{
	public:
		OccPrimitiveBase(Handle(AIS_InteractiveContext) ais_context) {ais_context_ = ais_context;}

		virtual ~OccPrimitiveBase() {/* @TODO add code here to delete ais_object_ from ais_context_ */;}

		virtual void Display();

	protected:
		Handle(AIS_InteractiveContext) ais_context_;
		Handle(AIS_InteractiveObject) ais_object_;
};

// point class
class OccPoint : public OccPrimitiveBase, public Point
{
	public:
		OccPoint (Handle(AIS_InteractiveContext) ais_context, double x, double y, double z, bool x_free = false, bool y_free = false, bool z_free = false);

		void Display() {return OccPrimitiveBase::Display();}
	private:

		Handle(Geom_Point) oc_point_;
};
typedef boost::shared_ptr<OccPoint> OccPointPointer;

// point class
class OccPoint2D : public OccPrimitiveBase, public Point2D
{
	public:
		OccPoint2D (Handle(AIS_InteractiveContext) ais_context,double s, double t, SketchPlanePointer sketch_plane, bool s_free = false, bool t_free = false);

		void Display() {return OccPrimitiveBase::Display();}

	private:
		Handle(Geom_Point) oc_point_;

};
typedef boost::shared_ptr<OccPoint2D> OccPoint2DPointer;

// line class
class OccLine : public OccPrimitiveBase, public Line
{
	public:
		OccLine (Handle(AIS_InteractiveContext) ais_context, const PointPointer point1, const PointPointer point2);

		void Display() {return OccPrimitiveBase::Display();}

	private:
		Handle(Geom_Point) oc_point1_;
		Handle(Geom_Point) oc_point2_;
};
typedef boost::shared_ptr<OccLine> OccLinePointer;

// line class
class OccLine2D : public OccPrimitiveBase, public Line2D
{
	public:
		OccLine2D (Handle(AIS_InteractiveContext) ais_context, const Point2DPointer point1, const Point2DPointer point2, SketchPlanePointer sketch_plane);

		void Display() {return OccPrimitiveBase::Display();}

	private:
		Handle(Geom_Point) oc_point1_;
		Handle(Geom_Point) oc_point2_;
};
typedef boost::shared_ptr<OccLine2D> OccLine2DPointer;

// line class
class OccParallelConstraint : public OccPrimitiveBase
{
	public:
		OccParallelConstraint (const ParallelConstraintPointer parallel_constraint_, Handle(AIS_InteractiveContext) ais_context);

		void Display() {return OccPrimitiveBase::Display();}

	private:
		ParallelConstraintPointer line_;

		Handle(Geom_Point) oc_point1_;
		Handle(Geom_Point) oc_point2_;

 		Handle(Geom_Plane) oc_plane_;
};
typedef boost::shared_ptr<OccParallelConstraint> OccParallelConstraintPointer;

#endif //OccPrimitivesH
