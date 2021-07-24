/**
* The abstract class that keeps informations 
* of users
*/
public abstract class User implements UserInterface{

	/**User's ID*/
	private long id;
	/**User's password*/
	private String password;

	User(long id, String password){
		setID(id);
		setPassword(password);
	}

	public void setID(long id){
		this.id = id;
	}

	public long getID(){
		return id;
	}
	
	public void setPassword(String password){
		this.password = password;
	}
	
	public String getPassword(){
		return password;
	}
}