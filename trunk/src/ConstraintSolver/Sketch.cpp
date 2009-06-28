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
#include <iostream>
#include <sstream>
#include "Sketch.h"

const std::string SQL_sketch_database_schema = "CREATE TABLE sketch (sketch_plane INTEGER NOT NULL);";

Sketch::Sketch(VectorPointer normal, VectorPointer up, PointPointer base,PrimitiveBasePointer (*current_primitive_factory)(unsigned, Ark3DModel &), ConstraintEquationBasePointer (*current_constraint_factory)(unsigned, Ark3DModel &)):
Ark3DModel(current_primitive_factory, current_constraint_factory),
sketch_plane_(new SketchPlane(normal,up,base))
{
	AddPrimitive(sketch_plane_);
	AddToDatabase();
}

Sketch::Sketch(const std::string &file_name, PrimitiveBasePointer (*current_primitive_factory)(unsigned, Ark3DModel &), ConstraintEquationBasePointer (*current_constraint_factory)(unsigned, Ark3DModel &)):
Ark3DModel(file_name, current_primitive_factory, current_constraint_factory)
{
	// need to set the value for sketch_plane_ from the database
	char *zErrMsg = 0;
	int rc;
	sqlite3_stmt *statement;
	
	std::string sql_command = "SELECT * FROM sketch;";

	rc = sqlite3_prepare(GetDatabase(), sql_command.c_str(), -1, &statement, 0);
	if( rc!=SQLITE_OK ){
		std::stringstream error_description;
		error_description << "SQL error: " << sqlite3_errmsg(GetDatabase());
		throw Ark3DException(error_description.str());
	}

	rc = sqlite3_step(statement);

	if(rc == SQLITE_ROW) {
		// set the sketch plane based on the database
		sketch_plane_ = FetchPrimitive<SketchPlane>(sqlite3_column_int(statement,0));

	} else {
		// the requested row does not exist in the database
		sqlite3_finalize(statement);	

		throw Ark3DException("SketchPlane ID not stored in database, cannot initialize Sketch Object");
	}

	rc = sqlite3_step(statement);
	if( rc!=SQLITE_DONE ){
		// sql statement didn't finish properly, some error must to have occured
		std::stringstream error_description;
		error_description << "SQL error: " << sqlite3_errmsg(GetDatabase());
		throw Ark3DException(error_description.str());
	}
	
	rc = sqlite3_finalize(statement);
	if( rc!=SQLITE_OK ){
		std::stringstream error_description;
		error_description << "SQL error: " << sqlite3_errmsg(GetDatabase());
		throw Ark3DException(error_description.str());
	}

}

// Add the information needed by this class to the database
void Sketch::AddToDatabase()
{
	// initialize the database schema for this class
	char *zErrMsg = 0;
	int rc;
	rc = sqlite3_exec(GetDatabase(), SQL_sketch_database_schema.c_str(), 0, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		std::string error_description = "SQL error: " + std::string(zErrMsg);
		sqlite3_free(zErrMsg);
		throw Ark3DException(error_description);
	}

	// Add the database row for this class
	std::stringstream temp_stream;
	temp_stream << "INSERT INTO sketch VALUES("
                << sketch_plane_->GetID() << "); ";
	rc = sqlite3_exec(GetDatabase(), temp_stream.str().c_str(), 0, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		std::string error_description = "SQL error: " + std::string(zErrMsg);
		sqlite3_free(zErrMsg);
		throw Ark3DException(error_description);
	}

}

Point2DPointer Sketch::AddPoint2D ( double s, double t, bool s_free, bool t_free)
{
	Point2DPointer new_point(new Point2D(s,t,sketch_plane_,s_free,t_free));
	AddPrimitive(new_point);
	return new_point;
}


Arc2DPointer Sketch::AddArc2D (double s_center, double t_center, double theta_1, double theta_2, double radius, bool s_center_free, bool t_center_free, bool theta_1_free, bool theta_2_free, bool radius_free)
{
	Arc2DPointer new_arc(new Arc2D(s_center, t_center, theta_1, theta_2, radius, sketch_plane_,s_center_free, t_center_free, theta_1_free, theta_2_free, radius_free));
	AddPrimitive(new_arc);

	// now add the end points and the center of the arc as seperate primitives so that they can be selected by the user for constructing lines and other primitives
	// @fixme these points need to be removed fro the sketch if new_arc is ever deleted from the scene otherwise the arc will still drive the points but will not be visible
	AddPrimitive(new_arc->GetPoint1());
	AddPrimitive(new_arc->GetPoint2());
	AddPrimitive(new_arc->GetCenterPoint());

	return new_arc;
}

Circle2DPointer Sketch::AddCircle2D (double s_center, double t_center, double radius, bool s_center_free, bool t_center_free, bool radius_free)
{
    Circle2DPointer new_circle(new Circle2D(s_center, t_center, radius, sketch_plane_, s_center_free, t_center_free, radius_free));
    AddPrimitive(new_circle);

    AddPrimitive(new_circle->GetCenterPoint());

    return new_circle;
}

Arc2DPointer Sketch::AddArc2D (double s1, double t1, double s2, double t2, double s3, double t3, bool s_center_free, bool t_center_free, bool theta_1_free, bool theta_2_free, bool radius_free)
{
	bool success = true;
	
	Arc2DPointer new_arc;

	try{
		new_arc.reset(new Arc2D(s1,t1,s2,t2,s3,t3, sketch_plane_,s_center_free, t_center_free, theta_1_free, theta_2_free, radius_free));
	}
	catch (Ark3DException e)
	{
		// all three points were on a straight line so no arc could be made
		success = false;
	}
	
	if(success)
	{
		AddPrimitive(new_arc);
		
		// now add the end points and the center of the arc as seperate primitives so that they can be selected by the user for constructing lines and other primitives
		// @fixme these points need to be removed fro the sketch if new_arc is ever deleted from the scene otherwise the arc will still drive the points but will not be visible
		AddPrimitive(new_arc->GetPoint1());
		AddPrimitive(new_arc->GetPoint2());
		AddPrimitive(new_arc->GetCenterPoint());
	
	} 

	return new_arc;
}

Line2DPointer Sketch::AddLine2D (const Point2DPointer point1, const Point2DPointer point2)
{
	Line2DPointer new_line(new Line2D(point1, point2, sketch_plane_));
	AddPrimitive(new_line);
	return new_line;
}


DistancePoint2DPointer Sketch::AddDistancePoint2D(const Point2DPointer point1, const Point2DPointer point2, double distance)
{
	DistancePoint2DPointer new_constraint(new DistancePoint2D(point1,point2,distance));
	AddConstraintEquation(new_constraint);
	return new_constraint;
}

// Add a distance constraint using the current distance
DistancePoint2DPointer Sketch::AddDistancePoint2D(const Point2DPointer point1, const Point2DPointer point2)
{
	DistancePoint2DPointer new_constraint(new DistancePoint2D(point1,point2,1.0));  // using a temp distance of 1.0, will be replated by current distance next
	new_constraint->SetValue(new_constraint->GetActualDistance());
	AddConstraintEquation(new_constraint);
	return new_constraint;
}

// Add a distance constraint using the current distance
DistancePointLine2DPointer Sketch::AddDistancePointLine2D(const Point2DPointer point, const Line2DPointer line)
{
    DistancePointLine2DPointer new_constraint(new DistancePointLine2D(point,line,1.0));  // using a temp distance of 1.0, will be replated by current distance next
    new_constraint->SetValue(new_constraint->GetActualDistance());
    AddConstraintEquation(new_constraint);
    return new_constraint;
}

ParallelLine2DPointer Sketch::AddParallelLine2D(const Line2DPointer line1, const Line2DPointer line2)
{
	ParallelLine2DPointer new_constraint (new ParallelLine2D(line1, line2));
	AddConstraintEquation(new_constraint);
	return new_constraint;
}

HoriVertLine2DPointer Sketch::AddHoriVertLine2D(const Line2DPointer line, bool vertical_constraint)
{
	HoriVertLine2DPointer new_constraint (new HoriVertLine2D(line, vertical_constraint));
	AddConstraintEquation(new_constraint);
	return new_constraint;
}

AngleLine2DPointer Sketch::AddAngleLine2D(const Line2DPointer line1, const Line2DPointer line2, double angle, bool interior_angle)
{
	AngleLine2DPointer new_constraint(new AngleLine2D(line1,line2,angle,interior_angle));
	AddConstraintEquation(new_constraint);
	return new_constraint;
}

AngleLine2DPointer Sketch::AddAngleLine2D(const Line2DPointer line1, const Line2DPointer line2, bool interior_angle)
{
	AngleLine2DPointer new_constraint(new AngleLine2D(line1,line2,1.0,interior_angle)); // using a temp angle of 1.0, will be replaced by the current angle next
	new_constraint->SetAngleValue(new_constraint->GetActualAngle());
	AddConstraintEquation(new_constraint);
	return new_constraint;
}

TangentEdge2DPointer Sketch::AddTangentEdge2D(Edge2DBasePointer edge1, EdgePointNumber point_num_1, Edge2DBasePointer edge2, EdgePointNumber point_num_2)
{
	TangentEdge2DPointer new_constraint(new TangentEdge2D(edge1, point_num_1, edge2, point_num_2));
	AddConstraintEquation(new_constraint);
	return new_constraint;
}
