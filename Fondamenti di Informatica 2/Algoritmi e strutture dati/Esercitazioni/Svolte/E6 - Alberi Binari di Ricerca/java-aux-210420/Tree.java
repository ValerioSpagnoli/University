public class Tree {

    private int key;
    private Tree left;
    private Tree right;

    public Tree(int key) {
        this.key = key;
    }

    public static Tree build_1() {

        Tree n6 = new Tree(6);
        Tree n3 = new Tree(3);
        Tree n12 = new Tree(12);
        Tree n1 = new Tree(1);
        Tree n5 = new Tree(5);
        Tree n7 = new Tree(7);
        Tree n15 = new Tree(15);

        n6.left = n3;
        n6.right = n12;

        n3.left = n1;
        n3.right = n5;

        n12.left = n7;
        n12.right = n15;

        return n6;
    }

    public static Tree build_2() {

        Tree n6 = new Tree(6);
        Tree n3 = new Tree(3);
        Tree n12 = new Tree(12);
        Tree n1 = new Tree(1);
        Tree n5 = new Tree(5);
        Tree n7 = new Tree(7);
        Tree n15 = new Tree(15);

        n6.right = n3;
        n6.left = n12;

        n3.left = n1;
        n3.right = n5;

        n12.left = n7;
        n12.right = n15;

        return n6;
    }

    public static Tree build_3() {

        Tree n6 = new Tree(6);
        Tree n3 = new Tree(3);
        Tree n12 = new Tree(12);
        Tree n1 = new Tree(1);
        Tree n5 = new Tree(5);

        n6.left = n3;

        n3.left = n1;
        n3.right = n5;

        n5.right = n12;

        return n6;
    }

    public boolean isBST() {	// è un BST se rispetta l'ordinamento
        int res = isBST(this, 0);
        if(res<0) return false;
        return true;
        
    }
    
    private int isBST(Tree t, int m){ 
		if(t == null) return m;
		int max = isBST(t.left, m);
		if(max == -1 || max > t.key) return -1;
		return isBST(t.right, t.key);
	}
    
    

    public boolean isBalanced() {
		int res  = isBalanced(this);
		if(res<0)return false;
		return true;
    }
    
    private int isBalanced(Tree t){
		if(t == null) return 0;
		int l = isBalanced(t.left);
		int r = isBalanced(t.right);
		if(l<0 || r<0) return -1;
		int diff;
		if(l>=r) diff = l-r;
		else diff = r-l;
		if(diff <= 1){
			if(l>=r) return l+1;
			else return r+1;
		}
		return -1;
	}

    public boolean isAVL() {
		if(isBalanced() && isBST()) return true;
		return false;
    }

}
