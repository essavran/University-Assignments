/**
*	The Class Company
*	This is a class that contains data related with the company
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public class Company{
	/**To keep all the admins*/
	private KWArrayList<Administrator> admins;
	/**To keep all the branches*/
	private KWLinkedList<Branch> branches;
	/**To not lose number of customers*/
	private int totalCustomer = 0;
	/**To keep all the customers*/
	private KWArrayList<Customer> customers;
/**
*	The constructor 
*/	
	public Company(){
		admins = new KWArrayList<Administrator>();
		branches = new KWLinkedList<Branch>();
		customers = new KWArrayList<Customer>();
	}
	//ADMIN
/**
*	get the admins
*	@return admins
*/
	public KWArrayList getAdmins(){
		return admins;
	}
/**
*	set the admins
*	@param admins
*/
	public void setAdmins(KWArrayList admins){
		this.admins = admins;
	}
/**
*	get the number of admins
*	@return number of admins
*/
	public int getNumOfAdmins(){
		return admins.size();
	}
/**
*	shows all the admins of the company
*/	
	public void showAllAdmins(){
		System.out.println("-> Admin List:");
		for(int i=0; i<admins.size(); i++){
			if( i == 0 ){
				System.out.println("Default Admin(First Admin)");
			}else{
				System.out.println(i+1 + ". Admin");
			}
			System.out.println(admins.get(i));
		}
	}
	//BRANCH
/**
*	get the branches
*	@return branches
*/
	public KWLinkedList getBranches(){
		return branches;
	}
/**
*	set the branches
*	@param branches
*/
	public void setBranches(KWLinkedList branches){
		this.branches = branches;
	}
/**
*	get the number of branches
*	@return number of branches
*/	
	public int getNumOfBranches(){
		return branches.size();
	}
/**To print all the branches*/
	public void showAllBranches(){
		System.out.println("-> Branch List:");
		for(int i=0; i<branches.size(); i++){
			System.out.println(i+1 + ". Branch");
			System.out.println(branches.get(i));
		}
	}
	//CUSTOMER
/**
*	get the customers
*	@return customers
*/
	public KWArrayList getCustomers(){
		return customers;
	}
/**
*	set the customers
*	@param customers
*/
	public void setCustomers(KWArrayList customers){
		this.customers = customers;
	}
/**
*	get the number of customers
*	@return number of customers
*/
	public int getNumOfCustomers(){
		return customers.size();
	}
/**
*	get the total customer
*	@return total customer
*/
	public int getTotalCustomer(){
		return totalCustomer;
	}
/**
*	set the total customer
*	@param totalCustomer total customer
*/
	public void setTotalCustomer(int totalCustomer){
		this.totalCustomer = totalCustomer;
	}
/**
*	prints all the customers of the company
*/	
	public void showAllCustomers(){
		System.out.println("-> Customer List:");
		for(int i=0; i<customers.size(); i++){
			System.out.println(i+1 + ". Customer");
			System.out.println(customers.get(i));
		}
	}
}