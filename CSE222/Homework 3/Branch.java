/**
*	The Class Branch
*	This is a class that contains data related with the branch
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public class Branch{
	/**Branch name*/
	private String branchName;
	/**products of the branch*/
	private HybridList<Product> products;
	/**employees of the branch*/
	private KWArrayList<BranchEmployee> employees;
/**
*	The constructor
*	@param branchName branch name
*/	
	public Branch(String branchName){
		products = new HybridList<Product>();
		employees = new KWArrayList<BranchEmployee>();
		setName( branchName );
	}

	public void setName(String branchName){
		this.branchName = branchName;
	}

	public String getName(){
		return this.branchName;
	}
	//*PRODUCTS********************************************************************************************
	public HybridList getProducts(){
		return products;
	}

	public void setProducts(HybridList products){
		this.products = products;
	}
	
	public int getNumOfProducts(){
		return products.size();
	}

	//**EMPLOYEEE*******************************************************************************************
	public KWArrayList getEmployees(){
		return employees;
	}

	public void setEmployees(KWArrayList employees){
		this.employees = employees;
	}
	
	public int getNumOfEmployees(){
		return employees.size();
	}

/**
*	shows all employees of the the branch
*/	
	public void showAllEmployees(){
		System.out.println("-> " + this.branchName + "'s Employee List: ");
		for(int i=0; i<employees.size(); i++){
			System.out.println(i+1 + ". Employee");
			System.out.println(employees.get(i));
		}
	}
/**To print branch's information*/
	@Override
	public String toString(){
		return "Branch's name: " + this.branchName;
	}
/**
*	To compare branch objects
*	@param o object that will be compared
*	@return true if they are same, otherwise false
*/
	@Override
	public boolean equals(Object o){
		if( o == this )
			return true;
		if( o == null )
			return false;
		if( o.getClass() != getClass() )
			return false;
		try{
			Branch temp = (Branch) o;
			return this.getName().equals( temp.getName() );
		} catch( Exception e ){
			System.out.println("There is a problem");
			return false;
		}
	}
}