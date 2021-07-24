import java.io.BufferedReader;  
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Hashtable;
/**
* The class that keeps informations 
* of Admin
*/
public class Administrator extends User{
	
	//Data fields
	/**Keeps the traders*/
	private Hashtable<String, User> traders;
	//Methods
	Administrator(){
		super(00000000, "000000");
		traders = new Hashtable<String, User>();
	}

	/**
	* reads CSV file and creates Products.txt and Users.txt
	* @return if there is no problem, true
	*			otherwise false
	*/
	public boolean csvFile(){
		String row = "";
		long userCount = 10000000; 
		try{  
			FileReader pathToCSV = new FileReader("e-commerce-samples.csv");
			BufferedReader csvReader = new BufferedReader(pathToCSV); 
			FileWriter productsWriter = new FileWriter("Products.txt");
			FileWriter usersWriter = new FileWriter("Users.txt", false);
			row = csvReader.readLine();
			while ( (row = csvReader.readLine()) != null ){ 
				//reading a row
				String[] informations = row.split(";");    // use semicolon as separator
				for(int i=0; i<informations.length; i++){
					productsWriter.write( informations[i] + "\n" );
				}
				productsWriter.write( "\n" );
				//bu user eğer user txtde yoksa, onu oraya ekleyyeyim
				if( !traders.containsKey( informations[6] ) ){
					usersWriter = new FileWriter("Users.txt", true);
					usersWriter.write( ++userCount + ";" + "123456" + ";" + informations[6] + "\n" );
					usersWriter.close();
					traders.put(informations[6], new Trader(userCount, informations[6]));
				}
			}
      		productsWriter.close();
     		return true; 
		} catch(Exception e){
			System.out.println("There is a problem! Files cannot created.");
			return false;
		}
	}

	/**
	* checks whether the user is at Users.txt
	* @return if exists, true
	*			otherwise false
	*/
	private boolean containsUser(String userName){
		String row = "";
		try{  
			FileReader pathToUsers = new FileReader("Users.txt");
			BufferedReader usersReader = new BufferedReader(pathToUsers);
			while ( (row = usersReader.readLine()) != null ){
				//reading a row
				String[] informations = row.split(";");    // use semicolon as separator
				if( informations.length == 3 && informations[2].equals( userName ) ){
					return true;
				}
			}
			usersReader.close();
			return false;
		} catch (Exception e){
			return false;
		} 
	}

	/**
	* checks whether users who want to log in are registered
	* @param id id
	* @param password password
	* @return if exists, true
	*			otherwise false
	*/
	public String login(String id, String password){
		String row = "";
		try{  
			FileReader pathToUsers = new FileReader("Users.txt");
			BufferedReader usersReader = new BufferedReader(pathToUsers);
			while ( (row = usersReader.readLine()) != null ){
				//reading a row
				String[] informations = row.split(";");    // use semicolon as separator
				if( informations[0].equals( id ) &&
					informations[1].equals( password ) ){
					return row;
				}
			}
			usersReader.close();
			return "";
		} catch (Exception e){
			return "";
		} 
	}


/*
	private boolean containProduct(String target){
		String row = "";
		try{  
			FileReader pathToProducts = new FileReader("Products.txt");
			BufferedReader productsReader = new BufferedReader(pathToProducts);
			while ( (row = productsReader.readLine()) != null ){ //&& flag<3 ){
				//reading a row
				if( row.equals( target ) ){
					return true;
				}
				for(int i=0; i<7; i++){
					row = productsReader.readLine();
				}
			}
			return false;
		} catch (IOException e){  
			e.printStackTrace();  
			return false;
		}  
	}
*/

}