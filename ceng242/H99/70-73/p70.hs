-- tree construction from node string

data Tree a = Node a [Tree a] deriving Show

p70 :: String -> Tree Char
p70 (x:xs) = Node x (fst (p70' xs)) where
        p70' (x:xs)
                | x == '^'  = ([], xs)
                | otherwise = (Node x tree0 : trees1, rest1) where
                        (tree0, rest0)  = p70' xs
                        (trees1, rest1) = p70' rest0

