#ifndef __NANOSQL
#define __NANOSQL

#include <sqlite3.h>
#include <string>
typedef struct
{
	char **arr;
	int row, col;
} Res;

typedef int CallbackFunc (void *notUsed, int argc, char **argv, char **colName);

class Sql
{
	public:
		Sql(const std::string& filename);
		~Sql();
		Res raw_result; // by get_table(query)
		std::string lasterr;
		bool is_tran() const;
		int exec(const std::string& query, CallbackFunc cb=NULL);
		int get_table(const std::string& query);
		inline char* result(long row, long col) const;
		inline char* colName(long col) const;
		int begin_tran();
		int end_tran();

	private:
		sqlite3* db_;
		bool tran_;
};


inline char* Sql::result(long row, long col) const
{
	return (raw_result.arr[ row*raw_result.col + col -1 ]);
}

inline char* Sql::colName(long col) const
{
	return raw_result.arr[col-1];
}
#endif
