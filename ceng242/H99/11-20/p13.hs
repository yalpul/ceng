-- run-length encoding directly (no prior grouping)

data RL a = Single a | Multiple Int a deriving (Show)

p13 :: Eq a => [a] -> [RL a]
p13 = map encodeH . encode where
        encodeH (1,x) = Single x
        encodeH (n,x) = Multiple n x
        encode = foldr conv [] where
                conv c [] = [(1,c)]
                conv c (y@(a,b):xs)
                        | c == b = (a+1,b):xs
                        | otherwise = (1,c):y:xs
