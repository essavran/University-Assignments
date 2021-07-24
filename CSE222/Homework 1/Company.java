/**
*	The Class Company
*	This is a class that contains data related with the company
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public class Company{
	//
	private int capacityOfAdmins = 10;
	private int numOfAdmins = 0;	
	private Administrator[] admins;
	//
	private int capacityOfBranches = 10;
	private int numOfBranches = 0;
	private Branch[] branches;
	//
	private int capacityOfCustomers = 10;
	private int numOfCustomers = 0;
	private int totalCustomer = 0;
	private Customer[] customers;
/**
*	The constructor 
*/	
	public Company(){
		admins = new Administrator[ capacityOfAdmins ];
		branches = new Branch[ capacityOfBranches ];
		customers = new Customer[ capacityOfCustomers ];
	}
	//ADMIN
	public Administrator[] getAdmins(){
		return admins;
	}

	public void setAdmins(Administrator[] admins){
		this.admins = admins;
	}
	
	public int getCapacityOfAdmins(){
		return capacityOfAdmins;
	}

	public void setCapacityOfAdmins(int capacityOfAdmins){
		this.capacityOfAdmins = capacityOfAdmins;
	}

	public int getNumOfAdmins(){
		return numOfAdmins;
	}

	public void setNumOfAdmins(int numOfAdmins){
		this.numOfAdmins = numOfAdmins;
	}

	public int getTotalCustomer(){
		return totalCustomer;
	}

	public void setTotalCustomer(int totalCustomer){
		this.totalCustomer = totalCustomer;
	}
/**
*	shows all the admins of the company
*/	
	public void showAllAdmins(){
		System.out.println("-> Admin List:");
		for(int i=0; i<numOfAdmins; i++){
			if( i == 0 ){
				System.out.println("Default Admin(First Admin)");
			}else{
				System.out.println(i+1 + ". Admin");
			}
			admins[i].userProfile();
		}
	}
	//BRANCH
	public Branch[] getBranches(){
		return branches;
	}

	public void setBranches(Branch[] branches){
		this.branches = branches;
	}
	
	public int getCapacityOfBranches(){
		return capacityOfBranches;
	}

	public void setCapacityOfBranches(int capacityOfBranches){
		this.capacityOfBranches = capacityOfBranches;
	}

	public int getNumOfBranches(){
		return numOfBranches;
	}

	public void setNumOfBranches(int numOfBranches){
		this.numOfBranches = numOfBranches;
	}

	public void showAllBranches(){
		System.out.println("-> Branch List:");
		for(int i=0; i<numOfBranches; i++){
			System.out.println(i+1 + ". Branch");
			System.out.println(branches[i]);
		}
	}
	//CUSTOMER
	public Customer[] getCustomers(){
		return customers;
	}

	public void setCustomers(Customer[] customers){
		this.customers = customers;
	}
	
	public int getCapacityOfCustomers(){
		return capacityOfCustomers;
	}

	public void setCapacityOfCustomers(int capacityOfCustomers){
		this.capacityOfCustomers = capacityOfCustomers;
	}

	public int getNumOfCustomers(){
		return numOfCustomers;
	}

	public void setNumOfCustomers(int numOfCustomers){
		this.numOfCustomers = numOfCustomers;
	}
/**
*	shows all the customers of the company
*/	
	public void showAllCustomers(){
		System.out.println("-> Customer List:");
		for(int i=0; i<numOfCustomers; i++){
			System.out.println(i+1 + ". Customer");
			customers[i].userProfile();
		}
	}
}