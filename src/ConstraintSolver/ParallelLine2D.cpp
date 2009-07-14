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

#include "IndependentDOF.h"
#include "ParallelLine2D.h"

#include "Ark3DModel.h"

const std::string SQL_parallel_line2d_database_schema = "CREATE TABLE parallel_line2d_list (id INTEGER PRIMARY KEY, dof_table_name TEXT NOT NULL, primitive_table_name TEXT NOT NULL, constraint_table_name TEXT NOT NULL, line1 INTEGER NOT NULL, line2 INTEGER NOT NULL, marker_position_dof INTEGER NOT NULL);";

using namespace std;
using namespace GiNaC;

// Create a parallelism constrain between two lines
ParallelLine2D::ParallelLine2D(const Line2DPointer line1, const Line2DPointer line2):
line1_(line1),
line2_(line2),
marker_position_(new IndependentDOF(0.5,false))   // by default place marker at the middle of the constrained lines
{
	AddPrimitive(line1);
	AddPrimitive(line2);

	AddDOF(line1_->GetS1());
	AddDOF(line1_->GetS2());
	AddDOF(line1_->GetT1());
	AddDOF(line1_->GetT2());

	AddDOF(line2_->GetS1());
	AddDOF(line2_->GetS2());
	AddDOF(line2_->GetT1());
	AddDOF(line2_->GetT2());

	AddDOF(marker_position_);

	// create the expression that defines the parallel constraint and add it the the constraint list
	boost::shared_ptr<ex> new_constraint(new ex);
	
    /*
	ex line1_ds = line1->GetS1()->GetVariable() - line1->GetS2()->GetVariable();
	ex line1_dt = line1->GetT1()->GetVariable() - line1->GetT2()->GetVariable();
	ex line1_length = sqrt(pow(line1_ds,2)+pow(line1_dt,2));

	ex line2_ds = line2->GetS1()->GetVariable() - line2->GetS2()->GetVariable();
	ex line2_dt = line2->GetT1()->GetVariable() - line2->GetT2()->GetVariable();
	ex line2_length = sqrt(pow(line2_ds,2)+pow(line2_dt,2));
    */

	// Calculate the dot product normalized by the vector lengths and subtract one
	// this expression will be zero when the lines are parallel
	// Ideally, I would use abs() instead of pow() but abs is not differentiable. 
	//*new_constraint = pow((1/(line1_length*line2_length))*(line1_ds*line2_ds + line1_dt*line2_dt),2)-1;

    *new_constraint = parallel_line_2d(line1->GetS1()->GetVariable(),line1->GetT1()->GetVariable(),line1->GetS2()->GetVariable(),line1->GetT2()->GetVariable(),line2->GetS1()->GetVariable(),line2->GetT1()->GetVariable(),line2->GetS2()->GetVariable(),line2->GetT2()->GetVariable());

	constraints_.push_back(new_constraint);
	weight_list_.push_back(1.0);
}

// Construct from database
ParallelLine2D::ParallelLine2D(unsigned id, Ark3DModel &ark3d_model)
{
	SetID(id);  bool exists = SyncToDatabase(ark3d_model);
	
	if(!exists) // this object does not exist in the table
	{
		stringstream error_description;
		error_description << "SQLite rowid " << id << " in table parallel_line2d_list does not exist";
		throw Ark3DException(error_description.str());
	}
}

void ParallelLine2D::AddToDatabase(sqlite3 *database)
{
	database_ = database;
	DatabaseAddRemove(true);
}

void ParallelLine2D::RemoveFromDatabase()
{
	DatabaseAddRemove(false);
}

void ParallelLine2D::DatabaseAddRemove(bool add_to_database) // Utility method used by AddToDatabase and RemoveFromDatabase
{
	string sql_do, sql_undo;

	stringstream dof_list_table_name;
	dof_list_table_name << "dof_table_" << GetID();
	stringstream primitive_list_table_name;
	primitive_list_table_name << "primitive_table_" << GetID();
	stringstream constraint_list_table_name;
	constraint_list_table_name << "constraint_table_" << GetID();

	//"CREATE TABLE parallel_line2d_list (id INTEGER PRIMARY KEY, dof_table_name TEXT NOT NULL, primitive_table_name TEXT NOT NULL, constraint_table_name TEXT NOT NULL, line1 INTEGER NOT NULL, line2 INTEGER NOT NULL, marker_position_dof INTEGER NOT NULL);";

	// First, create the sql statements to undo and redo this operation
	stringstream temp_stream;
	temp_stream.precision(__DBL_DIG__);
	temp_stream << "BEGIN; "
                << "INSERT INTO parallel_line2d_list VALUES(" 
                << GetID() << ",'" << dof_list_table_name.str() << "','" 
				<< primitive_list_table_name.str() 
				<< "','" << constraint_list_table_name.str()
				<< "'," << line1_->GetID() << "," << line2_->GetID()
				<< "," << marker_position_->GetID() << "); "
                << "INSERT INTO constraint_equation_list VALUES("
                << GetID() << ",'parallel_line2d_list'); "
                << "COMMIT; ";

	if(add_to_database)
		sql_do = temp_stream.str();
	else
		sql_undo = temp_stream.str();

	temp_stream.str(""); // clears the string stream

	temp_stream << "BEGIN; "
				<< "DELETE FROM constraint_equation_list WHERE id=" << GetID() 
				<< "; DELETE FROM parallel_line2d_list WHERE id=" << GetID() 
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
			rc = sqlite3_exec(database_, ("ROLLBACK;"+SQL_parallel_line2d_database_schema).c_str(), 0, 0, &zErrMsg);  // need to add ROLLBACK since previous transaction failed
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

	// Now use the methods provided by PrimitiveBase and ConstraintEquationBase to create the tables listing the DOF's, the other Primitives that this primitive depends on, and the constraint equations
	DatabaseAddDeleteLists(add_to_database,dof_list_table_name.str(),primitive_list_table_name.str());
	DatabaseAddDeleteConstraintList(add_to_database, constraint_list_table_name.str());
}


bool ParallelLine2D::SyncToDatabase(Ark3DModel &ark3d_model)
{
	database_ = ark3d_model.GetDatabase();

	string table_name = "parallel_line2d_list";

	char *zErrMsg = 0;
	int rc;
	sqlite3_stmt *statement;
	
	stringstream sql_command;
	sql_command << "SELECT * FROM " << table_name << " WHERE id=" << GetID() << ";";

	rc = sqlite3_prepare(ark3d_model.GetDatabase(), sql_command.str().c_str(), -1, &statement, 0);
	if( rc!=SQLITE_OK ){
		stringstream error_description;
		error_description << "SQL error: " << sqlite3_errmsg(ark3d_model.GetDatabase());
		throw Ark3DException(error_description.str());
	}

	rc = sqlite3_step(statement);

	stringstream dof_table_name, primitive_table_name, constraint_table_name;

	if(rc == SQLITE_ROW) {
		// row exists, store the values to initialize this object
		
		dof_table_name << sqlite3_column_text(statement,1);
		primitive_table_name << sqlite3_column_text(statement,2);
		constraint_table_name << sqlite3_column_text(statement,3);
		line1_ = ark3d_model.FetchPrimitive<Line2D>(sqlite3_column_int(statement,4));
		line2_ = ark3d_model.FetchPrimitive<Line2D>(sqlite3_column_int(statement,5));
		marker_position_ = ark3d_model.FetchDOF(sqlite3_column_int(statement,6));

	} else {
		// the requested row does not exist in the database
		sqlite3_finalize(statement);	

		return false; // row does not exist in the database, exit method and return false
	}

	rc = sqlite3_step(statement);
	if( rc!=SQLITE_DONE ){
		// sql statement didn't finish properly, some error must to have occured
		stringstream error_description;
		error_description << "SQL error: " << sqlite3_errmsg(ark3d_model.GetDatabase());
		throw Ark3DException(error_description.str());
	}
	
	rc = sqlite3_finalize(statement);
	if( rc!=SQLITE_OK ){
		stringstream error_description;
		error_description << "SQL error: " << sqlite3_errmsg(ark3d_model.GetDatabase());
		throw Ark3DException(error_description.str());
	}

	// now sync the lists store in the base classes
	SyncListsToDatabase(dof_table_name.str(),primitive_table_name.str(),ark3d_model); // PrimitiveBase
	SyncConstraintListToDatabase(constraint_table_name.str(),ark3d_model); // ConstraintEquationBase 

	return true; // row existed in the database
}

