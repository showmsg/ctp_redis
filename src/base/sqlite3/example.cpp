#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "nanosql.hpp"
using namespace std;

Sql s("123.db");
char op[1000];
int cb(void *notUsed, int argc, char **argv, char **colName)
{
	cout<<argc<<" col is selected"<<endl;
	for (int i=0;i<argc;++i)
	  cout<<colName[i]<<":"<<argv[i]<<endl;
	return 0;
}
int main()
{
	s.exec("drop table t");
	s.exec("create table t \
				(id integer PRIMARY KEY AUTOINCREMENT, \
				 name varchar(100) \
				)");
	cout<<s.lasterr<<endl;

	cout<<"begin inserting 1000000 row"<<endl;
	s.begin_tran();
	for (int i=1;i<=1000000;++i)
	{
		sprintf(op,"insert into t (name) VALUES ('%x')",rand() );
		if (i%10000==0) cout<<i/10000<<"% "<<flush;
		s.exec(op);
	}
	s.end_tran();
	cout<<"finished"<<endl;
	cout<<s.lasterr<<endl;


	s.get_table("select * from t order by name DESC limit 3");

	s.exec("select * from t order by id DESC limit 2",cb);

	for (int i=1;i<=s.raw_result.col;++i)
	  cout<<s.colName(i)<<" |";
	cout<<endl;
	for (int i=1;i<=s.raw_result.row;++i)
	{
		for (int j=1;j<=s.raw_result.col;++j)
		  cout<<s.result(i,j)<<",";
		cout<<endl;
	}

	return 0;
}
