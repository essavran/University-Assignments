import java.util.TreeSet;

/**
 * Hash table implementation using chaining with TreeSet
*/
public class HashtableChainTreeSet<K extends Comparable<K>, V extends Comparable<V>>  implements KWHashMap<K, V> {

    /** The table */
    private TreeSet<Entry<K, V>>[] table;
    /** The number of keys */
    private int numKeys;
    /** The capacity */
    private static final int CAPACITY = 11;
    /** The maximum load factor */
    private static final double LOAD_THRESHOLD = 3.0;

    /** Contains key‐value pairs for a hash table. */
    private static class Entry<K extends Comparable<K>, V extends Comparable<V>> implements Comparable<Entry<K, V>>  {
        /** The key */
        private final K key;
        /** The value */
        private V value;
        /** Creates a new key‐value pair.
        @param key The key
        @param value The value
        */
        public Entry(K key, V value) {
            this.key = key;
            this.value = value;
        }
        /** Retrieves the key.
        @return The key
        */
        public K getKey() {
            return key;
        }
        /** Retrieves the value.
        @return The value
        */
        public V getValue() {
            return value;
        }
        /** Sets the value.
        @param val The new value
        @return The old value
        */
        public V setValue(V val) {
            V oldVal = value;
            value = val;
            return oldVal;
        }

        /**
         * Returns a string representation of the Entry.
         * @return The string in format "key=value"
         */
        @Override
        public String toString() {
            return key + "=" + value;
        }
        /**
        * Comparing objects
        * @param o the object
        * @return Negative int if there is no the element or the heap is empty
        *         positive int if there is the element      
        */
        @Override
        public int compareTo(Entry<K, V> other) {
            return key.compareTo(other.key);
        }
    }

    // Constructor
    /**
     * Construct a new HashtableChain object of size CAPACITY
     */
    @SuppressWarnings("unchecked")
    public HashtableChainTreeSet() {
        table = new TreeSet[CAPACITY];
    }

    @Override
    public V get(Object key) {
        int index = key.hashCode() % table.length;
        if (index < 0) {
            index += table.length;
        }
        if (table[index] == null) {
            return null; // key is not in the table.
        }
        // Search the list at table[index] to find the key.
        for (Entry<K, V> nextItem : table[index]) {
            if (nextItem.key.equals(key)) {
                return nextItem.value;
            }
        }

        // assert: key is not in the table.
        return null;
    }

    @Override
    public V put(K key, V value) {
        int index = key.hashCode() % table.length;
        if (index < 0) {
            index += table.length;
        }
        if (table[index] == null) {
            // Create a new linked list at table[index].
            table[index] = new TreeSet<Entry<K, V>>();
        }

        // Search the list at table[index] to find the key.
        for (Entry<K, V> nextItem : table[index]) {
            // If the search is successful, replace the old value.
            if (nextItem.key.equals(key)) {
                // Replace value for this key.
                V oldVal = nextItem.value;
                nextItem.setValue(value);
                return oldVal;
            }
        }

        table[index].add(new Entry<K, V>(key, value));
  
        numKeys++;
        if (numKeys > (LOAD_THRESHOLD * table.length)) {
            rehash();
        }
        return null;
    }

    @Override
    public boolean isEmpty() {
        return numKeys == 0;
    }
    
    /**
     * Method to rehash table.
     * Allocates a new hash table that is double the size and has an odd length.
     * Reinsert each table entry in the new hash table.
     */
    private void rehash() {
        TreeSet<Entry<K,V>>[] oldTable = table;
        table = new TreeSet[oldTable.length * 2 + 1];
        numKeys = 0;
        for (TreeSet<Entry<K, V>> list : oldTable) {
            if (list != null) {
                for (Entry<K,V> entry : list) {
                    put(entry.getKey(), entry.getValue());
                    numKeys++;
                }
            }
        }
    }
    
    @Override
    public V remove(Object key) {
        int index = key.hashCode() % table.length;
        if (index < 0) {
            index += table.length;
        }
        if (table[index] == null) {
            return null; // key is not in table
        }
        for (Entry<K, V> entry : table[index]) {
            if (entry.getKey().equals(key)) {
                V value = entry.getValue();
                table[index].remove(entry);
                numKeys--;
                if (table[index].isEmpty()) {
                    table[index] = null;
                }
                return value;
            }
        }
        return null;
    }

    @Override
    public int size() {
        return numKeys;
    }
    
        /**
     * Returns a String representation of the map.
     */
    public String toString() {
        StringBuilder sb = new StringBuilder();
        TreeSet<Entry<K, V>> entry = null;
        for (int i = 0; i < table.length; i++) {
            sb.append("[" + i + "] ");
            try{
                try{
                    entry = table[i];
                } catch(Exception e){
                    entry = null ;
                }
                sb.append("-> " + entry + " ");
                
            } catch(Exception e){
                entry = null ;
                sb.append("-> " + entry + " ");
            }
            sb.append("\n");
        }
        return sb.toString();
    } 
    
}