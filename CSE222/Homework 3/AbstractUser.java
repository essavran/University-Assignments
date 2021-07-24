/**
*	The Abstract Class AbstractUser
*	This is a class that shows what actions administrator, customer, and customer can do
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public abstract class AbstractUser implements User{
	/**the Company*/
	protected Company company;
	/**user's name*/
	private String name;
	/**user's surname*/
	private String surname;
	/**user's email*/
	private String email;
	/**user's password*/
	private String password;
/**
*	The base constructor class
*	@param name user's name
*	@param surname user's surname
*	@param email user's email
*	@param password user's password
*	@param company the company
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
/**
*	Set name
*	@param name
*/
	public void setName(String name){
		this.name = name;
	}
/**
*	get the name
*	@return name
*/
	public String getName(){
		return name;
	}
/**
*	Set surname
*	@param surname
*/
	public void setSurname(String surname){
		this.surname = surname;
	}
/**
*	get the surname
*	@return surname
*/
	public String getSurname(){
		return surname;
	}
/**
*	Set password
*	@param password
*/
	public void setPassword(String password){
		this.password = password;
	}
/**
*	get the password
*	@return password
*/
	public String getPassword(){
		return password;
	}
/**
*	Set email
*	@param email
*/
	public void setEmail(String email){
		this.email = email;
	}
/**
*	get the email
*	@return email
*/
	public String getEmail(){
		return email;
	}

}