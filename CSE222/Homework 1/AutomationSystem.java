/**
*	The Class AutomationSystem
*	This is a class that contains testing
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
	public class AutomationSystem{
	public static void main( String args[] ){
		testing();
	}

	public static void testing(){
		System.out.println("\n--------------------TESTING--------------------\n\n");
		Company company = new Company();
		//default admin is created
		Administrator defaultAdmin = new Administrator(company);
		Administrator admin2 = new Administrator("Ian", "McKellen", "ian@gmail.com", "1122", company);
		Administrator admin3 = new Administrator("Minnos", "Savran", "minnossavran@gmail.com", "1234", company);
		Branch branch1 = new Branch("Lothlorien");
		Branch branch2 = new Branch("Tirion");
		Branch branch3 = new Branch("Doriath");
		Branch branch4 = new Branch("Nenya");
		Branch branch5 = new Branch("Narya");
		BranchEmployee employee1 = new BranchEmployee("Viggo", "Mortensen", "viggo@gmail.com", "7777", company, branch4);
		BranchEmployee employee2 = new BranchEmployee("Sean", "Bean", "sean@gmail.com", "gondor123", company, branch4);
		BranchEmployee employee3 = new BranchEmployee("Andy", "Serkis", "andy@gmail.com", "1b23", company, branch4);
		Product product1 = new Product("Chair", "X", "Black", "100", branch4);
		Product product2 = new Product("Chair", "X", "White", "5", branch4);
		Product product3 = new Product("Chair", "Y", "Black", "1", branch4);
		Product product4 = new Product("Office Cabine", "M", "Brown", "10", branch4);
		Product product5 = new Product("Office Cabine", "M", "White", "30", branch4);
		Customer customer1 = new Customer("Sean", "Astin", "seanastin@gmail.com", "sean123", branch4, company);
		Customer customer2 = new Customer("Liv", "Tyler", "livtyler@gmail.com", "liv123", branch4, company);
		Customer customer3 = new Customer("Cate", "Blanchett", "cate@gmail.com", "cate123", branch4, company);
		Customer customer4 = new Customer("Mirsanda", "Otto", "otto@gmail.com", "otto", branch4, company);
		Customer customer5 = new Customer("Mirsanda", "Otto", "otto@gmail.com", "otto", branch4, company);

		Order order1 = new Order(customer2, branch4, product5, 2, false);
		Order order2 = new Order(customer2, branch4, product2, 1, false);

		//*********************************************************************************************
		System.out.println("\n*** Testing for Administrator ***\n");
		//add admins
		System.out.println("\n--> Before adding admin <--\n");
		company.showAllAdmins();
		System.out.println("\n--> After adding new admins <--\n");
		defaultAdmin.addAdmin(admin2);
		defaultAdmin.addAdmin(admin3);
		company.showAllAdmins();
		//remove admins
		System.out.println("\n--> Before removing admin <--\n");
		company.showAllAdmins();
		System.out.println("\n--> After removing admin <--\n");
		defaultAdmin.removeAdmin(admin2);
		company.showAllAdmins();
		//add branches
		System.out.println("\n--> Adding Branch Lothlorien, Branch Tirion, Branch Doriath, Branch Nenya, and Branch Narya <--\n");
		defaultAdmin.addBranch(branch1);
		defaultAdmin.addBranch(branch2);
		defaultAdmin.addBranch(branch3);
		defaultAdmin.addBranch(branch4);
		defaultAdmin.addBranch(branch5);
		company.showAllBranches();
		//trying add already exist branches
		System.out.println("\n--> Adding Branch Lothlorien(branch1) <--\n");
		defaultAdmin.addBranch(branch1);
		//remove branches
		System.out.println("\n--> Remove Branch Lothlorien <--\n");
		defaultAdmin.removeBranch(branch1);
		company.showAllBranches();
		System.out.println("\n--> Remove Branch Narya <--\n");
		defaultAdmin.removeBranch(branch5);
		company.showAllBranches();		
		System.out.println("\n--> Remove Branch Doriath <--\n");
		defaultAdmin.removeBranch(branch3);
		company.showAllBranches();
		System.out.println("\n--> Removing Branch Lothlorien(branch1) <--\n");
		defaultAdmin.removeBranch(branch1);
		//add employees
		System.out.println("\n--> Adding Employees to Branch Nenya <--\n");
		defaultAdmin.addEmployee(branch4, employee1);
		defaultAdmin.addEmployee(branch4, employee2);
		defaultAdmin.addEmployee(branch4, employee3);
		branch4.showAllEmployees();
		//trying add already exist employee
		System.out.println("\n--> Adding Viggo Mortensen(employee1) to Branch Nenya <--\n");
		defaultAdmin.addEmployee(branch4, employee1);
		//remove employees
		System.out.println("\n--> Removing Employees from Branch Nenya <--\n");
		defaultAdmin.removeEmployee(branch4, employee1);
		branch4.showAllEmployees();
		System.out.println("\n--> Removing Viggo Mortensen(employee1) to Branch Nenya <--\n");
		defaultAdmin.removeEmployee(branch4, employee1);
		//show supply
		System.out.println("\n-->Shows any products that need to be supplied <--\n");
		employee2.addProduct(product1);
		employee2.addProduct(product2);
		employee2.addProduct(product3);
		defaultAdmin.printProductsDetailed();
		//**************************************************************************************************************************
		System.out.println("\n*** Testing for Branch Employee ***\n");
		//add product
		System.out.println("\n--> Before Adding Products to Branch Nenya <--\n");
		employee2.printProductsDetailed();
		System.out.println("\n--> After Adding Products and Shows Stock Information to Branch Nenya <--\n");
		employee2.addProduct(product4);
		employee2.addProduct(product5);
		employee2.printProductsDetailed();
		//remove product
		System.out.println("\n--> After Remove Product and Shows Stock Information to Branch Nenya <--\n");
		employee2.removeProduct(product1);
		employee2.printProductsDetailed();
		System.out.println("\n--> Inform the Admin that the product should be purchased <--\n");
		employee2.adminInformed();
		//add customer
		System.out.println("\n--> Adding Customers to Branch Nenya <--\n");
		employee2.addCustomer(customer1);
		employee2.addCustomer(customer2);
		employee2.addCustomer(customer3);
		employee2.addCustomer(customer4);
		company.showAllCustomers();
		System.out.println("\n--> Adding Already Exists Customers to Branch Nenya <--\n");
		employee2.addCustomer(customer5);
		//remove customer
		System.out.println("\n--> Removing Customers from Branch Nenya <--\n");
		employee2.removeCustomer(customer1);
		employee2.removeCustomer(customer3);
		company.showAllCustomers();
		System.out.println("\n--> Adding Does not Exist Customers to Branch Nenya <--\n");
		employee2.removeCustomer(customer3);
		//customer's previous orders
		System.out.println("\n--> Shows previous orders of Customer2(Customer number: "+ customer2.getCustomerNumber() + ") <--\n");
		employee2.customersPreviousOrders( customer2.getCustomerNumber() );
		System.out.println("\n--> Products at Nenya Before Make Sales <--\n");
		employee2.printProductsDetailed();
		employee2.makeSales(order1, customer2);
		employee2.makeSales(order2, customer2);
		System.out.println("\n--> Products at Nenya After Make Sales <--\n");
		employee2.printProductsDetailed();
		System.out.println("\n--> Liv Tyler(Customer2) made purchases from Nenya <--\n");
		employee2.customersPreviousOrders( customer2.getCustomerNumber() );

		System.out.println("\n--> !!!! **There is no this customer. So employee will be add** !!!!\n--> Shows previous orders of Customer1(Customer number: "
			+ customer1.getCustomerNumber() + ") <--");
		System.out.println("\n--> Customer List at Nenya Before Make Sales <--\n");
		company.showAllCustomers();
		employee2.customersPreviousOrders( customer1.getCustomerNumber() );
		System.out.println("\n--> Products at Nenya Before Make Sales <--\n");
		employee2.printProductsDetailed();
		employee2.makeSales(order1, customer1);
		employee2.makeSales(order2, customer1);
		System.out.println("\n--> Products at Nenya After Make Sales <--\n");
		employee2.printProductsDetailed();
		System.out.println("\n--> Customer List at Nenya After Make Sales <--\n");
		company.showAllCustomers();
		//**************************************************************************************************************************
		System.out.println("\n*** Testing for Customers(Also Online Shop) ***\n");
		//online
		Branch onlineBranch = new Branch("Online");
		defaultAdmin.addBranch(onlineBranch);
		BranchEmployee onlineEmployee = new BranchEmployee("Online", "Online", "Online", "Online", company, onlineBranch);
		defaultAdmin.addEmployee(onlineBranch, onlineEmployee);
		System.out.println("\n--> Subscribe (onlineCustomer1 = Emine Sultan) <--\n");
		Customer onlineCustomer1 = new Customer("Emine", "Sultan", "ess@gmail.com", "2222", onlineBranch, company);
		onlineEmployee.online(onlineCustomer1);
		System.out.println("\n--> After adding onlineCustomer1, the Customer List <--\n");
		company.showAllCustomers();
		System.out.println("\n--> Shows List of Products(also which store a product is in) <--\n");
		onlineCustomer1.printProductsDetailed();
		System.out.println("\n--> Search product <--\n");
		onlineCustomer1.searchProduct(product2);
		System.out.println("\n--> Before Shop Online <--\n");
		onlineEmployee.customersPreviousOrders( onlineCustomer1.getCustomerNumber() );
		onlineEmployee.shopOnline(product2, onlineCustomer1, 2, "Istanbul", "5551234567");
		System.out.println("\n--> After Shop Online <--\n");
		onlineEmployee.customersPreviousOrders( onlineCustomer1.getCustomerNumber() );
		System.out.println("\n--> Previous Orders <--\n");
		onlineEmployee.customersPreviousOrders( onlineCustomer1.getCustomerNumber() );
		System.out.println("\n--> Shows List of Products(also which store a product is in) <--\n");
		onlineCustomer1.printProductsDetailed();
	}
} 