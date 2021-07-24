/**
*	The Class Administrator
*	This is a class that shows what actions administrator
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public class Administrator extends AbstractUser{
/**
*	The subconstructor to create default admin
*	@param company to add
*/
	public Administrator(Company company){
		super( "Default", "Admin", "default@gmail.com", "0000", company );
		this.addAdmin( this );
	}
/**
*	The subconstructor
*	@param name user's name
*	@param surname user's surname
*	@param email user's email
*	@param password user's password
*	@param company the company
*/		
	public Administrator(String name, String surname, String email, String password, Company company){
		super(name, surname, email, password, company);	
	}

/**
*	add admins to company
*	@param admin to add
*/
	public void addAdmin(Administrator admin){
		//zaten eklenmiş bir admini eklemeye çalışabilir
		KWArrayList<Administrator> admins = company.getAdmins();
		if( admins.contains(admin) ){
			System.out.println("The admin already exists: "+ admin);
		} else{
			admins.add(admin);
		}
	}
/**
*	removes admin from the company
*	@param admin to remove
*/	

	public void removeAdmin(Administrator admin){
		KWArrayList<Administrator> admins = company.getAdmins();
		if( admins.contains(admin) ){
			admins.remove(admin);
		} else{
			System.out.println("Failed. The admin does not exist : " + admin);
		}
	}

/**
*	add branch to company
*	@param branch to add
*/	
	public void addBranch(Branch branch){
		KWLinkedList<Branch> branches = company.getBranches();
		if( branches.contains(branch) ){
			System.out.println("The branch already exists: "+ branch);
		} else{
			branches.add(branch);
		}

	}

/**
*	remove branch from the company
*	@param branch to remove
*/	
	public void removeBranch(Branch branch){
		
		KWLinkedList<Branch> branches = company.getBranches();
		if( branches.contains(branch) ){
			branches.remove(branch);
		} else{
			System.out.println("Failed. The branch does not exists:  : "+ branch);
		}
	}
/**
*	add employee to branch
*	@param findBranch to add
*	@param employee to add
*/
	public void addEmployee(Branch findBranch, BranchEmployee employee){		
		KWLinkedList<Branch> branches = company.getBranches();
		if( branches.contains(findBranch) ){
			KWArrayList<BranchEmployee> employees = findBranch.getEmployees();

			if( !employees.contains(employee) ){
				employees.add(employee);		

			} else{
				System.out.println("The employee already exists: " + employee);
			}
		} else{
			System.out.println("Failed. The branch does not exists:  : "+ findBranch);
		}

	}

/**
*	remove employee from branch
*	@param findBranch from add
*	@param employee from add
*/	
	public void removeEmployee(Branch findBranch, BranchEmployee employee){
		KWLinkedList<Branch> branches = company.getBranches();
		if( branches.contains(findBranch) ){
			KWArrayList<BranchEmployee> employees = findBranch.getEmployees();
			if( employees.contains(employee) ){
			
				employees.remove( employee );
			} else{
				System.out.println("The employee does not exist: " + employee);
			}
		} else{
			System.out.println("Failed. The branch does not exists:  : "+ findBranch);
		}
	}
/**To print product detailed for administrator*/
	@Override
	public void printProductsDetailed(){
		KWLinkedList<Branch> currentBranch = company.getBranches();
		String supply = "";
		System.out.printf("%25s", "Product's Type");
		System.out.printf("%25s", "Product's Model");		
		System.out.printf("%25s", "Product's Color");		
		System.out.printf("%25s", "Product's Stock");		
		System.out.printf("%25s", "Product's Need Supply\n");
		for(int i=0; i<company.getNumOfBranches(); i++){
			HybridList<Product> currentProduct = currentBranch.get(i).getProducts();
			for(int j=0; j<currentBranch.get(i).getNumOfProducts(); j++){
				if( currentProduct.get(j).getNeedSupply().equals("Need") ){
					supply = "Need to be supplied.";
				} else{
					supply = "No need to be supplied.";
				}
				System.out.printf("%25s", currentProduct.get(j).getType());
				System.out.printf("%25s", currentProduct.get(j).getModel());		
				System.out.printf("%25s", currentProduct.get(j).getColor());		
				System.out.printf("%25s", currentProduct.get(j).getStock());		
				System.out.printf("%25s", supply);
				System.out.println();
			}
		}
	}
/**To print administrator's information*/
	@Override
	public String toString(){
		return "Administrator's name: " + this.getName() + "\n" + 
				"Administrator's surname: " + this.getSurname() + "\n" + 
				"Administrator's password: " + this.getPassword() + "\n";
	}

/**
*	To compare administrator objects
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
			Administrator temp = (Administrator) o;
			return this.getEmail().equals( temp.getEmail() );
		} catch( Exception e ){
			return false;
		}
	}
	
}