import java.util.*;
/**
* A class that extends the HashMap 
* and adds an iterator feature
* @author Emine Sultan Savran
* @param <K> generic type keeps the key
* @param <V> generic type keeps the value
*/
public class IterHashMap<K,V> extends HashMap<K,V>{

    /**
    * To return the MapIterator which is the iterator of HashMap
    * @return the iterator of HashMap
    */
	public MapIterator<K,V> iter(){
		return new MapIterator<K,V>();
	}

	/**
    * To return the MapIterator which is the iterator of HashMap
    * with spesific key value
    * @param key location of the iterator
    * @return the iterator of HashMap with specific key value
    */
	public MapIterator<K,V> iter(K key){
		return new MapIterator<K,V>(key);
	}

	/**
	* A private class to represent MapIterator
	* implements MapIteratorInterface<K,V>
	*/
	private class MapIterator<K,V> implements MapIteratorInterface<K,V>{
		//V hiç kullanmadın 

		//Data fields
		/**location of the iterator*/
		private int cursor = -1;
		/**IterHashMap's iterator*/
		private Iterator iterKeys;
		/**To count iterated keys in the map*/
		private int totalIter = 0;
		private boolean checkIterable = true;
		/**Default constructor*/
		MapIterator(){
			cursor = 0;
			totalIter = 0;
			iterKeys = IterHashMap.this.keySet().iterator();
		}

		/**
		* Constructor with specific key value
		* @param key location of the iterator
		*/
		MapIterator(K key){
			this();
			if( containsKey(key) ){
				K temp = (K)iterKeys.next();
				while( !temp.equals(key) ){
					temp = (K)iterKeys.next();
					cursor++;
				}
			}
		}

		public K next(){
			totalIter++;
			if( totalIter == size() ){
				checkIterable = false;
			}
			try{
				cursor++;
				return (K)iterKeys.next();
			} catch(Exception e){
				iterKeys = IterHashMap.this.keySet().iterator();
				return (K)iterKeys.next();
			}
		}

		public K prev(){
			if( totalIter == size() ){
				checkIterable = false;
			}
			totalIter--;
			iterKeys = IterHashMap.this.keySet().iterator();
			int goalIndex = 0; 
			if( cursor%size() == 0 || cursor%size() == 1  ){
				goalIndex = size()-1;
			} else if( cursor%size() > 0 ){
				goalIndex = (cursor%size())-1;
			}
			int index = 0;
			K temp = (K)iterKeys.next();
			while( index < goalIndex ){
				temp = (K)iterKeys.next();
				index++;
			}
			cursor--;
			if(cursor < 0){
				cursor = size()-1;
			}
			return temp;
		}

		public boolean hasNext(){
			return checkIterable;
		}

	}

}
