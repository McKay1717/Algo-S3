/**
 * Created by sdomas on 03/10/16.
 */
public class Tree {
    Node root;
    Board board;

    int nbConfigurations;

    public Tree(Board board) {
        root = null;
        this.board = board;
	nbConfigurations = 0;
    }

    /* setFirstBlueChoice():
       create the root node of the tree, that represents the first turn of a party, i.e.
       the cell chosen by the blue player to put its pawn #1

       CAUTION: it also sets the pawn in the board
     */
    public void setFirstBlueChoice(int idCell) {

        root = new Node(idCell,1);
        board.setPawn(idCell,(byte)1);
    }

    /* setFirstRedChoice():
       create the node that represents the second turn of a party, i.e.
       the cell chosen by the red player to put its pawn #1

       CAUTION: it also sets the pawn in the board
     */
    public void setFirstRedChoice(int idCell) {
        root.addChild(idCell);
        board.setPawn(idCell,(byte)7);
    }

    /* buildTree();
        build the tree of all possible evolution of the party, taking into account
        the first choice of blue and red
     */
    public void buildTree() {

        nbConfigurations = 0;
        /*get the single child of the root, i.e. the node that
          represents the first pawn played by red player.
        */
        Node n = root.children[0];
        // call the recursive method that build the tree from that node
        computePossibilities(n);

        System.out.println(" done.");
    }

    /* computePossibilities():
       create all possible children of Node n.
     */
    public void computePossibilities(Node n) {

        /* if n represents the last turn of the party, stop the recursion
           and determine winner
         */
        if (n.turn == 12) {
            board.computeScore();
            int r = board.redScore;
            int b = board.blueScore;
            if (b == r) {
                n.result = Node.DRAW_PARTY;
            }
            // if blue obtains less than red -> blue wins
            else if (b < r) {
                n.result = Node.BLUE_WINS;
            }
            // if red obtains less than blue -> red wins
            else {
                n.result = Node.RED_WINS;
            }
            nbConfigurations += 1;
            if ((nbConfigurations % 1000000) == 0) System.out.print(".");
            return;
        }
        /* determine value of the next pawn that must be played from n.turn
         */
        int nextPawnValue = (n.turn+2)/2; // get the "real" value (i.e. from 1 to 6)
        if ((n.turn+1)%2 == 0) nextPawnValue += 6; // get the value in the board if it is a red one
        // check for all remaining void cells and try to place a pawn
        for(int i=0;i<13;i++) {
            // if the cell i is empty
            if (board.board[i] == Board.VOID_CELL) {
                // place the pawn here
                board.setPawn(i,(byte)nextPawnValue);
                // create the corresponding node in the tree
                Node child = n.addChild(i);
                // recursive call
                computePossibilities(child);
                // remove pawn so that the cell appears to be free
                board.setPawn(i,Board.VOID_CELL);
            }
        }
    }

    /* computeBlueVictories()
        determine recursively in how many cases blue wins
        in the tree that begins with n. This can be done
        by using the value of result attribute in leaves.
     */
    public int computeBlueVictories(Node n) {
        int nb = 0, i;
        
        if(n.nbChildren == 0 && n.result == Node.BLUE_WINS)
			nb++;
			
		for(i = 0; i < n.nbChildren; i++)
			nb += computeBlueVictories(n.children[i]);
			
        return nb;
    }

    /* computeRedVictories()
        determine recursively in how many cases red wins
        in the tree that begins with n. This can be done
        by using the value of result attribute in leaves.
     */
    public int computeRedVictories(Node n) {
        int nb = 0, i;
        
        if(n.nbChildren == 0 && n.result == Node.RED_WINS)
			nb++;
			
		for(i = 0; i < n.nbChildren; i++)
			nb += computeRedVictories(n.children[i]);
			
        return nb;
    }

    /* computeDraws()
        determine recursively in how many cases blue and red
         are draw in the tree that begins with n. This can be done
        by using the value of result attribute in leaves.
     */
    public int computeDraws(Node n) {
        int nb = 0, i;
        
        if(n.nbChildren == 0 && n.result == Node.DRAW_PARTY)
			nb++;
			
		for(i = 0; i < n.nbChildren; i++)
			nb += computeDraws(n.children[i]);
			
        return nb;
    }
}
