#include<iostream>
#include<db_cxx.h>
using namespace std;

class DB {
	DbEnv *env; 
	public :
	
	DB() {
		env = new DbEnv(0); //db evironment
    		env->set_cachesize(0, 64 * 1024, 0); 
    		env->open("./database", DB_CREATE | DB_INIT_MPOOL, 0); //open environmet
	}
	~DB() {
		
	}
};
