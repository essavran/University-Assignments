package HW7;

public interface SearchTree<E> {
    boolean add(E item);
    boolean contains(Object o);
    E find(E target);
    E delete(E target);
    boolean remove(Object o);
}