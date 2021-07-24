package HW7;

import java.util.ArrayList;
import java.util.List;

/**
 * An implementation of the B-tree. A B-tree is a
 * search tree in which each node contains n data items where
 * n is between N/2 and N. (For the root, n may be between 1
 * and N. Other than leaves there are n+1 children.  The tree
 * is always balanced in that all leaves are on the same level,
 * i.e., the length of the path  from the root to a leaf is
 * constant.
 * @param <E> The element type
 * @author Koffman and Wolfgang
 */
public class BTree<E extends Comparable<E>> {
    /** A Node represents a node in a B-tree.
     */
    protected static class Node<E> {
        //Data fields
        /** The number of data items in this node */
        public int size = 0;
        /** The information */
        public final E[] data;
        /** The links to the children. child[i] refers to
         *  the subtree of children less than data[i] for i less than size
         *  and to the subtree of children less than data[size-1]
         *  for i == size  */
        public final Node<E>[] child;

        /**
         * Create an empty node of size nn
         * @param order - The size of a node
         */
        @SuppressWarnings("unchecked")
        public Node(int order) {
            data = (E[]) new Comparable[order - 1];
            child = (Node<E>[]) new Node[order];
            size = 0;
        }

        /**
         * Return a String representation of this node
         * @return a String representation of this node
         */
        @Override
        public String toString() {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < size - 1; ++i) {
                sb.append(data[i].toString());
                sb.append(", ");
            }
            sb.append(data[size - 1].toString());
            return sb.toString();
        }
    }
    
    /** The root node. */
    protected Node<E> root = null;
    /** The maximum number of children of a node */
    private int order;
    /** The parent of a split node returned from insert */
    private E newParent;
    /** The right half of a split node returned from insert */
    private Node<E> newChild;

    /**
     * Construct a B-tree with a specified order
     * @param order - the size of a node
     * @throws IllegalArgumentException if order less than 3
     */
    public BTree(int order) {
    //    if (order < 3) {
    //        throw new IllegalArgumentException("order < 3");
    //    }
        this.order = order;
        root = null;
    }

    /**
     * Insert an Object into the tree.  Inserted item
     * must implement the Comparable interface
     * @param item The object to be inserted
     * @return true if the item was inserted
     */
    public boolean add(E item) {
        if (order == 0) {
            throw new IllegalStateException("Must set order first");
        }
        if (root == null) {
            root = new Node<E>(order);
            root.data[0] = item;
            root.size = 1;
            return true;
        }
        newChild = null;
        boolean result = insert(root, item);
        if (newChild != null) {
            Node<E> newRoot = new Node<>(order);
            newRoot.child[0] = root;
            newRoot.child[1] = newChild;
            newRoot.data[0] = newParent;
            newRoot.size = 1;
            root = newRoot;
        }
        return result;
    }

    /** Recursively insert an item into the B‐tree. Inserted
    item must implement the Comparable interface
    @param root The local root
    @param item The item to be inserted
    @return true if the item was inserted,
    false if the item is already in the tree
    */
    private boolean insert(Node<E> root, E item) {
        int index = binarySearch(item, root.data, 0, root.size);
        if (index != root.size && item.compareTo(root.data[index]) == 0) {
            return false;
        }
        if (root.child[index] == null) {
            if (root.size < order-1) {
                insertIntoNode(root, index, item, null);
                newChild = null;
            } else {
                splitNode(root, index, item, null);
            }
            return true;
        } else {
            boolean result = insert(root.child[index], item);
            if (newChild != null) {
                if (root.size < order-1) {
                    insertIntoNode(root, index, newParent, newChild);
                    newChild = null;
                } else {
                    splitNode(root, index, newParent, newChild);
                }
            }
            return result;
        }
    }

    /** Method to insert a new value into a node
    @pre node.data[index‐1] < item < node.data[index];
    @post node.data[index] == item and old values are moved right one position
    @param node The node to insert the value into
    @param index The index where the inserted item is to be placed
    @param item The value to be inserted
    @param child The right child of the value to be inserted
    */
    private void insertIntoNode(Node<E> node, int index, E obj, Node<E> child) {
        for (int i = node.size; i > index; i--) {
            node.data[i] = node.data[i - 1];
            node.child[i + 1] = node.child[i];
        }
        node.data[index] = obj;
        node.child[index + 1] = child;
        node.size++;
    }

    private void splitNode(Node<E> node, int index, E item, Node<E> child) {
        // Create new child
        newChild = new Node<E>(order);
        // Determine number of items to move
        int numToMove = (order-1) - ((order-1) / 2);
        // If insertion point is in the right half, move one less item
        if (index > (order-1) / 2) {
            numToMove--;
        }
        // Move items and their children
        System.arraycopy(node.data, order - numToMove - 1,
        newChild.data, 0, numToMove);
        System.arraycopy(node.child, order - numToMove,
        newChild.child, 1, numToMove);
        node.size = order - numToMove - 1;
        newChild.size = numToMove;
        // Insert new item
        if (index == ((order-1) / 2)) { // Insert as middle item
            newParent = item;
            newChild.child[0] = child;
        } else {
            if (index < ((order-1) / 2)) { // Insert into the left
                insertIntoNode(node, index, item, child);
            } else {
                insertIntoNode(newChild, index - ((order-1) / 2) - 1, item, child);
            }
            // The rightmost item of the node is the new parent
            newParent = node.data[node.size - 1];
            // Its child is the left child of the split‐off node
            newChild.child[0] = node.child[node.size];
            node.size--;
        }
        // Remove items and references to moved items
        for (int i = node.size; i < node.data.length; i++) {
            node.data[i] = null;
            node.child[i + 1] = null;
        }
    }

    /**
     * Perform a binary search of the array data for target.
     * @param target The item being sought
     * @param data The sorted array the may contain the data
     * @param first The first index to be searched
     * @param last One past the last index to be searched
     * @return The smallest index such that target >= data[index]
     */
    private int binarySearch(E target, E[] data, int first, int last) {
        if (first == last) {
            return first;
        }
        if (last - first == 1) {
            if (target.compareTo(data[first]) <= 0) {
                return first;
            } else {
                return last;
            }
        }
        int middle = first + (last - first) / 2;
        int compResult = target.compareTo(data[middle]);
        if (compResult == 0) {
            return middle;
        }
        if (compResult < 0) {
            return binarySearch(target, data, first, middle);
        } else {
            return binarySearch(target, data, middle + 1, last);
        }
    }

    /**
     * Return a pre-order traversal as the string
     * representation of the tree
     * @return a string representation of the tree
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(root, 0, sb);
        return sb.toString();
    }

    /**
     * Perform a pre-order traversal
     * @param node - The local root
     * @param d - The depth
     * @param sb - The string buffer to put the output
     */
    private void preOrderTraverse(Node<E> node, int d, StringBuilder sb) {
        for (int i = 0; i != d; ++i) {
            sb.append("  ");
        }
        if (node == null) {
            sb.append("null");
        } else {
            for (int i = 0; i != node.size; ++i) {
                sb.append(node.data[i]);
                if (i != node.size - 1) {
                    sb.append(", ");
                }
            }
            sb.append("\n");
            for (int i = 0; i != node.size; ++i) {
                preOrderTraverse(node.child[i], d + 1, sb);
                sb.append("\n");
            }
            preOrderTraverse(node.child[node.size], d + 1, sb);
            sb.append("\n\n");
        }
    }
}