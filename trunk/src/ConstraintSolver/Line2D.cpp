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

#include <sstream>

#include "Line2D.h"

const std::string SQL_line2d_database_schema = "CREATE TABLE line2d_list (id INTEGER PRIMARY KEY, dof_table_name TEXT NOT NULL, primitive_table_name TEXT NOT NULL, sketch_plane INTEGER NOT NULL, s1_dof INTEGER NOT NULL, t1_dof INTEGER NOT NULL, s2_dof INTEGER NOT NULL, t2_dof INTEGER NOT NULL);";

using namespace std;

void Line2D::GetTangent1(GiNaC::ex & s_component, GiNaC::ex & t_component)
{
	GiNaC::ex length = sqrt(pow(GetS1()->GetVariable()-GetS2()->GetVariable(),2)+pow(GetT1()->GetVariable()-GetT2()->GetVariable(),2));
	
	s_component = (GetS1()->GetVariable() - GetS2()->GetVariable())/length;
	t_component = (GetT1()->GetVariable() - GetT2()->GetVariable())/length;
}

void Line2D::GetTangent2(GiNaC::ex & s_component, GiNaC::ex & t_component)
{
	GiNaC::ex length = sqrt(pow(GetS1()->GetVariable()-GetS2()->GetVariable(),2)+pow(GetT1()->GetVariable()-GetT2()->GetVariable(),2));
	
	s_component = (GetS2()->GetVariable() - GetS1()->GetVariable())/length;
	t_component = (GetT2()->GetVariable() - GetT1()->GetVariable())/length;
}

void Line2D::GetTangent1(double & s_component, double & t_component)
{
	double length = sqrt(pow(GetS1()->GetValue()-GetS2()->GetValue(),2)+pow(GetT1()->GetValue()-GetT2()->GetValue(),2));
	
	s_component = (GetS1()->GetValue() - GetS2()->GetValue())/length;
	t_component = (GetT1()->GetValue() - GetT2()->GetValue())/length;
}

void Line2D::GetTangent2(double & s_component, double & t_component)
{
	double length = sqrt(pow(GetS1()->GetValue()-GetS2()->GetValue(),2)+pow(GetT1()->GetValue()-GetT2()->GetValue(),2));
	
	s_component = (GetS2()->GetValue() - GetS1()->GetValue())/length;
	t_component = (GetT2()->GetValue() - GetT1()->GetValue())/length;
}

// returns global coordinates of line end points
void Line2D :: Get3DLocations(double & x1, double & y1, double & z1,
															double & x2, double & y2, double & z2)
{
	sketch_plane_->Get3DLocation(s1_->GetValue(), t1_->GetValue(), x1, y1, z1);
	sketch_plane_->Get3DLocation(s2_->GetValue(), t2_->GetValue(), x2, y2, z2);
}

void Line2D::ApplySelectionMask(SelectionMask mask)
{
	if(mask == All || mask == Edges || mask == Lines)
		SetSelectable(true);
	else
		SetSelectable(false);
}

Line2D :: Line2D(const Point2DPointer point1, const Point2DPointer point2, SketchPlanePointer sketch_plane):
Edge2DBase(sketch_plane)
{
	AddPrimitive(point1);
	AddPrimitive(point2);
	AddPrimitive(sketch_plane);

	s1_ = point1->GetSDOF();
	t1_ = point1->GetTDOF();

	s2_ = point2->GetSDOF();
	t2_ = point2->GetTDOF();

	AddDOF(s1_);
	AddDOF(t1_);

	AddDOF(s2_);
	AddDOF(t2_);
}

Point2DPointer Line2D::GetPoint1()
{
	// create the actual point object
	Point2DPointer result(new Point2D(GetS1(), GetT1(), GetSketchPlane()));
	return result;
}

Point2DPointer Line2D::GetPoint2()
{
	// create the actual point object
	Point2DPointer result(new Point2D(GetS2(), GetT2(), GetSketchPlane()));
	return result;
}

void Line2D::AddToDatabase(sqlite3 *database)
{
	database_ = database;
	DatabaseAddRemove(true);
}

void Line2D::RemoveFromDatabase()
{
	DatabaseAddRemove(false);
}

void Line2D::DatabaseAddRemove(bool add_to_database) // Utility method used by AddToDatabase and RemoveFromDatabase
{
	string sql_do, sql_undo;

	stringstream dof_list_table_name;
	dof_list_table_name << "dof_table_" << GetID();
	stringstream primitive_list_table_name;
	primitive_list_table_name << "primitive_table_" << GetID();

	// First, create the sql statements to undo and redo this operation
	stringstream temp_stream;
	temp_stream.precision(__DBL_DIG__);
	temp_stream << "BEGIN; "
                << "INSERT INTO line2d_list VALUES(" 
                << GetID() << ",'" << dof_list_table_name.str() << "','" 
				<< primitive_list_table_name.str() << "'," << GetSketchPlane()->GetID() 
				<< "," << s1_->GetID() << "," << t1_->GetID()
				<< "," << s2_->GetID() << "," << t2_->GetID() << "); "
                << "INSERT INTO primitive_list VALUES("
                << GetID() << ",'line2d_list'); "
                << "COMMIT; ";

	if(add_to_database)
		sql_do = temp_stream.str();
	else
		sql_undo = temp_stream.str();

	temp_stream.str(""); // clears the string stream

	temp_stream << "BEGIN; "
				<< "DELETE FROM primitive_list WHERE id=" << GetID() 
				<< "; DELETE FROM line2d_list WHERE id=" << GetID() 
				<< "; COMMIT;";

	if(add_to_database)
		sql_undo = temp_stream.str();
	else
		sql_do = temp_stream.str();

	// add this object to the appropriate tables by executing the SQL command sql_insert 
	char *zErrMsg = 0;
	int rc = sqlite3_exec(database_, sql_do.c_str(), 0, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		if(add_to_database)
		{
			//std::cerr << "SQL error: " << zErrMsg << endl;
			sqlite3_free(zErrMsg);
			
			// the table "independent_dof_list" may not exist, attempt to create
			rc = sqlite3_exec(database_, ("ROLLBACK;"+SQL_line2d_database_schema).c_str(), 0, 0, &zErrMsg);  // need to add ROLLBACK since previous transaction failed
			if( rc!=SQLITE_OK ){
				std::string error_description = "SQL error: " + std::string(zErrMsg);
				sqlite3_free(zErrMsg);
				throw Ark3DException(error_description);
			}
	
			// now that the table has been created, attempt the insert one last time
			rc = sqlite3_exec(database_, sql_do.c_str(), 0, 0, &zErrMsg);
			if( rc!=SQLITE_OK ){
				std::string error_description = "SQL error: " + std::string(zErrMsg);
				sqlite3_free(zErrMsg);
				throw Ark3DException(error_description);
			}
		} else {
			std::string error_description = "SQL error: " + std::string(zErrMsg);
			sqlite3_free(zErrMsg);
			throw Ark3DException(error_description);
		}
	}

	// finally, update the undo_redo_list in the database with the database changes that have just been made
	// need to use sqlite3_mprintf to make sure the single quotes in the sql statements get escaped where needed
	char *sql_undo_redo = sqlite3_mprintf("INSERT INTO undo_redo_list(undo,redo) VALUES('%q','%q')",sql_undo.c_str(),sql_do.c_str());

	rc = sqlite3_exec(database_, sql_undo_redo, 0, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		std::string error_description = "SQL error: " + std::string(zErrMsg);
		sqlite3_free(zErrMsg);
		throw Ark3DException(error_description);
	}

	sqlite3_free(sql_undo_redo);

	// Now use the method provided by PrimitiveBase to create the tables listing the DOF's and the other Primitives that this primitive depends on
	DatabaseAddDeleteLists(add_to_database,dof_list_table_name.str(),primitive_list_table_name.str());
}
