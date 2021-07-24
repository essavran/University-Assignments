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
*	@param Company the company
*/		
	public Administrator(String name, String surname, String email, String password, Company company){
		super(name, surname, email, password, company);	
	}

/**
*	add admins to company
*	@param admin to add
*/
	public void addAdmin(Administrator admin){
		//zaten eklenmiş bir admini eklemeye çalışbilir
		Administrator[] admins = company.getAdmins();
		if( containsAdmin(admin) ){
			System.out.println("The admin already exists: "+ admin);
		} else{
			//make sure there is a room
			if( company.getCapacityOfAdmins() <= company.getNumOfAdmins() ){
				reallocateAdmin();
			}
			admins = company.getAdmins();
			admins[ company.getNumOfAdmins() ] = admin;
			company.setNumOfAdmins( company.getNumOfAdmins()+1 );
		}
	}
/**
*	extend size of the admin arrays
*/	
	private void reallocateAdmin(){
		Administrator[] admins = company.getAdmins();
		company.setCapacityOfAdmins( company.getCapacityOfAdmins()*2 );
		Administrator[] temp = new Administrator[ company.getCapacityOfAdmins() ];
		for(int i=0; i<company.getNumOfAdmins(); i++){
			temp[i] = admins[i];
		}
		company.setAdmins( temp );
	}
/**
*	removes admin from the company
*	@param admin to remove
*/	
	public void removeAdmin(Administrator admin){
		if( containsAdmin(admin) ){
			//böyle bir admin var, silebilirim
			int index = 0;
			Administrator[] admins = company.getAdmins();
			Administrator[] temp = new Administrator[ company.getCapacityOfAdmins() ];
			for(int i=0; i<company.getNumOfAdmins(); i++){
				if( admins[i].getName().equals( admin.getName() ) && admins[i].getSurname().equals( admin.getSurname() ) ) //böyle biri var
					index++;
				temp[i] = admins[index];
				index++;
			}
			company.setAdmins( temp );
			company.setNumOfAdmins( company.getNumOfAdmins()-1 );
		} else{
			System.out.println("Failed. The admin does not exist : " + admin);
		}
	}

/**
*	add branch to company
*	@param branch to add
*/	
	public void addBranch(Branch branch){
		Branch[] branches = company.getBranches();
		if( containsBranch(branch) ){
			System.out.println("The branch already exists: "+ branch);
		} else{
			//make sure there is a room
			if( company.getCapacityOfBranches() <= company.getNumOfBranches() ){
				reallocateBranch();
			}
			branches = company.getBranches();
			branches[ company.getNumOfBranches() ] = branch;
			company.setNumOfBranches( company.getNumOfBranches()+1 );
		}

	}
/**
*	extends size of the branches array
*/	
	private void reallocateBranch(){//free() tarzı bi şey yapmam gerekiyo mu
		Branch[] branches = company.getBranches();
		company.setCapacityOfBranches( company.getCapacityOfBranches()*2 );
		Branch[] temp = new Branch[ company.getCapacityOfBranches() ];
		for(int i=0; i<company.getNumOfBranches(); i++){
			temp[i] = branches[i];
		}
		company.setBranches( temp );
	}
/**
*	remove branch from the company
*	@param branch to remove
*/	
	public void removeBranch(Branch branch){
		//olmayan bir admini silmeye çalışabilir
		if( containsBranch(branch) ){
			//böyle bir admin var, silebilirim
			int index = 0;
			Branch[] branches = company.getBranches();
			Branch[] temp = new Branch[ company.getCapacityOfBranches() ];
			for(int i=0; i<company.getNumOfBranches(); i++){
				if( branches[i].getName().equals( branch.getName() ) ) //böyle biri var
					index++;
				temp[i] = branches[index];
				index++;
			}
			company.setBranches( temp );
			company.setNumOfBranches( company.getNumOfBranches()-1 );
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
		//böyle bir brach var mı 
		//varsa böyle bir işçi var mı
		//yoksa ekle		
		
		if( containsBranch(findBranch) ){
			BranchEmployee[] employees = findBranch.getEmployees();

			if( !containsEmployee(findBranch, employee) ){
			
				if( findBranch.getCapacityOfEmployees() <= findBranch.getNumOfEmployees() ){
					reallocateEmployee(findBranch);
				}
				employees = findBranch.getEmployees();
				employees[ findBranch.getNumOfEmployees() ] = employee;
				findBranch.setNumOfEmployees( findBranch.getNumOfEmployees()+1 );			

			} else{
				System.out.println("The employee already exists: " + employee);
			}
		} else{
			System.out.println("Failed. The branch does not exists:  : "+ findBranch);
		}

	}
/**
*	extends size of the employees array
*/	
	private void reallocateEmployee(Branch findBranch){//free() tarzı bi şey yapmam gerekiyo mu
		BranchEmployee[] employees = findBranch.getEmployees();
		findBranch.setCapacityOfEmployees( findBranch.getCapacityOfEmployees()*2 );
		BranchEmployee[] temp = new BranchEmployee[ findBranch.getCapacityOfEmployees() ];
		for(int i=0; i<findBranch.getNumOfEmployees(); i++){
			temp[i] = employees[i];
		}
		findBranch.setEmployees( temp );
	}

/**
*	remove employee from branch
*	@param findBranch from add
*	@param employee from add
*/	
	public void removeEmployee(Branch findBranch, BranchEmployee employee){
		if( containsBranch(findBranch) ){
			int index = 0;
			BranchEmployee[] employees = findBranch.getEmployees();
			BranchEmployee[] temp = new BranchEmployee[ findBranch.getCapacityOfEmployees() ];
			if( containsEmployee(findBranch, employee) ){
			
				for(int i=0; i<findBranch.getNumOfEmployees(); i++){
					if( employees[i].getName().equals( employee.getName() ) && employees[i].getSurname().equals( employee.getSurname() ) ) //böyle biri var
						index++;
					temp[i] = employees[index];
					index++;
				}
				findBranch.setEmployees( temp );
				findBranch.setNumOfEmployees( findBranch.getNumOfEmployees()-1 );		

			} else{
				System.out.println("The employee does not exist: " + employee);
			}
		} else{
			System.out.println("Failed. The branch does not exists:  : "+ findBranch);
		}
	}

	@Override
	public void printProductsDetailed(){
		Branch[] currentBranch = company.getBranches();
		String supply = "";
		System.out.printf("%25s", "Product's Type");
		System.out.printf("%25s", "Product's Model");		
		System.out.printf("%25s", "Product's Color");		
		System.out.printf("%25s", "Product's Stock");		
		System.out.printf("%25s", "Product's Need Supply\n");
		for(int i=0; i<company.getNumOfBranches(); i++){
			Product[] currentProduct = currentBranch[i].getProducts();
			for(int j=0; j<currentBranch[i].getNumOfProducts(); j++){
				if( currentProduct[j].getNeedSupply().equals("Need") ){
					supply = "Need to be supplied.";
				} else{
					supply = "No need to be supplied.";
				}
				System.out.printf("%25s", currentProduct[j].getType());
				System.out.printf("%25s", currentProduct[j].getModel());		
				System.out.printf("%25s", currentProduct[j].getColor());		
				System.out.printf("%25s", currentProduct[j].getStock());		
				System.out.printf("%25s", supply);
				System.out.println();
			}
		}
	}

	@Override
	public void userProfile(){
		System.out.println( "Administrator's name: " + this.getName() + "\n" + 
							"Administrator's surname: " + this.getSurname() + "\n" + 
							"Administrator's password: " + this.getPassword() );
	}

	@Override
	public String toString(){
		//this yazmam saçma mı oldu acaba :D
		return this.getName() + " " + this.getSurname() + " " + this.getPassword() + "\n";
	}
	
}