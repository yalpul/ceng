-- generate balanced trees
-- with n nodes

data Tree a = Empty | Branch a (Tree a) (Tree a) deriving (Show, Eq)

p55 :: Int -> [Tree Char]
p55 0 = [Empty]
p55 n = let (q,r) = quotRem (n-1) 2
        in [ (Branch 'x' l r) | i <- [q..q+r],
                                l <- p55 i,
                                r <- p55 (n-i-1) ]
