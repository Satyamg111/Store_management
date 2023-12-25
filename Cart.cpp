#include<iostream>
#include<db_cxx.h>
/* Cart information of customer*/
class Cart{
	int pid,quantity;
	string name;
	double price;
	public :
		Cart();
		Cart(int pid,string name,double price,int quantity) {
			this->pid = pid;
			this->name = name;
			this->price = price;
			this->quantity = quantity;
		}
		void setItem(int pid,string name,double price,int quantity) {
			this->pid = pid;
			this->name = name;
			this->price = price;
			this->quantity = quantity;
		}
		void displayProduct() {
			cout << pid << "\t" << name << "\t" << price << "\t" << quantity<<"\t";
		}
		int getId(){
			return this->pid;
		}
		int getQuantity() {
			return this->quantity;
		}
		int getPrice() {
			return this->price;
		}
};

class CartDB{

DbEnv *env; 
Db *db;
string dbn;
double total;
public:

	CartDB(){
		/*
		env = new DbEnv(0); //db evironment
    		env->set_cachesize(0, 64 * 1024, 0); 
    		env->open("./database", DB_CREATE | DB_INIT_MPOOL, 0); //open environmet
    		*/
		db = new Db(NULL,0); //create database
		db->open(nullptr, "database/cart.db", nullptr, DB_BTREE, DB_CREATE, 0);  //open database
		total = 0;
	}
	
	void setProduct(Cart cart){
		int pid = cart.getId();
		Dbt key((void*)&pid, sizeof(int));
        	Dbt value((void*)&cart, sizeof(Cart));
        	if(db->put(nullptr, &key, &value, 0)!=0){
        		cerr << "Error adding data : " << endl;
        		return;
        	}
        	total += (cart.getQuantity() * cart.getPrice());	
	}
	
	int getTotal() {
		return total;
	}
	void removeProduct(int pid) {
		Dbt key((void*)&pid, sizeof(int));
		if(db->del(NULL,&key,0) != 0){
			cout<<"Product not found !\n";
		}
		else {
			cout<<"Product removed Successfully !\n";
		}
	}
	/// get data from database;
	void displayCart(){
		Dbt key;
		Dbt val;
		
		Db my_db(NULL,0);
		my_db.open(nullptr, "database/cart.db", nullptr, DB_BTREE, DB_RDONLY, 0);
		Dbc *cursorp;
		try{
			db->cursor(NULL,&cursorp,0);
		
			int ret;
		
			while((ret = cursorp->get(&key,&val,DB_NEXT)) == 0) {
				Cart *c = (Cart*)(val.get_data());
				c->displayProduct();
				double t = (c->getQuantity() * c->getPrice());
				cout<< t<<"\n";
			}
			if(ret != DB_NOTFOUND) {
				cout<<"DB NOT FOUND\n";
			}
		}
		catch(DbException &e){
			db->err(e.get_errno()," Error");
		}
		catch(std :: exception &e){
			db->errx("Error : %s", e.what());
		}
		if(cursorp != NULL) {
			cursorp->close();
		}
		//my_db.close(0);
	}
};










