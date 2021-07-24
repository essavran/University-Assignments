/**
*	The Class Customer
*	This is a class that shows what actions customer
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public class Customer extends AbstractUser{
	private String address;
	private String phoneNumber;
	private String customerNumber;
	private Branch atBranch;//setter getter
	private Order[] orders;
	private int numOfOrders = 0;//settergetter
	private int capacityOfOrders = 10;//settergetter
/**
*	The subconstructor class
*	@param name user's name
*	@param surname user's surname
*	@param email user's email
*	@param password user's password
*	@param Company the company
*/	
	public Customer(String name, String surname, String email, String password, Branch atBranch, Company company){
		super(name, surname, email, password, company);
		setBranch(atBranch);
		orders = new Order[ capacityOfOrders ];
		company.setTotalCustomer( company.getTotalCustomer()+1 );
		setCustomerNumber( String.valueOf(company.getTotalCustomer()+1+company.getCapacityOfCustomers()) );
	}

	public void shopOnline(String address, String phoneNumber){
		setAddress(address);
		setPhoneNumber(phoneNumber);
	}

	public void setBranch(Branch atBranch){
		this.atBranch = atBranch;
	}

	public Branch getBranch(){
		return atBranch;
	}

	public void setAddress(String address){
		this.address = address;
	}

	public String getAddress(){
		return address;
	}
	
	public void setPhoneNumber(String phoneNumber){
		this.phoneNumber = phoneNumber;
	}

	public String getPhoneNumber(){
		return phoneNumber;
	}	

	public void setCustomerNumber(String customerNumber){
		this.customerNumber = customerNumber;
	}

	public String getCustomerNumber(){
		return customerNumber;
	}

	public void setNumOfOrders(int numOfOrders){
		this.numOfOrders = numOfOrders;
	}

	public int getNumOfOrders(){
		return numOfOrders;
	}

	public void setCapacityOfOrders(int capacityOfOrders){
		this.capacityOfOrders = capacityOfOrders;
	}

	public int getCapacityOfOrders(){
		return capacityOfOrders;
	}

	public void setOrders(Order[] orders){
		this.orders = orders;
	}

	public Order[] getOrders(){
		return orders;
	}

/**
*	check that the customers is same
*	@param newCustomer to check
*	@return true or false
*/
	protected boolean isSame(Customer newCustomer){
		if( this.getEmail().equals( newCustomer.getEmail() ) ) //not sure
			return true;
		return false;
	}
/**
*	shows all orders
*/
	public void showAllOrders(){
		System.out.println("***Previous Orders***");
		if( numOfOrders == 0 ){
			System.out.println("There is no order yet.");

		} else{
			for(int i=0; i<numOfOrders; i++){
				System.out.println(i+1 + ". Order:");
				System.out.println(orders[i]);
			}		
		}

	}
/**
*	to search the product
*	@param product to search
*/
	public void searchProduct(Product product){
		//böyle bir product var mı
		Branch[] branches = company.getBranches();
		boolean check = false;
		for(int i=0; i<company.getNumOfBranches(); i++){
			if( containsProduct(branches[i], product) ){
				System.out.println( product );
				check = true;
			} 
		}
		if( !check ){
			System.out.println("Şirkette böyle bir ürün yok.");
		}
	}

	@Override
	public void printProductsDetailed(){
		Branch[] currentBranch = company.getBranches();
		System.out.printf("%25s", "Product's Type");
		System.out.printf("%25s", "Product's Model");		
		System.out.printf("%25s", "Product's Color");
		System.out.printf("%25s", "Branch");			
		System.out.printf("%25s", "Stock\n");		
		for(int i=0; i<company.getNumOfBranches(); i++){
			Product[] currentProduct = currentBranch[i].getProducts();
			for(int j=0; j<currentBranch[i].getNumOfProducts(); j++){
				System.out.printf("%25s", currentProduct[j].getType());
				System.out.printf("%25s", currentProduct[j].getModel());		
				System.out.printf("%25s", currentProduct[j].getColor());
				System.out.printf("%25s", currentBranch[i].getName());				
				System.out.printf("%25s", currentProduct[j].getStock());		
				System.out.println();
			}
		}
	}

	@Override
	public void userProfile(){
		System.out.println( "Customer's name: " + this.getName() + "\n" + 
							"Customer's surname: " + this.getSurname() + "\n" +
							"Customer's email: " + this.getEmail() + "\n" + 
							"Customer's customer number: " + this.getCustomerNumber() + "\n" + 
							"Customer's password: " + this.getPassword() + "\n" +
							"Customer's Branch: " + atBranch.getName());
	}

	@Override
	public String toString(){
		return "Customer: " + this.getName() + " " + this.getSurname() + " " + this.getPassword() + "\n";
	}
}