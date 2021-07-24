/**
*	The Abstract Class AbstractUser
*	This is a class that shows what actions administrator, customer, and customer can do
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public abstract class AbstractUser implements User{
	protected Company company;// = new Company();
	private String name;
	private String surname;
	private String email;
	private String password;
/**
*	The base constructor class
*	@param name user's name
*	@param surname user's surname
*	@param email user's email
*	@param password user's password
*	@param Company the company
*/	
	public AbstractUser(String name, String surname, String email, String password, Company company){
		this.setName( name );
		this.setSurname( surname );
		this.setEmail( email );
		this.setPassword( password );
		this.setCompany( company );
	}
/**
*	get the Company
*	@return company
*/
	public Company getCompany(){
		return company;
	}
/**
*	Set the company
*	@param company
*/	
	public void setCompany(Company company){
		this.company = company;
	}

	public void setName(String name){
		this.name = name;
	}

	public String getName(){
		return name;
	}

	public void setSurname(String surname){
		this.surname = surname;
	}

	public String getSurname(){
		return surname;
	}

	public void setPassword(String password){
		this.password = password;
	}

	public String getPassword(){
		return password;
	}

	public void setEmail(String email){
		this.email = email;
	}

	public String getEmail(){
		return email;
	}
/**
*	Shows whether the company includes this branch
*	@param branch to find
*	@return true or false
*/
	protected boolean containsBranch(Branch branch){
		Branch[] branches = company.getBranches();
		for(int i=0; i<company.getNumOfBranches(); i++){
			if( branches[i].getName().equals( branch.getName() ) ) //böyle biri var
				return true;
		}

		return false;
	}
/**
*	Shows whether the company includes this admin
*	@param admin to find
*	@return true or false
*/
	protected boolean containsAdmin(Administrator admin){
		Administrator[] admins = company.getAdmins();
		for(int i=0; i<company.getNumOfAdmins(); i++){
			if( admins[i].getEmail().equals( admin.getEmail() ) ) //böyle biri var
				return true;
		}

		return false;
	}
/**
*	Shows whether the branch includes this employee
*	@param branch to find
*	@param employee to find
*	@return true or false
*/
	protected boolean containsEmployee(Branch branch, BranchEmployee employee){
		BranchEmployee[] employees = branch.getEmployees();
		for(int i=0; i<branch.getNumOfEmployees(); i++){
			if( employees[i].getEmail().equals( employee.getEmail() ) ) //böyle biri var
				return true;
		}
		return false;
	}
/**
*	Shows whether the company includes this customer
*	@param customer to find
*	@return true or false
*/
	protected boolean containsCustomer(Customer customer){
		Customer[] customers = company.getCustomers();
		for(int i=0; i<company.getNumOfCustomers(); i++){
			if( customers[i].isSame(customer) ) //böyle biri var
				return true;
		}
		return false;
	}
/**
*	Shows whether the branch includes this product
*	@param branch to find
*	@param product to find
*	@return true or false
*/
	protected boolean containsProduct(Branch branch, Product product){
		Product[] products = branch.getProducts();
		for(int i=0; i<branch.getNumOfProducts(); i++){
			if( products[i].isSame(product) ) //böyle biri var
				return true;
		}
		return false;
	}
/**
*	Shows whether the customer includes this order
*	@param customer to find
*	@param order to find
*	@return true or false
*/
	protected boolean containsOrder(Customer customer, Order order){
		Order[] orders = customer.getOrders();
		for(int i=0; i<customer.getNumOfOrders(); i++){
			if( orders[i].isSame(order) ) //böyle biri var
				return true;
		}
		return false;
	}
/**
*	Shows company's branches
*/
	public void showBranches(){
		for(int i=0; i<company.getNumOfBranches(); i++){
			System.out.println( company.getBranches()[i].getName() );
		}	
	}
}