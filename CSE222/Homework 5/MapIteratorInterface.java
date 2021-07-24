/**
* An interface to use the MapIterator class 
* as private class
* @author Emine Sultan Savran
* @param <K> generic type keeps the key
* @param <V> generic type keeps the value
*/
public interface MapIteratorInterface<K,V>{

	/**
	* The function returns the next key in the Map. 
	* It returns the first key when there is
	*  no not-iterated key in the Map.
	* @return returns the next key in the Map
	*/
	public K next();

	/**
	* The iterator points to the previous key in the Map. 
	* It returns the last key when the iterator is 
	* at the first key.
	* @return returns the previous key in the Map
	*/
	public K prev();

	/**
	* The method returns True if there are still not-iterated 
	* key/s in the Map, otherwise returns False.
	* @return true, if there are still not-iterated key/s
	*		false, otherwise
	*/
	public boolean hasNext();
}
