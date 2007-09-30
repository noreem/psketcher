%module ark3d;
%{
#include "../ConstraintSolver/Primitives.h"
#include "../ConstraintSolver/Ark3DModel.h"
#include "/usr/include/boost/shared_ptr.hpp"
%}

%include "../ConstraintSolver/Ark3DModel.h"
%include "../ConstraintSolver/Primitives.h"
namespace boost {
  template<class T> class shared_ptr
  {
    public:
      T * operator-> () const;
  };
}

%template(DOFPointer) boost::shared_ptr<DOF>;
%template(IndependentDOFPointer) boost::shared_ptr<IndependentDOF>;
%template(DependentDOFPointer) boost::shared_ptr<DependentDOF>;
%template(PrimitiveBasePointer) boost::shared_ptr<PrimitiveBase>;
%template(PointPointer) boost::shared_ptr<Point>;
%template(VectorPointer) boost::shared_ptr<Vector>;
%template(SketchPlanePointer) boost::shared_ptr<SketchPlane>;
%template(Primitive2DBasePointer) boost::shared_ptr<Primitive2DBase>;
%template(Point2DPointer) boost::shared_ptr<Point2D>;
%template(Edge2DBasePointer) boost::shared_ptr<Edge2DBase>;
%template(LinePointer) boost::shared_ptr<Line>;
%template(Line2DPointer) boost::shared_ptr<Line2D>;
%template(ConstraintEquationBasePointer) boost::shared_ptr<ConstraintEquationBase>;
%template(DistancePoint2DPointer) boost::shared_ptr<DistancePoint2D>;
%template(DistancePointPointer) boost::shared_ptr<DistancePoint>;
%template(ParallelLinePointer) boost::shared_ptr<ParallelLine>;
%template(ParallelLine2DPointer) boost::shared_ptr<ParallelLine2D>;
%template(TangentEdge2DPointer) boost::shared_ptr<TangentEdge2D>;
%template(AngleLine2DPointer) boost::shared_ptr<AngleLine2D>;
%template(Arc2DPointer) boost::shared_ptr<Arc2D>;
%template(EdgeLoop2DPointer) boost::shared_ptr<EdgeLoop2D>;










