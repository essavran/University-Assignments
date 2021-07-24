import java.util.LinkedList;
/**
 * Hash table implementation using coalesced hashing technique.
*/
public class HashtableCoalesced<K, V> implements KWHashMap<K, V> {

    /** The table */
    private LinkedList<Entry<K, V>>[] table;
    /** The number of keys */
    private int numKeys;
    /** The capacity */
    private static final int CAPACITY = 11;
    /** The maximum load factor */
    private static final double LOAD_THRESHOLD = 0.75;
    /** The number of deletes */
    private int numDeletes;

    /** Contains key‐value pairs for a hash table. */
    private static class Entry<K, V> {
        /** The key */
        private final K key;
        /** The value */
        private V value;
        /**To keep the next key*/
        private int next;

        /** Creates a new key‐value pair.
        * @param key The key
        * @param value The value
        */
        public Entry(K key, V value) {
            this.key = key;
            this.value = value;
            this.next = -1;
        }
        /** Retrieves the key.
        * @return The key
        */
        public K getKey() {
            return key;
        }
        /** Retrieves the value.
        * @return The value
        */
        public V getValue() {
            return value;
        }
        /** Sets the value.
        * @param val The new value
        * @return The old value
        */
        public V setValue(V val) {
            V oldVal = value;
            value = val;
            return oldVal;
        }

        /** Retrieves the value.
        * @return The value
        */
        public int getNext() {
            return next;
        }
        /** Sets the value.
        * @param next The new value
        */
        public void setNext(int next) {
            this.next = next;
        }


        /**
         * Returns a string representation of the Entry.
         * @return The string in format "key=value"
         */
        public String toString() {
            if( next == -1 )
                return key + "=" + value + " , null ";
            return key + "=" + value + " , " + next;
        }
    }

    // Constructor
    /**
     * Construct a new HashtableCoalesced object of size CAPACITY
     */
    @SuppressWarnings("unchecked")
    public HashtableCoalesced() {
        table = new LinkedList[CAPACITY];
    }


    @Override
    public V get(Object key) {
        int index = find(key);
        if (table[index] == null || 
            table[index].size() == 0 ||
            table[index].get(0) == null) {
            return null; // key is not in the table.
        }
        // Search the list at table[index] to find the key.
        return table[index].get(0).getValue();
    }

    @Override
    public V put(K key, V value) {
        int index = find(key);
        if (table[index] == null || 
            table[index].size() == 0 ||
            table[index].get(0) == null) {
            // Create a new linked list at table[index].
            //bu hashcode boştu yer açtım
            table[index] = new LinkedList<Entry<K, V>>();



            for(int i=0; i<table.length; i++){
                if( (table[i] != null) &&
                    (table[i].size() != 0) &&
                    (table[i].get(0) != null) &&
                    table[i].get(0).key.equals( key ) ){
                    V oldVal = table[i].get(0).value;
                    table[i].get(0).setValue(value);
                    return oldVal;
                }
            }

            table[index].addFirst(new Entry<K, V>(key, value));
            addNext(key, index);
            numKeys++;
            double loadFactor = (double) (numKeys+numDeletes) / table.length;
            if( loadFactor > LOAD_THRESHOLD ){
                rehash();
            }
            return null;
        }
        //bu eleman tabloda zaten var mı bakıyorum
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
        V oldVal = null;
        if( (table[index] != null) &&
                (table[index].size() != 0) &&
                (table[index].get(0) != null) ){
            oldVal = table[index].get(0).getValue();
            table[index].get(0).setValue( value );

        }
        return oldVal; 
    }

    public boolean isEmpty() {
        return numKeys == 0;
    }
    
    /**
     * Method to rehash table.
     * Allocates a new hash table that is double the size and has an odd length.
     * Reinsert each table entry in the new hash table.
     */
    private void rehash() {
        LinkedList<Entry<K,V>>[] oldTable = table;
        table = new LinkedList[oldTable.length * 2 + 1];

        numKeys = 0;
        numDeletes = 0;
        for (LinkedList<Entry<K, V>> list : oldTable) {
            if (list != null) {
                for (Entry<K,V> entry : list) {
                    put(entry.getKey(), entry.getValue());
    //                numKeys++;
                }
            }
        }
    }


    @Override
    public V remove(Object key) {
        int index = find(key);
        if (table[index] == null) {
            return null; // key is not in table
        }

        int temp = index;

        while( table[index].get(0).getNext() != -1 ){
            index = table[index].get(0).getNext();
            table[temp].addFirst(new Entry<K, V>(table[index].get(0).getKey(), table[index].get(0).getValue()));
            table[temp].get(0).setNext(table[index].get(0).getNext());
            temp = index;
        }

        V value = table[index].get(0).getValue();
        table[index].remove(table[index].get(0));
        numDeletes++;
        if (table[index].isEmpty()) {
            table[index] = null;
        }
        return value;
        
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
        Entry<K,V> entry = null;
        for (int i = 0; i < table.length; i++) {
            sb.append("[" + i + "] ");
            try{
                entry = table[i].get(0);
            } catch(Exception e){
                entry = null ;
            }
            sb.append("-> " + entry + " ");
            
            sb.append("\n");
        }
        return sb.toString();
    }

    /**
    *   To find valid index value according to coalesced hashing technique
    *   @param key to find index of the key
    *   @return index value
    */
    private int find(Object key){
        int k = -1;
        int index = key.hashCode() % table.length;
        if( index < 0 ){
            index += table.length;
        }
        int firstIndex = index;
        int temp = index;
        while( (table[index] != null) &&
             (!key.equals(table[index].get(0).key)) ){
            k += 2;
            index = (index+k) % table.length;
            if( index >= table.length ){
                index = 0;
            }
        }
        return index;
    }

    /**
    *   To link related keys
    *   @param key to link
    *   @paran index index of the key
    */
    private void addNext(Object key, int index){
        for(int i=index; i>=0; i--){
            if( table[i] != null &&
                table[i].size() != 0 &&
                table[i].get(0) != null &&
                (table[i].get(0).getNext() == -1) && 
                (table[i].get(0).getKey().hashCode() % table.length == key.hashCode() % table.length) &&
                i != index ){
                table[i].get(0).setNext(index);
            }
        }
    }
}