#include<iostream>
#include<db_cxx.h>
using namespace std;

class Product{

	int id;
	string name;
	int quantity;
	double price;
	public :
	Product() {}
	Product(int id) {
		this->id = id;
	}
	Product(int id,string name, double price, int quantity) {
		this->id = id;
		this->name = name;
		this->price = price;
		this->quantity = quantity;
	}
	void addProduct(int id,string name, double price, int quantity) {
		this->id = id;
		this->name = name;
		this->price = price;
		this->quantity = quantity;
	}
	void displayProduct() {
		cout << id << "\t" << this->name << "\t" << price << "\t" << quantity <<"\n";
	}
	int getId() {
		return this->id;
	}
	int getQuantity() {
		return this->quantity;
	}
	int getPrice() {
		return this->price;
	}
	string getName() {
		return this->name;
	}
	void updatePrice(double price) {
		this->price = price;
	}
	void updateQuantity(int quantity) {
		this->quantity = quantity;
	}
 };
 
 
 
class ProductDB{
//DbEnv *env; 
Db *db;
string dbn;

public:

	ProductDB(){
		/*
		env = new DbEnv(0); //db evironment
    		env->set_cachesize(0, 64 * 1024, 0); 
    		env->open("./database", DB_CREATE | DB_INIT_MPOOL, 0); //open environmet
    		*/
		db = new Db(0,0); //create database
		db->open(nullptr, "database/product.db", nullptr, DB_BTREE, DB_CREATE , 0);  //open database
	}
	
	void setProduct(Product pr){
		//product.displayPro/duct();
		int pid = pr.getId();
		Dbt key((void*)&pid, sizeof(int));
        	Dbt value((void*)&pr, sizeof(Product));
        	if(db->put(nullptr, &key, &value, 0) != 0){
        		cerr << "Error adding data : " << endl;
        	}
	}
	void addNewProduct(int pid,string name,double price, int q) {
		Product p;
		p.addProduct(pid,name,price,q);
		Dbt key((void*)&pid, sizeof(int));
        	Dbt value((void*)&p, sizeof(Product));
        	if(db->put(nullptr, &key, &value, 0) != 0){
        		cerr << "Error adding data : " << endl;
        	}
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
	Product getProduct(int pid) {
		Dbt key((void*)&pid, sizeof(int));
		Dbt val;
		Product p(-1);
		
		if(db->get(nullptr, &key, &val, 0) == 0){
        		Product *pr = (Product*)(val.get_data());
			//pr->displayProduct();
			return *pr;
			
		}
		else{
			cerr<<"Product not found "<<endl;
		}
		
		return p;
	}
	/// get data from database;
	void getProducts(){
		
		
		Db my_db(0,0);
		//my_db.open(nullptr, "database/product.db", nullptr, DB_BTREE, DB_RDONLY, 0);
		//if(s!=0) cerr<<"Err:";
		Dbc *cursorp;
		try{
			db->cursor(NULL,&cursorp,0);
			Dbt key;
			Dbt val;
			int ret;
		
			while((ret = cursorp->get(&key,&val,DB_NEXT)) == 0) {
				Product *p = (Product*)(val.get_data());
				p->displayProduct();
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
	~ProductDB(){
		//db->close(0);
		//env->close(0);
	}
	
	
};


 
