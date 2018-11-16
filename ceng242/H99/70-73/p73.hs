-- print n-ary trees in LISP notation

data Tree a = Node a [Tree a]

p73 :: Tree Char -> String
p73 (Node x []) = [x]
p73 (Node x xs) = '(' : [x] ++ concatMap p73 xs ++ ")"
