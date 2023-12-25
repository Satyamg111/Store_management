#include <iostream> 
#include <ctime>
#include <string>
#include "Product.cpp"
#include "Customer.cpp"
#include "Cart.cpp"

using namespace std;

/* Grocery Store Management */
class GSM{
	string name;
	string location;
	public:
	GSM() {
		name = "Grocery Store";
		location = "Warangal";
	}
};
/**/
class Store : public GSM {
	protected:
	ProductDB products; // array of products
	//CustomerDB customers; // array of customers
	
	public:
	Store() {		
			/* Available Products Detail */
			
			Product p;
			p.addProduct(1,"Bread",25,10);
			products.setProduct(p);
			p.addProduct(2,"Egg",15,100);
			products.setProduct(p);
			p.addProduct(3,"Soap",30,100);
			products.setProduct(p);
			p.addProduct(4,"Shampoo",50,100);
			products.setProduct(p);
			p.addProduct(5,"Salt",25,50);
			products.setProduct(p);
			p.addProduct(6,"Shugar",40,100);
			products.setProduct(p);
			p.addProduct(7,"Butter",100,150);
			products.setProduct(p);
			p.addProduct(8,"Flour",25,500);
			products.setProduct(p);
			p.addProduct(9,"Oil",150,100);
			products.setProduct(p);
			p.addProduct(10,"Ketchup",40,120);
			products.setProduct(p);
		
		
		/* Customer Details*/
		/* customers[0].addCostomer(100,"Ankush");
		customers[1].addCostomer(101,"Ankit");
		customers[2].addCostomer(102,"Shubh");
		customers[3].addCostomer(103,"Shreya");
		customers[4].addCostomer(104,"Arpita"); */
		
	}	
	/*~Store() {
		delete(customers);
		delete(products);
	}*/
};

/* Admin class of System*/
class Admin : public Store {
	string id,password;
	string name;
	public :
		Admin() {
			this->id = "admin";
			this->password = "admin";
			this->name = "Satyam";
		}
		void admin() {
			int choice;
			cout<<"1.List Products\t2.Add Products\t3.Remove Products\t4.Update Product\t0.Exit\n";
			while(true) {
				cout<<"Enter your choice : ";
				cin>>choice;
				switch(choice) {
					
					case 1:{
						listProducts();
						break;
					}
					case 2:{
						addProduct();
						break;
					}
					case 3:{
						int pid;
						cout<<"Enter product id : ";
						cin>>pid;
						removeProduct(pid);
						break;
					}
					case 4:{
						updateProduct();
						break;
					}
					case 0:{
						return;
					}
					default :{
						cout<<"Enter correct choice\n";
						break;
					}
				}
			}
		}
		bool isValid() {
			string aId,aPass;
			cout<<"Enter admin id and password\n";
			cin>>aId>>aPass;
			if(id == aId && password == aPass) return true;
			return false;
		}
		/* Show all available Products */
		void listProducts() {
			cout<<"----- Available Products -----\n";
			cout<< "Id\tName\tPrice\tQuantity\n";
			products.getProducts();
		}
		/* Add new Product */
		void addProduct() {
			int pid,q;
			string pname;
			double p;
			cout<<"Enter product id : ";
			cin>>pid;
			cout<<"Enter Product name : ";
			cin>>pname;
			cout<<"Enter Product price : ";
			cin>>p;
			cout<<"Enter Product quantity : ";
			cin>>q;
			//Product product;
			//product.addProduct(pid,pname,p,q);
			//products.setProduct(product);
			products.addNewProduct(pid,pname,p,q);
			
			cout<<"Add successfully\n";
		}
		
		/* Remove Product*/
		void removeProduct(int pid) {
			products.removeProduct(pid);
		}
		
		/* Update product details */
		void updateProduct() {
			cout<<"1.Update Price\t2.Update Quantity\t3.Exit\n";
			int choice;
			while(true) {
				cout<<"Enter your choice : ";
				cin>>choice;
				
				switch(choice) {
					case 1: {
						int pid;
						double p;
						cout<<"Enter product id and price :\n";
						cin>>pid>>p;
						updatePrice(pid,p);
						break;
					}
					case 2: {
						int pid,q;
						cout<<"Enter product id and quantity :\n";
						cin>>pid>>q;
						updateQuantity(pid,q);
						break;
					}
					case 3: {
						return;
					}
					default :{
						cout<<"Enter correct choice\n";
						break;
					}
				}
			}
		}
		/* Update price of product*/
		void updatePrice(int pid,double price) {
			Product product = products.getProduct(pid); 
			if(product.getId() > 0) {
				product.updatePrice(price);
				products.setProduct(product);
				cout<<"Price update successfully\n";
			}
		}
		/* Update quantity of product*/
		void updateQuantity(int pid,int q) {
			Product product = products.getProduct(pid); 
			if(product.getId() > 0) {
				product.updateQuantity(q);
				products.setProduct(product);
				cout<<"Quantity update successfully\n";
			}
		}
};

/* Buyer class side*/
class Buyer : public Store {
	int id;
	string name;
	CartDB cart;
	double total;
	public :
		
		Buyer() {
			id = 100;
			name = "Ankush";
			total = 0;
		}
		/*--------------------------------------------*/
		void buyer() {
			int choice;
			cout<<"1.List Products\t2.Add Product to cart\t3.Exit\n";
			while(true) {
				cout<<"Enter your choice : ";
				cin>>choice;
				switch(choice) {
					case 1:{
						listProducts();
						break;
					}
					case 2:{
						buyProducts();
						break;
					}
					case 3:{
						return;
						break;
					}
					
					default :{
						cout<<"Enter correct choice\n";
						break;
					}
				}
			}
		}
		/*--------------------------------------------*/
		void listProducts() {
			cout<<"----- Available Products -----\n";
			cout<< "Id\tName\tPrice\tQuantity\n";
			products.getProducts();
			
		}
		/*--------------------------------------------*/
		void buyProducts(){
			int pid,q;
			int choice;
			cout<<"1. Add products\t2.Remove Products from cart\t3.Display Cart\t4. Checkout\n";
			while(true) {
				cout << "Enter your choice : ";
				cin>>choice;
				switch(choice) {
					case 1 : {
						cout << "Enter product id : ";
						cin>>pid;
						cout<<"Enter quantity : ";
						cin>>q;
						addToCart(pid,q);
						break;
					}
					case 2: {
						int pid;
						cout<<"Enter product id : ";
						cin>>pid;
						removeFromCart(pid);
						break;
					}
					case 3: {
						displayCart();
						break;
					}
					case 4: {
						checkout();
						exit(0);
					}
					default: {
						cout<<"Enter correct choice\n";
						break;
					}
				}
				
			}
			
		} 
		/*--------------------------------------------*/
		void addToCart(int pid,int q) {
			Product product = products.getProduct(pid);
			if(product.getId() > 0) {
				if(product.getQuantity() >= q) {
					Cart c(pid,product.getName(),product.getPrice(),q);
					cart.setProduct(c);
				}
				else {
					cout<<"## Insufficient Quantity ##\n";
				}
			}
		}
		/*display products in cart*/
		void displayCart() {
			cout<<
			"-----------------------------------------\n"<<
			"|\t\t Grocery Store \t\t|\n"<<
			"-----------------------------------------\n"<<
			"| \t\t\t Cart\t\t|\n"<<
			"-----------------------------------------\n"<<
			"|    "<<id<<"\t\t\t"<<name<<"  |\n"<<
			"-----------------------------------------\n"<<
			"| pid\tpname\tprice\tquant\ttotal   |\n"<<
			"-----------------------------------------\n";
			cart.displayCart();
			cout<<"-----------------------------------------\n";
			cout<<"| Total :\t\t\t"<<cart.getTotal()<<"\t|\n";
			cout<<"-----------------------------------------\n";
		}
		
		/*--------------------------------------------*/
		void removeFromCart(int pid) {
			cart.removeProduct(pid);
		}
		
		/*--------------------------------------------*/
		void checkout() {
			generateBill();
		}
		
		/*--------------------------------------------*/
		void generateBill(){
			time_t now = time(0);
			tm *ltm = localtime(&now);
			int year = 1900 + ltm->tm_year;
			int mon = 1 + ltm->tm_mon;
			int mday = ltm->tm_mday;
			int hour = ltm->tm_hour;
			int min = ltm->tm_min;
			int sec = ltm->tm_sec;
			
			string date = to_string(mday) + "."+ to_string(mon) + "." + to_string(year) ; 
			string time = to_string(hour) + ":"+ to_string(min) + ":" + to_string(sec) ; 
			
			cout<<
			"-----------------------------------------\n"<<
			"|\t\tGrocery Store \t\t|\n"<<
			"-----------------------------------------\n"<<
			"| "<<date<<"\t\t\t"<<time<<"|\n"<<
			"-----------------------------------------\n"<<
			"|    "<<id<<"\t\t\t"<<name<<"  |\n"<<
			"-----------------------------------------\n"<<
			"| pid\tpname\tprice\tquant\ttotal   |\n"<<
			"-----------------------------------------\n";
			cart.displayCart();
			cout<<"-----------------------------------------\n";
			cout<<"| Total :\t\t\t"<<cart.getTotal()<<"\t|\n";
			cout<<"-----------------------------------------\n";
		}
};

class Main : public Admin, public Buyer {
	public:
		void menu() {
			int choice;
			cout<< "1.Login as Admin\n2.Login as Buyer\n3.Exit\n";
			while(true) {
				cout<<"Enter choice : ";
				cin>>choice;
				switch(choice) {
					case 1: {
						if(isValid()){
							cout<<"-- Login Successfully --\n";
							admin();
						}
						else cout<<"Incorrect id or Password\n";
						break;
					}
					case 2:{
						buyer();
						break;
					}
					case 3:{
						exit(0);
						break;
					}
					default:{
						cout<<"Enter correct choice\n";
						break;
					}
				}
			}
		}
};

void start() {
	cout<<"\t   Grocery Store\n";
	cout<<"-----------------------------------\n\n";
	Main main;
	main.menu();
}
int main() {
	start();
	return 0;
}
