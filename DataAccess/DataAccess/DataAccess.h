// DataAccess.h

#pragma once

#include <string>

#using <System.dll>
#using <System.Data.dll>

using namespace std;
using namespace System;
using namespace System::Data;
using namespace System::Data::Sql;
using namespace System::Data::SqlClient;

namespace DataAccess {

	public ref class DataAccess
	{
		// TODO: Add your methods for this class here.
	public: 
		bool CallTransaction(System::String^, System::String^, DataTable);
		DataTable^ CallQueryTable(System::String^, System::String^, DataTable);
		DataRow^ CallQueryRow(System::String^, System::String^, DataTable);
		String^ CallQueryField(System::String^, System::String^, DataTable);
	};
}
