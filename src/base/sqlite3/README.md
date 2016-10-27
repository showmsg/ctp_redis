NanoSQL
========

> NanoSQL是一个简单封装的C++ Sqlite3库，支持简单的事务，同时具有方便、迅速的语法

#基本内容
##Sql类
一个实例对应一个文件
```cpp
class Sql
{
		Sql(const std::string& filename); //文件名
		~Sql(); //安全析构
		Res raw_result; // by get_table(query)
		std::string lasterr; //上一个错误
		bool is_tran() const; //是否在一个事务中？
		int exec(const std::string& query, CallbackFunc cb=NULL); //执行语句，回调函数可以省略
		int get_table(const std::string& query); //把得到的table存到raw_result中
		inline char* result(long row, long col); //从1开始，快速获得raw_result中的结果
		inline char* colName(long col); //读取自raw_result
		int begin_tran(); //进入事务状态，错误会抛出runtime_error
		int end_tran();  //离开事务状态，错误会抛出runtime_error
};
```
##Res类
保存`get_table`的结果，析构时安全释放
```cpp
typedef struct
{
	char **arr;
	int row, col;
} Res;
```
#实例
详见目录下的`example.cpp`
