/**
*	The Class Branch
*	This is a class that contains data related with the branch
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public class Branch{
	private String branchName;

	private int capacityOfProducts = 10;
	private int numOfProducts = 0;
	private Product[] products;
	
	private int capacityOfEmployees = 10;
	private int numOfEmployees = 0;
	private BranchEmployee[] employees;
/**
*	The constructor
*	@param branchName branch name
*/	
	public Branch(String branchName){
		products = new Product[ capacityOfProducts ];
		employees = new BranchEmployee[ capacityOfEmployees ];
		setName( branchName );
	}

	public void setName(String branchName){
		this.branchName = branchName;
	}

	public String getName(){
		return this.branchName;
	}
	//*PRODUCTS********************************************************************************************
	public Product[] getProducts(){
		return products;
	}

	public void setProducts(Product[] products){
		this.products = products;
	}
	
	public int getCapacityOfProducts(){
		return capacityOfProducts;
	}

	public void setCapacityOfProducts(int capacityOfProducts){
		this.capacityOfProducts = capacityOfProducts;
	}

	public int getNumOfProducts(){
		return numOfProducts;
	}

	public void setNumOfProducts(int numOfProducts){
		this.numOfProducts = numOfProducts;
	}
	//**EMPLOYEEE*******************************************************************************************
	public BranchEmployee[] getEmployees(){
		return employees;
	}

	public void setEmployees(BranchEmployee[] employees){
		this.employees = employees;
	}
	
	public int getCapacityOfEmployees(){
		return capacityOfEmployees;
	}

	public void setCapacityOfEmployees(int capacityOfEmployees){
		this.capacityOfEmployees = capacityOfEmployees;
	}

	public int getNumOfEmployees(){
		return numOfEmployees;
	}

	public void setNumOfEmployees(int numOfEmployees){
		this.numOfEmployees = numOfEmployees;
	}
/**
*	shows all employees of the the branch
*/	
	public void showAllEmployees(){
		System.out.println("-> " + this.branchName + "'s Employee List: ");
		for(int i=0; i<numOfEmployees; i++){
			System.out.println(i+1 + ". Employee");
			employees[i].userProfile();
		}
	}
/**
*	check that the branches are same
*	@param branch to check
*	@return true or false
*/	
	public boolean isSame(Branch branch){
		if( this.getName().equals( branch.getName() ) )
			return true;
		return false;
	}

	@Override
	public String toString(){
		return "Branch's name: " + this.branchName;
	}
}