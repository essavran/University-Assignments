import java.util.Scanner;

public class Test{
	private static Administrator admin;
/*
20000001;123456
20000002;123456
20000003;123456
20000004;123456
20000005;123456
20000006;123456
20000007;123456
20000008;123456
20000009;123456
20000010;123456
*/
	public static void main( String args[] ){
		driver();		
		menu();	
	//	admin = new Administrator();
	//	admin.csvFile();
	}

	public static void menu(){
		admin = new Administrator();
		System.out.println("\n\n -> CSV file is reading and other files are creating/reloading ... ");	
		admin.csvFile();
		System.out.println(" -> Done ... Please make sure to add Customers to Users.txt !!! \n");	
		String id = "", password = "";
		boolean flag = false;
		System.out.println("\n--------------------WELCOME--------------------\n\n");
		do{
		    Scanner scanner = new Scanner(System.in);
			System.out.print("--> ID: ");
		    id = scanner.nextLine();
			System.out.print("--> Password: ");
		    password = scanner.nextLine();
		    String informationOfUser = admin.login(id, password);
		    if( informationOfUser.length() > 15 ){
				String[] information = informationOfUser.split(";"); 
		    	traderMenu(Long.parseLong(id), password, information[2]);
		    	flag = true;	
		    } else if( informationOfUser.length() == 15 ){
		    	customerMenu(Long.parseLong(id), password);
		    	flag = true;
		    } else{
		    	System.out.println("Cannot find the user. Please try again.");
		    }
		} while( !flag );
	}

	public static void traderMenu(long id, String password, String traderName){
		System.out.println("\n\nWelcome again, you are a trader.");
		String choice="";
		Trader trader = new Trader(id, password, traderName);	
		do{
			System.out.println("\n1) Add product\n2) Remove product\n3) Edit product");
			System.out.println("4) See the list of orders from customers\n5) Meet the orders\n6) Cancel the orders");
			System.out.println("0) Exit");
			System.out.print("-> Please select: ");
		    Scanner scanner = new Scanner(System.in);
		    choice = scanner.nextLine();
		    if( choice.equals("0") ){
				System.out.println("Goodbye!");
		    } else if( choice.equals("1") ){
				String idProduct = "";
				String name = "";
				String category = "";
				long price = -1;
				long discountedPrice = -1;
		    	String description = "";
				System.out.print("\n--> Product ID: ");
			    idProduct = scanner.nextLine();
				System.out.print("--> Product name: ");
				name = scanner.nextLine();
				System.out.print("--> Product category: ");
			    category = scanner.nextLine();
				System.out.print("--> Product price: ");
			    price = Long.parseLong(scanner.nextLine());
				System.out.print("--> Product discountedPrice: ");
			    discountedPrice = Long.parseLong(scanner.nextLine());
				System.out.print("--> Product description: ");
			    description = scanner.nextLine();
			    Product product = new Product(idProduct, name, category, price, discountedPrice, description, trader);
			    trader.addProduct(product);
		    } else if( choice.equals("2") ){			
				String idProduct = "";
				System.out.print("\n--> Product ID: ");
			    idProduct = scanner.nextLine();
			    trader.removeProduct(idProduct);
		    } else if( choice.equals("3") ){
				String idProduct = "";
				System.out.print("\n--> The Product ID you want to edit: ");
			    idProduct = scanner.nextLine();
			    if( trader.containsProduct(idProduct) ){
					String name = "";
					String category = "";
					long price = -1;
					long discountedPrice = -1;
			    	String description = "";
					System.out.println("\n--> Enter new informations of the product: ");
					System.out.print("----> Product name: ");
					name = scanner.nextLine();
					System.out.print("----> Product category: ");
				    category = scanner.nextLine();
					System.out.print("----> Product price: ");
				    price = Long.parseLong(scanner.nextLine());
					System.out.print("----> Product discountedPrice: ");
				    discountedPrice = Long.parseLong(scanner.nextLine());
					System.out.print("----> Product description: ");
				    description = scanner.nextLine();
				    Product product = new Product(idProduct, name, category, price, discountedPrice, description, trader);
				    trader.editProduct(product);
			    } else{
			    	System.out.println("There is no the product");
			    }
		    } else if( choice.equals("4") ){
		    	trader.seeListOfOrders();
		    } else if( choice.equals("5") ){
		    	String idOrder = "";
				System.out.print("\n--> The Order ID you want to meet: ");
			    idOrder = scanner.nextLine();
			    trader.meet(true, idOrder);
		    } else if( choice.equals("6") ){
		    	String idOrder = "";
				System.out.print("\n--> The Order ID you want to meet: ");
			    idOrder = scanner.nextLine();
			    trader.meet(false, idOrder);
		    } else{
				System.out.println("Invalid input.");
		    }
		} while( !choice.equals("0") );
	}

	public static void customerMenu(long id, String password){
		System.out.println("\n\nWelcome again, you are a customer.");
		String choice="";
		Customer customer = new Customer(id, password);	
		do{
			System.out.println("\n1) Search and query the products by their names.");
			System.out.println("2) Display all the products of a trader");
			System.out.println("0) Exit");
			System.out.print("-> Please select: ");
		    Scanner scanner = new Scanner(System.in);
		    choice = scanner.nextLine();
		    if( choice.equals("0") ){
				System.out.println("Goodbye!");
		    } else if( choice.equals("1") ){
		    	String target = "";
				System.out.print("\n--> Enter: ");
			    target = scanner.nextLine();
			    if(customer.search(target)){
					customerSearchMenu(customer);
			    } else{
					System.out.println("No products found!");			   
				}
		    } else if( choice.equals("2") ){
		    	String target = "";
				System.out.print("\n--> Enter trader name: ");
			    target = scanner.nextLine();
				if(!customer.displayTradersProduct(target)){
					System.out.println("No traders found!");	
				}
		    } else{
				System.out.println("Invalid input.");
		    }
		} while( !choice.equals("0") );
	}

	public static void customerSearchMenu(Customer customer){
		System.out.println("\n\n");
		String choice="";
		do{
			System.out.println("\n1) Sort the products in the search results by their prices");
			System.out.println("2) Sort the products in the search results by the percentage of the discount");
			System.out.println("3) Sort the products in the search results by the name");
			System.out.println("4) Filter by their category");
			System.out.println("5) Filter by the prices with respect to upper thresholds");
			System.out.println("6) Filter by the prices with respect to lower thresholds");
			System.out.println("7) Filter by the prices with respect to upper and lower thresholds");
			System.out.println("0) Exit");
			System.out.print("-> Please select: ");
		    Scanner scanner = new Scanner(System.in);
		    choice = scanner.nextLine();
		    if( choice.equals("0") ){
				System.out.println("Goodbye!");
		    } else if( choice.equals("1") ){
		    	customer.sortByPrice();
		    } else if( choice.equals("2") ){
				customer.sortByDiscount();
		    } else if( choice.equals("3") ){
				customer.sortByName();
		    } else if( choice.equals("4") ){
		    	String target = "";
				System.out.print("\n--> Enter: ");
			    target = scanner.nextLine();
				customer.filterCategory(target);
		    } else if( choice.equals("5") ){
		    	String target = "";
				System.out.print("\n--> Upper: ");
			    target = scanner.nextLine();
				customer.filterUpper(Long.parseLong(target));
		    } else if( choice.equals("6") ){
		    	String target = "";
				System.out.print("\n--> Lower: ");
			    target = scanner.nextLine();
				customer.filterLower(Long.parseLong(target));
		    } else if( choice.equals("7") ){
		    	String upper = "";
				System.out.print("\n--> Upper: ");
			    upper = scanner.nextLine();
		    	String lower = "";
				System.out.print("\n--> Lower: ");
			    lower = scanner.nextLine();
				customer.filterUpperLower(Long.parseLong(upper), Long.parseLong(lower));
		    } else{
				System.out.println("Invalid input.");
		    }
		} while( !choice.equals("0") );
	}

	public static void driver(){
		System.out.println("\n--------------------Driver Function--------------------\n\n");
		admin = new Administrator();
		System.out.println(" -> Driver starts with files that are ready in the file ... ");	

		Trader trader1 = new Trader(10000001, "123456", "Alisha");
		Product product1 = new Product("ABCDEG", "New Toy", "Boy", 123, 12, "description", trader1);
		Product product2 = new Product("ABCDEG", "New Toy", "Girls", 1234, 12, "description", trader1);
		Customer customer1 = new Customer(200000001,"123456");

		System.out.println("\n\n *** Test for the trader *** ");
		System.out.println("----------------------------------------");
		System.out.println(" -> Add product ... " + trader1.addProduct(product1));
		System.out.println("----------------------------------------");
		System.out.println(" -> Remove product ... " + trader1.removeProduct("SRTEH2FF9KEDEFGF"));
		System.out.println("----------------------------------------");
		System.out.println(" -> Edit product ... " + trader1.editProduct(product2));	
		System.out.println("----------------------------------------");
		System.out.println(" -> See orders ... ");	
		trader1.seeListOfOrders();
		System.out.println("----------------------------------------");
		System.out.println(" -> Meet order ... " + trader1.meet(true, "EEE"));
		System.out.println("----------------------------------------");
		System.out.println(" -> Cancel order ... " + trader1.meet(false, "BBB"));
		System.out.println("----------------------------------------");
		System.out.println(" -> See orders again ... ");	
		trader1.seeListOfOrders();

		System.out.println("\n\n\n *** Test for the customer(Make sure the information of the customer is in Users.txt) *** ");
		System.out.println("----------------------------------------");
		System.out.println(" -> Search (UCB)... " + customer1.search("UCB"));
		System.out.println("----------------------------------------");
		System.out.println(" ->  Display all the products of a trader ... " + customer1.displayTradersProduct("Alisha"));
		System.out.println("----------------------------------------");
		System.out.println(" -> Sort by piece ... ");
		customer1.sortByPrice();
		System.out.println("----------------------------------------");
		System.out.println(" -> Sort by the percentage of the discount ... ");
		customer1.sortByDiscount();
		System.out.println("----------------------------------------");		
		System.out.println(" -> Sort by name ... ");
		customer1.sortByName();
		System.out.println("----------------------------------------");
		System.out.println(" -> Filter category ... ");
		customer1.filterCategory("Baby Boys");
		System.out.println("----------------------------------------");		
		System.out.println(" -> Filter upper ... ");
		customer1.filterUpper(700);
		System.out.println("----------------------------------------");
		System.out.println(" -> Filter lower ... ");
		customer1.filterLower(600);
		System.out.println("----------------------------------------");		
		System.out.println(" -> Filter upper and lower ... ");
		customer1.filterUpperLower(600, 500);
		System.out.println("----------------------------------------");
	}
}