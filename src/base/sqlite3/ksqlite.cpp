#include <string>
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <sqlite3.h>
#include "ksqlite.h"

using namespace std;

Sql::Sql(const string& filename):tran_(false) 
{
	raw_result.arr = NULL;
	raw_result.row = 0;
	raw_result.col = 0;
	sqlite3_open(filename.c_str(), &db_);
}

Sql::~Sql()
{
	sqlite3_close(db_);
	sqlite3_free_table(raw_result.arr);
}

bool Sql::is_tran() const
{
	return tran_;
}

int Sql::begin_tran()
{
	if (tran_)
	  throw runtime_error("already in transaction");
	exec("begin;");
	tran_=true;
	return 0;
}

int Sql::end_tran()
{
	if (!tran_)
	  throw runtime_error("not in transaction yet");
	exec("commit;");
	tran_=false;
	return 0;
}
int Sql::exec(const string& query, CallbackFunc cb)
{
	static char* clasterr=NULL;
	sqlite3_exec(db_, query.c_str(), cb, 0, &clasterr);
	if (clasterr!=NULL) lasterr=clasterr;
	return static_cast<bool>(clasterr);
}

int Sql::get_table(const string& query)
{
	static char* clasterr=NULL;
	sqlite3_get_table(db_, query.c_str(), &raw_result.arr, &raw_result.row, &raw_result.col, &clasterr);
	if (clasterr!=NULL) lasterr=clasterr;
	return static_cast<bool>(clasterr);
}
