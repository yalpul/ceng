-- bottom-up of n-ary tree

data Tree a = Node a [Tree a]

p72 :: Tree a -> [a]
p72 (Node x xs) = concatMap p72 xs ++ [x]
