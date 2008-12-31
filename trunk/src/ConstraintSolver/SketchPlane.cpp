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

#include "SketchPlane.h"

const std::string SQL_sketch_plane_database_schema = "CREATE TABLE sketch_plane_list (id INTEGER PRIMARY KEY, dof_table_name TEXT NOT NULL, primitive_table_name TEXT NOT NULL, base_point INTEGER NOT NULL, normal_vector INTEGER NOT NULL, up_vector INTEGER NOT NULL);";

using namespace std;
using namespace GiNaC;

// Constructor for SketchPlane class
SketchPlane::SketchPlane ( VectorPointer normal, VectorPointer up, PointPointer base):
normal_(normal),
up_(up),
base_(base)
{
	AddPrimitive(normal);
	AddPrimitive(up);
	AddPrimitive(base);

	// @TODO need to check to insure that the normal vector and the up vector are normalized, calculations later on will assume this

	// @TODO need to make sure that up vector lies in plane defined by normal vector (up vector must be orthogonal to normal vector)

	// Populate the primitve base classes DOF list for each of the primitives referenced by this SketchPlane
	std::vector<DOFPointer> current_dof_list = normal_->GetDOFList();
	for(unsigned int current_dof = 0; current_dof < current_dof_list.size(); current_dof++)
	{
		AddDOF(current_dof_list[current_dof]);
	}

	current_dof_list = up_->GetDOFList();
	for(unsigned int current_dof = 0; current_dof < current_dof_list.size(); current_dof++)
	{
		AddDOF(current_dof_list[current_dof]);
	}

	current_dof_list = base_->GetDOFList();
	for(unsigned int current_dof = 0; current_dof < current_dof_list.size(); current_dof++)
	{
		AddDOF(current_dof_list[current_dof]);
	}
}

void SketchPlane::GetABCD ( double & coef_a, double & coef_b, double & coef_c, double & coef_d)
{
	mmcMatrix normal_vector = normal_->GetmmcMatrix();
	mmcMatrix base_vector = base_->GetmmcMatrix();

	coef_a = normal_vector(0,0);
	coef_b = normal_vector(1,0);
	coef_c = normal_vector(2,0);
	coef_d = normal_vector.DotProduct(base_vector);
}

// Return the global coordinates of a point on the sketch plane
void SketchPlane::Get3DLocation ( double s, double t, double & x, double & y, double & z)
{
	mmcMatrix j_vector = up_->GetmmcMatrix();  // t axis direction vector in sketch plane
	mmcMatrix i_vector = j_vector.CrossProduct(normal_->GetmmcMatrix()); // s axis direction vector in sketch plane

	mmcMatrix global_position = base_->GetmmcMatrix() + s*i_vector + t*j_vector;

	x = global_position(0,0);
	y = global_position(1,0);
	z = global_position(2,0);
}

// Find the closest pont on the sketch plane to the global coordinates x,y, and z and return its s and t coordinates
// the return value is the distance of the global point to the sketch plane (if the sketch plane normal vector is not normalized than the distance will be scaled)
double SketchPlane::GetSTLocation( double x, double y, double z, double &s, double &t)
{
	mmcMatrix global_point(3,1);
	global_point(0,0) = x;
	global_point(1,0) = y;
	global_point(2,0) = z;

	mmcMatrix normal_vector = normal_->GetmmcMatrix();
	mmcMatrix j_vector = up_->GetmmcMatrix();  // t axis direction vector in sketch plane
	mmcMatrix i_vector = j_vector.CrossProduct(normal_vector); // s axis direction vector in sketch plane

	mmcMatrix a_matrix = i_vector;
	a_matrix = a_matrix.CombineAsRow(j_vector);
	a_matrix = a_matrix.CombineAsRow(normal_vector);

	mmcMatrix result = a_matrix.GetInverse()*(global_point - base_->GetmmcMatrix());

	s = result(0,0);
	t = result(1,0);

	return result(2,0);
}

void SketchPlane::ApplySelectionMask(SelectionMask mask)
{
	if(mask == All)
		SetSelectable(true);
	else
		SetSelectable(false);
}

// method for adding this object to the SQLite3 database, needs to be implement by each child class
void SketchPlane::AddToDatabase(sqlite3 *database)
{
	database_ = database;
	DatabaseAddRemove(true);
}

void SketchPlane::RemoveFromDatabase()
{
	DatabaseAddRemove(false);
}

void SketchPlane::DatabaseAddRemove(bool add_to_database) // Utility method used by AddToDatabase and RemoveFromDatabase
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
                << "INSERT INTO sketch_plane_list VALUES(" 
                << GetID() << ",'" << dof_list_table_name.str() << "','" 
				<< primitive_list_table_name.str() << "'," << base_->GetID() 
				<< "," << normal_->GetID() << "," << up_->GetID() << "); "
                << "INSERT INTO primitive_list VALUES("
                << GetID() << ",'sketch_plane_list'); "
                << "COMMIT; ";

	if(add_to_database)
		sql_do = temp_stream.str();
	else
		sql_undo = temp_stream.str();

	temp_stream.str(""); // clears the string stream

	temp_stream << "BEGIN; "
				<< "DELETE FROM primitive_list WHERE id=" << GetID() 
				<< "; DELETE FROM sketch_plane_list WHERE id=" << GetID() 
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
			rc = sqlite3_exec(database_, ("ROLLBACK;"+SQL_sketch_plane_database_schema).c_str(), 0, 0, &zErrMsg);  // need to add ROLLBACK since previous transaction failed
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