# AA-Tree
AA trees are a type of self balancing binary search trees and a variation of Red-Black trees. 
They were introduced by Arne Andersson in 1993, hence the name AA, as a simpler alternative to Red-Black trees. 
AA trees use the concept of levels instead of color to rebalance data. 
A link connecting a child and a parent both at the same level is called a horizontal link.

![AA-tree-2](https://user-images.githubusercontent.com/100040302/189117217-3a7bcd5e-8963-4ec8-b7fd-f1b82967c2c2.JPG)

# Rules
  1. Every node can be either red (linked horizontally) or black.
  2. The root and all external nodes are black.
  3. There are no adjacent red nodes (horizontal links).
  4. Every path from root to a NULL node has same number of black nodes.
  5. The left child of a node can not be red (horizontal).
  6. The level of every leaf node is one.
  7. Each red node is at the same level as it's parent.
  8. The level of each black node is one less than that of it's parent.
  
# Performance
Although Red-Black trees are more consistent in their performance with slightly faster insertion and deletion operations, AA trees tend to be flatter which results in slightly faster search times. Additionally the restructuring process is much more simple in AA trees, with only 2 rebalancing operations named: Skew and Split.
   
# Skew    
  The skew operation needs to be applied in case of a left horizontal link.
  
  ![skew](https://user-images.githubusercontent.com/100040302/189130171-9656da86-509f-4dee-a7b6-b7924b622f3d.jpg)

  
# Split
  The split operation needs to be applied in case of adjacent horizontal links.
  
  ![split](https://user-images.githubusercontent.com/100040302/189130155-f5c780b1-9abc-44c9-b6f2-2ac1f35d2ecd.jpg)
