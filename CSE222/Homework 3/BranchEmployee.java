/**
*	The Class branch employee
*	This is a class that shows what actions branch employee
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public class BranchEmployee extends AbstractUser{
	private Branch workBranch;
/**
*	The subconstructor class
*	@param name user's name
*	@param surname user's surname
*	@param email user's email
*	@param password user's password
*	@param company the company
*/	
	public BranchEmployee(String name, String surname, String email, String password, Company company, Branch workBranch){
		super(name, surname, email, password, company);
		this.setWorkBranch( workBranch );
	}

	public void setWorkBranch(Branch workBranch){
		this.workBranch = workBranch;
	}

	public Branch getWorkBranch(){
		return workBranch;
	}
/**
*	add product to company
*	@param newProduct product to add
*/
	public void addProduct(Product newProduct){
		//zaten eklenmiş bir  eklemeye çalışbilir
		HybridList<Product> currentProducts = workBranch.getProducts();
		if( currentProducts.contains(newProduct) ){
			System.out.println("boyle bir product zaten var: "+newProduct);
		} else{
			currentProducts.add(newProduct);
		}

	}
/**
*	remove product to company
*	@param product to remove
*/	
	public void removeProduct(Product product){
		HybridList<Product> products = workBranch.getProducts();
		if( products.contains(product) ){
			products.remove(product);
		} else{
			System.out.println("böyle bir product yok, silemem: "+product);

		}
	}
/**
*	add customer to branch
*	@param newCustomer to add
*/	
	public void addCustomer(Customer newCustomer){
		KWArrayList<Customer> currentCustomers = company.getCustomers();
		if( currentCustomers.contains(newCustomer) ){
			System.out.println("böyle bir customer zaten var");
		} else{
			currentCustomers.add(newCustomer);
		}
	}

/**
*	remove customer from company
*	@param customer to remove
*/	
	public void removeCustomer(Customer customer){
		KWArrayList<Customer> currentCustomers = company.getCustomers();
		if( currentCustomers.contains(customer) ){
			currentCustomers.remove( customer );

		} else{
			System.out.println("Failed. The customer does not exist : " + customer);
		}
	}

/**
*	add order to customer with special customer numbers
*	@param order to add
*	@param customerNumber to find the customer
*/
	public void addOrder(Order order, String customerNumber){
		KWArrayList<Customer> currentCustomers = company.getCustomers();
		Customer cCustomer = null;//not sure
		for(int i=0; i<company.getNumOfCustomers(); i++){
			//	System.out.println(currentCustomers.get(i).getCustomerNumber());
			if( customerNumber.equals( currentCustomers.get(i).getCustomerNumber() ) )
				cCustomer = currentCustomers.get(i);
		}
		HybridList<Order> currentOrders = cCustomer.getOrders();
		currentOrders.add(order);
	}
/**
*	add customer for online shop
*	@param customer to add
*/
	public void online(Customer customer){
		KWArrayList<Customer> currentCustomers = company.getCustomers();
		if( currentCustomers.contains(customer) ){
			System.out.println("Failed. It's already registered.");
		} else{
			registration(customer);
		}
	}
/**
*	registration of customer
*	@param newCustomer to register
*/
	private void registration(Customer newCustomer){
		addCustomer(newCustomer);
		System.out.println("Signed up. Welcome to our company!");
	}

/**
*	shows customers's previous orders with special customer number
*	@param customerNumber to find the customer
*/
	public void customersPreviousOrders(String customerNumber){
		//find customer
		KWArrayList<Customer> allCustomers = company.getCustomers();
		boolean check = false;
		for(int i=0; i<company.getNumOfCustomers(); i++){
			if( allCustomers.get(i).getCustomerNumber().equals( customerNumber ) ){
				allCustomers.get(i).showAllOrders();
				check = true;
			}
		}
		if( !check )
			System.out.println("There is no customer with this customer number: "+customerNumber);

	}
/**
*	to informed the admin about the product's stock
*/
	public void adminInformed(){
		HybridList<Product> currentProduct = workBranch.getProducts();
		for(int j=0; j<workBranch.getNumOfProducts(); j++){
			if( currentProduct.get(j).getNeedSupply().equals("Need") ){
				System.out.println("Admin is informed. This product should be purchased " + currentProduct.get(j));
			}
		}
	}	
/**
*	employee makes sales
*	@param order to add order
*	@param customer who did order
*/
	public void makeSales(Order order, Customer customer){
		//bu customer var mı
		KWArrayList<Customer> currentCustomers = company.getCustomers();
		if( !currentCustomers.contains(customer) ){
			addCustomer(customer);
		}

		int stock = Integer.parseInt(order.getProduct().getStock()); 
		
		if( stock < order.getBuyNum() ){
			System.out.println("Failed. Not enough this product. This order cannot perform:\n" + order);
			adminInformed();
		} else{
			addOrder(order, customer.getCustomerNumber());

			Product rProduct = order.getProduct();

			for(int i=0; i<order.getBuyNum(); i++)
				decreaseProduct(rProduct);			
		}
	}
/**
*	to increase product's stock
*	@param rProduct to find product
*/
	public void increaseProduct(Product rProduct){
		int stock=Integer.parseInt(rProduct.getStock());  
		rProduct.setStock( String.valueOf(stock+1) );
	}
/**
*	to decrease product's stock
*	@param rProduct to find product
*/
	public void decreaseProduct(Product rProduct){
		int stock=Integer.parseInt(rProduct.getStock());  
		rProduct.setStock( String.valueOf(stock-1) );
	}
/**
*	to create the order, set address and phonenumber and make sales
*	@param product to sale
*	@param customer who did order
*	@param buyNum how many buy
*	@param address address
*	@param phoneNumber phoneNumber
*/
	public void shopOnline(Product product, Customer customer, int buyNum, String address, String phoneNumber){
		Order order = new Order(customer, workBranch, product, buyNum, true);
		customer.setAddress(address);
		customer.setPhoneNumber(phoneNumber);
		makeSales(order, customer);
	}
/**To print product detailed for branch employee*/
	@Override
	public void printProductsDetailed(){
		KWLinkedList<Branch> currentBranch = company.getBranches();
		System.out.printf("%-25s", "Product's Type");
		System.out.printf("%-25s", "Product's Model");		
		System.out.printf("%-25s", "Product's Color");		
		System.out.printf("%-25s", "Product's Stock");		
		System.out.printf("%-25s", "Product's Need Supply");		
		System.out.println();

		for(int i=0; i<company.getNumOfBranches(); i++){
			HybridList<Product> currentProduct = currentBranch.get(i).getProducts();
			for(int j=0; j<currentBranch.get(i).getNumOfProducts(); j++){
				System.out.printf("%-25s", currentProduct.get(j).getType());
				System.out.printf("%-25s", currentProduct.get(j).getModel());		
				System.out.printf("%-25s", currentProduct.get(j).getColor());		
				System.out.printf("%-25s", currentProduct.get(j).getStock());		
				System.out.printf("%-25s", currentProduct.get(j).getNeedSupply());
				System.out.println();
			}
		}
	}
/**To print branch employee's information*/
	@Override
	public String toString(){
		return "Branch Employee's name: " + this.getName() + "\n" + 
				"Branch Employee's surname: " + this.getSurname() + "\n" + 
				"Branch Employee's email: " + this.getEmail() + "\n" + 
				"Branch Employee's password: " + this.getPassword() + "\n";
	}
/**
*	To compare branch employee objects
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
			BranchEmployee temp = (BranchEmployee) o;
			return this.getEmail().equals( temp.getEmail() );
		} catch( Exception e ){
			System.out.println("There is some problems");
			return false;
		}
	}
}