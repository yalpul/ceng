-- implement treetostring and stringto tree


data Tree a = Empty | Branch a (Tree a) (Tree a)

p67a :: Tree Char -> String
p67a Empty = ""
p67a (Branch x Empty Empty) = [x]
p67a (Branch x l r) = 
        x : "(" ++ p67a l ++ "," ++ p67a r ++ ")"
