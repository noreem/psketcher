/****************************************************************************
**
** This file is part of the pSketcher project.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** Copyright (C) 2006-2008 Michael Greminger. All rights reserved.
**
****************************************************************************/

#ifndef QtSketchH
#define QtSketchH

#include <QGraphicsScene>

#include "../ConstraintSolver/Sketch.h"
#include "QtPrimitives.h"

//class QGraphicsScene;

class QtSketch : public Sketch
{
	public:
		// constructor
		QtSketch(QGraphicsScene *scene, VectorPointer normal, VectorPointer up, PointPointer base, bool grid_snap = false);

		// accessor methods
		bool GetGridSnap() {return grid_snap_;}
		void SetGridSnap(bool grid_snap) {grid_snap_ = grid_snap;}

		// override some of the Ark3DModel methods
		void ClearSelected() {scene_->clearSelection(); Ark3DModel::ClearSelected();}
		void AddConstraintEquation(const ConstraintEquationBasePointer &new_constraint_equation);
		void AddPrimitive(const PrimitiveBasePointer &new_primitive);

		// methods for adding primitives to the sketch
		QtPoint2DPointer AddPoint2D ( double s, double t, bool s_free, bool t_free);
		QtArc2DPointer AddArc2D (double s_center, double t_center, double theta_1, double theta_2, double radius, bool s_center_free, bool t_center_free, bool theta_1_free, bool theta_2_free, bool radius_free);
		QtArc2DPointer AddArc2D (double s1, double t1, double s2, double t2, double s3, double t3, bool s_center_free, bool t_center_free, bool theta_1_free, bool theta_2_free, bool radius_free);
		QtLine2DPointer AddLine2D (const Point2DPointer point1, const Point2DPointer point2);
		QtDistancePoint2DPointer AddDistancePoint2D(const Point2DPointer point1, const Point2DPointer point2, double distance);
		QtDistancePoint2DPointer AddDistancePoint2D(const Point2DPointer point1, const Point2DPointer point2);
		QtParallelLine2DPointer AddParallelLine2D(const Line2DPointer line1, const Line2DPointer line2);
		QtAngleLine2DPointer AddAngleLine2D(const Line2DPointer line1, const Line2DPointer line2, double angle, bool interior_angle);
		QtAngleLine2DPointer AddAngleLine2D(const Line2DPointer line1, const Line2DPointer line2, bool interior_angle);
		QtTangentEdge2DPointer AddTangentEdge2D(Edge2DBasePointer edge1, EdgePointNumber point_num_1, Edge2DBasePointer edge2, EdgePointNumber point_num_2);

	private:
		virtual void PreparePrimitiveForDeletion(PrimitiveBasePointer primitive_to_delete);

		QGraphicsScene *scene_;
		bool grid_snap_;
};
//typedef boost::shared_ptr<QtSketch> QtSketchPointer;
typedef QtSketch* QtSketchPointer;


#endif //QtSketchH