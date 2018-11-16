-- determine inorder preorder and postorder traversal of a tree

data Tree a = Empty | Branch a (Tree a) (Tree a)

-- inorder
p68 :: Tree Char -> String
p68 Empty = ""
p68 (Branch x Empty Empty) = [x]
p68 (Branch x l r) = p68 l ++ [x] ++ p68 r

-- preorder
p68' :: Tree Char -> String
p68' Empty = ""
p68' (Branch x Empty Empty) = [x]
p68' (Branch x l r) = x : p68' l ++ p68' r

-- postorder
p68'' :: Tree Char -> String
p68'' Empty = ""
p68'' (Branch x Empty Empty) = [x]
p68'' (Branch x l r) = p68'' l ++ p68'' r ++ [x]
