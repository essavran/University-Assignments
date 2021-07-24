/**
*	The Class Customer
*	This is a class that shows what actions customer
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public class Customer extends AbstractUser{
	/**address of the customer*/
	private String address;
	/**phonenumber of the customer*/
	private String phoneNumber;
	/**customer number of the customer*/
	private String customerNumber;
	/**branch where the customer subcribed*/
	private Branch atBranch;
	/**orders of the customer*/
	private HybridList<Order> orders;
/**
*	The subconstructor class
*	@param name user's name
*	@param surname user's surname
*	@param email user's email
*	@param password user's password
*	@param company the company
*/	
	public Customer(String name, String surname, String email, String password, Branch atBranch, Company company){
		super(name, surname, email, password, company);
		setBranch(atBranch);
		orders = new HybridList<Order>();
		company.setTotalCustomer( company.getTotalCustomer()+1 );
		setCustomerNumber( String.valueOf(company.getTotalCustomer()+1) );
	}
/**	
*	when shop online, keeps address and phone number
*	@param address of customer
*	@param phoneNumber number of the customer
*/
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


	public int getNumOfOrders(){
		return orders.size();
	}

	public void setOrders(HybridList orders){
		this.orders = orders;
	}

	public HybridList getOrders(){
		return orders;
	}

/**
*	shows all orders
*/
	public void showAllOrders(){
		System.out.println("***Previous Orders***");
		if( orders.size() == 0 ){
			System.out.println("There is no order yet.");

		} else{
			for(int i=0; i<orders.size(); i++){
				System.out.println(i+1 + ". Order:");
				System.out.println(orders.get(i));
			}		
		}

	}
/**
*	to search the product
*	@param product to search
*/
	public void searchProduct(Product product){
		//böyle bir product var mı
		KWLinkedList<Branch> branches = company.getBranches();
		boolean check = false;
		for(int i=0; i<company.getNumOfBranches(); i++){
			HybridList<Product> products = branches.get(i).getProducts();
			if( products.contains(product) ){
				System.out.println( product );
				check = true;
			} 
		}
		if( !check ){
			System.out.println("Şirkette böyle bir ürün yok.");
		}
	}
/**To print product detailed for customer*/
	@Override
	public void printProductsDetailed(){
		KWLinkedList<Branch> currentBranch = company.getBranches();
		System.out.printf("%25s", "Product's Type");
		System.out.printf("%25s", "Product's Model");		
		System.out.printf("%25s", "Product's Color");
		System.out.printf("%25s", "Branch");			
		System.out.printf("%25s", "Stock\n");		
		for(int i=0; i<company.getNumOfBranches(); i++){
			HybridList<Product> currentProduct = currentBranch.get(i).getProducts();
			for(int j=0; j<currentBranch.get(i).getNumOfProducts(); j++){
				System.out.printf("%25s", currentProduct.get(j).getType());
				System.out.printf("%25s", currentProduct.get(j).getModel());		
				System.out.printf("%25s", currentProduct.get(j).getColor());
				System.out.printf("%25s", currentBranch.get(i).getName());				
				System.out.printf("%25s", currentProduct.get(j).getStock());		
				System.out.println();
			}
		}
	}
/**To print customer's information*/
	@Override
	public String toString(){
		return "Customer's name: " + this.getName() + "\n" + 
							"Customer's surname: " + this.getSurname() + "\n" +
							"Customer's email: " + this.getEmail() + "\n" + 
							"Customer's customer number: " + this.getCustomerNumber() + "\n" + 
							"Customer's password: " + this.getPassword() + "\n" +
							"Customer's Branch: " + atBranch.getName() + "\n";
	}
/**
*	To compare customer objects
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
			Customer temp = (Customer) o;
			return this.getEmail().equals( temp.getEmail() );
		} catch( Exception e ){
			System.out.println("There is a problem");
			return false;
		}
	}
}