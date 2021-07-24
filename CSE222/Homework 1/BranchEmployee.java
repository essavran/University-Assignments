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
*	@param Company the company
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
*	@param product to add
*/
	public void addProduct(Product newProduct){
		//zaten eklenmiş bir  eklemeye çalışbilir
		Product[] currentProducts = workBranch.getProducts();
		if( containsProduct(workBranch, newProduct) ){
			System.out.println("boyle bir product zaten var");
		} else{
			//make sure there is a room
			if( workBranch.getCapacityOfProducts() <= workBranch.getNumOfProducts() ){
				reallocateProducts();
			}
			currentProducts = workBranch.getProducts();
			currentProducts[ workBranch.getNumOfProducts() ] = newProduct;
			workBranch.setNumOfProducts( workBranch.getNumOfProducts()+1 );
		}

	}
/**
*	extends size of products array
*/	
	private void reallocateProducts(){
		Product[] products = workBranch.getProducts();
		workBranch.setCapacityOfProducts( workBranch.getCapacityOfProducts()*2 );
		Product[] temp = new Product[ workBranch.getCapacityOfProducts() ];
		for(int i=0; i<workBranch.getNumOfProducts(); i++){
			temp[i] = products[i];
		}
		workBranch.setProducts( temp );
	}
/**
*	remove product to company
*	@param product to remove
*/	
	public void removeProduct(Product product){
		if( containsProduct(workBranch, product) ){
			int index = 0;
			Product[] products = workBranch.getProducts();
			Product[] temp = new Product[ workBranch.getCapacityOfProducts() ];
			for(int i=0; i<workBranch.getNumOfProducts(); i++){
				if( products[i].isSame(product) ) //böyle biri var
					index++;
				temp[i] = products[index];
				index++;
			}
			workBranch.setProducts( temp );
			workBranch.setNumOfProducts( workBranch.getNumOfProducts()-1 );
		} else{
			System.out.println("böyle bir product yok, silemem : ");

		}
	}
/**
*	add customer to branch
*	@param newCustomer to add
*/	
	public void addCustomer(Customer newCustomer){
		//zaten eklenmiş bir admini eklemeye çalışbilir
		Customer[] currentCustomers = company.getCustomers();
		if( containsCustomer(newCustomer) ){
			System.out.println("böyle bir customer zaten var");
		} else{
			//make sure there is a room
			if( company.getCapacityOfCustomers() <= company.getNumOfCustomers() ){
				reallocateCustomers();
			}
			currentCustomers = company.getCustomers();
			currentCustomers[ company.getNumOfCustomers() ] = newCustomer;
			company.setNumOfCustomers( company.getNumOfCustomers()+1 );
		}

	}
/**
*	extends size of customers array
*/	
	private void reallocateCustomers(){
		Customer[] customers = company.getCustomers();
		company.setCapacityOfCustomers( company.getCapacityOfCustomers()*2 );
		Customer[] temp = new Customer[ company.getCapacityOfCustomers() ];
		for(int i=0; i<company.getNumOfCustomers(); i++){
			temp[i] = customers[i];
		}
		company.setCustomers( temp );
	}
/**
*	remove customer from company
*	@param customer to remove
*/	
	public void removeCustomer(Customer customer){
		if( containsCustomer(customer) ){
			int index = 0;
			Customer[] customers = company.getCustomers();
			Customer[] temp = new Customer[ company.getCapacityOfCustomers() ];
			for(int i=0; i<company.getNumOfCustomers(); i++){
				if( customers[i].isSame(customer) ) //böyle biri var
					index++;
				temp[i] = customers[index];
				index++;
			}
			company.setCustomers( temp );
			company.setNumOfCustomers( company.getNumOfCustomers()-1 );
		} else{
			System.out.println("böyle bir product yok, silemem");

		}
	}

/**
*	add order to customer with special customer numbers
*	@param order to add
*	@param customerNumber to find the customer
*/
	public void addOrder(Order order, String customerNumber){
		//zaten eklenmiş bir admini eklemeye çalışbilir
		Customer[] currentCustomers = company.getCustomers();
		Customer cCustomer = null;//not sure
		for(int i=0; i<company.getNumOfCustomers(); i++){
			if( customerNumber.equals( currentCustomers[i].getCustomerNumber() ) )
				cCustomer = currentCustomers[i];
		}

		Order[] currentOrders = cCustomer.getOrders();

		//make sure there is a room
		if( cCustomer.getCapacityOfOrders() <= cCustomer.getNumOfOrders() ){
			reallocateOrders(cCustomer);
		}
		currentOrders = cCustomer.getOrders();
		currentOrders[ cCustomer.getNumOfOrders() ] = order;
		cCustomer.setNumOfOrders( cCustomer.getNumOfOrders()+1 );
	}
/**
*	extends size of orders array
*/
	private void reallocateOrders(Customer cCustomer){
		Order[] orders = cCustomer.getOrders();
		cCustomer.setCapacityOfOrders( cCustomer.getCapacityOfOrders()*2 );
		Order[] temp = new Order[ cCustomer.getCapacityOfOrders() ];
		for(int i=0; i<cCustomer.getNumOfOrders(); i++){
			temp[i] = orders[i];
		}
		cCustomer.setOrders( temp );
	}
/**
*	add customer for online shop
*	@param customer to add
*/
	public void online(Customer customer){
		Customer[] currentCustomers = company.getCustomers();
		if( containsCustomer(customer) ){
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
		Customer[] allCustomers = company.getCustomers();
		boolean check = false;
		for(int i=0; i<company.getNumOfCustomers(); i++){
			if( allCustomers[i].getCustomerNumber().equals( customerNumber ) ){
				allCustomers[i].showAllOrders();
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
		Product[] currentProduct = workBranch.getProducts();
		for(int j=0; j<workBranch.getNumOfProducts(); j++){
			if( currentProduct[j].getNeedSupply().equals("Need") ){
				System.out.println("Admin is informed. This product should be purchased " + currentProduct[j]);
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
		Customer[] currentCustomers = company.getCustomers();
		if( !containsCustomer(customer) ){
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

	@Override
	public void printProductsDetailed(){
		Branch[] currentBranch = company.getBranches();
		System.out.printf("%-25s", "Product's Type");
		System.out.printf("%-25s", "Product's Model");		
		System.out.printf("%-25s", "Product's Color");		
		System.out.printf("%-25s", "Product's Stock");		
		System.out.printf("%-25s", "Product's Need Supply");		
		System.out.println();

		for(int i=0; i<company.getNumOfBranches(); i++){
			Product[] currentProduct = currentBranch[i].getProducts();
			for(int j=0; j<currentBranch[i].getNumOfProducts(); j++){
				System.out.printf("%-25s", currentProduct[j].getType());
				System.out.printf("%-25s", currentProduct[j].getModel());		
				System.out.printf("%-25s", currentProduct[j].getColor());		
				System.out.printf("%-25s", currentProduct[j].getStock());		
				System.out.printf("%-25s", currentProduct[j].getNeedSupply());
				System.out.println();
			}
		}
	}
	
	@Override
	public void userProfile(){
		System.out.println( "Branch Employee's name: " + this.getName() + "\n" + 
							"Branch Employee's surname: " + this.getSurname() + "\n" + 
							"Branch Employee's email: " + this.getEmail() + "\n" + 
							"Branch Employee's password: " + this.getPassword() );
	}

	@Override
	public String toString(){
		//this yazmam saçma mı oldu acaba :D
		return "BranchEmployee: " + this.getName() + " " + this.getSurname() + " " + this.getEmail() + " " + this.getPassword() + "\n";
	}
}