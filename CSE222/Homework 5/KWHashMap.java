/**
* An interface KWHashMap
* @param <K> generic type keeps the key
* @param <V> generic type keeps the value
*/
public interface KWHashMap<K,V> {
    
    /**
    * Method get.
    * @param key The key being sought
    * @return The value associated with this key if found;
    *         otherwise, null
    */
	public V get (Object key);

	/**
	* Returns whether the map is empty or not
    * @return true if empty
    *         otherwise, false
    */
	public boolean isEmpty(); 

    /**
    * Method put
    * This key-value pair is inserted in the
    *       table and numKeys is incremented. If the key is already
    *       in the table, its value is changed to the argument
    *       value and numKeys is not changed.
    * @param key The key of item being inserted
    * @param value The value for this key
    * @return The old value associated with this key if
    *         found; otherwise, null
    */   
	public V put(K key, V value);

	/**
    * Removes the mapping for a key from this map if it is present.
    * @param key The key of item being inserted
    * @return The removed value associated with this key if
    *         found; otherwise, null
    */
 	public V remove(Object key);

 	/**
 	* returns size
 	* @return size 
 	*/
 	public int size();
}