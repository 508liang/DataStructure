# tree

a set of connected nodes，故为hierarchical 
Each node in the tree can be connected to many **children** (depending on the type of tree) #children->its **degree**(度), 

but must be connected to exactly one **parent**, except for the **root**, which has no parent. A **leaf** of a tree has no children

Define **depth**(<X>) of node <X> in a tree rooted at to be length of path from to <X> to <R>

Define **height**(<X>) of node to be max depth of any node in the subtree rooted at <X>

> ordered tree有序树  Tree edit distance;

These constraints mean there are **no cycles or "loops"** (no node can be its own ancestor), and also that each child can be treated like the root node of its own **subtree**, making `recursion` a useful technique for tree traversal.

from ROOT travel to one node, the pass-by nodes(except for itself) are called the **ancestor** nodes of this node


