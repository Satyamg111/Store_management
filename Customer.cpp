#include<iostream>
#include<db_cxx.h> 
using namespace std;
/* Customer database */
class Customer{
	int id;
	string name;
	int points;
	public:
		void addCostomer(int id,string name) { 
			this->id = id;
			this->name = name;
			this->points = 0;
		}
		int getId() {
			return this->id;
		}	
		void updatePoints(int p) {
			points += p;
		}
};


class CustomerDB{

DbEnv *env; 
Db *db;
string dbn;

public:

	CustomerDB(){
		/*
		env = new DbEnv(0); //db evironment
    		env->set_cachesize(0, 64 * 1024, 0); 
    		env->open("./database", DB_CREATE | DB_INIT_MPOOL, 0); //open environmet
    		*/
		db = new Db(NULL,0); //create database
		db->open(nullptr, "database/customer.db", nullptr, DB_BTREE, DB_CREATE, 0);  //open database
	}
	void setCustomer(Customer customer){
		int cid = customer.getId();
		Dbt key((void*)&cid, sizeof(int));
        	Dbt value((void*)&customer, sizeof(Customer));
        	if(db->put(nullptr, &key, &value, 0)!=0){
        		cerr << "Error adding : " << endl;
        	}
        
	}
	Customer getCostomer(int cid) {
		Dbt key((void*)&cid, sizeof(int));
		Dbt val;
		Customer *c;
		
		return *c; 
	}
	/// get data from database;
	
	
};

















