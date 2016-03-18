/*
These are just generalized stored procedure calls to SQL Server
*/

#include "stdafx.h"

#include "DataAccess.h"

bool DataAccess::DataAccess::CallTransaction(System::String^ connString, System::String^ storedProcedure, DataTable params)
{
	//declaring the command and connection
	//connection MUST stay outside of try...catch for closing in the finally clause
	SqlCommand^ cmd = gcnew SqlCommand();
	SqlConnection^ conn = gcnew SqlConnection(connString);

	try {
		
		//create a command and assign the passed stored procedure name
		cmd->Connection = conn;
		cmd->CommandText = storedProcedure;
		cmd->CommandType = CommandType::StoredProcedure;

		//add any and all parameters to the command
		for each (DataRow^ row  in params.Rows)
		{
			SqlParameter^ temp = gcnew SqlParameter(row->ItemArray->GetValue(0)->ToString(), row->ItemArray->GetValue(1)->ToString());
			cmd->Parameters->Add(temp);
		}

		//execute the query
		conn->Open();
		cmd->ExecuteNonQuery();
		return true;
	}
	catch (...) {
		//I don't care about exceptions from this, at least not right now
		return false;
	}
	finally {
		//close the connection if it's open
		if (conn->State != ConnectionState::Open) {
			conn->Close();
		}
	}
}

DataTable^ DataAccess::DataAccess::CallQueryTable(System::String^ connString, System::String^ storedProcedure, DataTable params)
{
	//declaring the command and connection
	//dt MUST stay outside of try...catch for returning in the catch clause
	SqlCommand^ cmd = gcnew SqlCommand();
	SqlConnection^ conn = gcnew SqlConnection(connString);
	DataTable^ dt = gcnew DataTable();

	try
	{
		//create a command and assign the passed stored procedure name
		cmd->Connection = conn; // new SqlConnection(connString); ;
		cmd->CommandText = storedProcedure;
		cmd->CommandType = CommandType::StoredProcedure;

		//add any and all parameters to the command
		for each (DataRow^ row  in params.Rows)
		{
			SqlParameter^ temp = gcnew SqlParameter(row->ItemArray->GetValue(0)->ToString(), row->ItemArray->GetValue(1)->ToString());
			cmd->Parameters->Add(temp);
		}

		//get the data and return it
		SqlDataAdapter^ da = gcnew SqlDataAdapter(cmd);
		da->Fill(dt);
		return dt;
	}
	catch (...)
	{
		//I don't care about exceptions from this, at least not right now
		return dt;
	}
}

DataRow^ DataAccess::DataAccess::CallQueryRow(System::String^ connString, System::String^ storedProcedure, DataTable params)
{
	//declaring the command and connection
	//dt MUST stay outside of try...catch for returning in the catch clause
	DataTable^ dt = gcnew DataTable();
	SqlCommand^ cmd = gcnew SqlCommand();
	SqlConnection^ conn = gcnew SqlConnection(connString);

	try
	{
		//create a command and assign it to the passed stored procedure name
		cmd->Connection = conn; // new SqlConnection(connString); ;
		cmd->CommandText = storedProcedure;
		cmd->CommandType = CommandType::StoredProcedure;

		//add any and all parameters to the command
		for each (DataRow^ row  in params.Rows)
		{
			SqlParameter^ temp = gcnew SqlParameter(row->ItemArray->GetValue(0)->ToString(), row->ItemArray->GetValue(1)->ToString());
			cmd->Parameters->Add(temp);
		}

		//get the data and return it
		//would probably be better to use a System::Data::DataRow and return cmd->ExecuteScalar(), but I got lazy
		SqlDataAdapter^ da = gcnew SqlDataAdapter(cmd);
		da->Fill(dt);
		return dt->Rows[0]; 
	}
	catch (...)
	{
		//I don't care about exceptions from this, at least not right now
		return dt->Rows[0];
	}
}

String^ DataAccess::DataAccess::CallQueryField(System::String^ connString, System::String^ storedProcedure, DataTable params)
{
	//declaring the command and connection
	SqlCommand^ cmd = gcnew SqlCommand();
	SqlConnection^ conn = gcnew SqlConnection(connString);

	try {

		//create a command and assign it to the passed stored procedure name
		cmd->Connection = conn;
		cmd->CommandText = storedProcedure;
		cmd->CommandType = CommandType::StoredProcedure;

		//add any and all parameters to the command
		for each (DataRow^ row  in params.Rows)
		{
			SqlParameter^ temp = gcnew SqlParameter(row->ItemArray->GetValue(0)->ToString(), row->ItemArray->GetValue(1)->ToString());
			cmd->Parameters->Add(temp);
		}

		//return the executed query cast to a String
		conn->Open();
		return cmd->ExecuteScalar()->ToString();
	}
	catch (...) {
		//I don't care about exceptions from this, at least not right now
		return "";
	}
	finally {
		//close the connection if it's open
		if (conn->State != ConnectionState::Open) {
			conn->Close();
		}
	}
}