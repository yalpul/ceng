-- remove the k'th element from a list

p20 :: Int -> [a] -> (a,[a])

p20 n xs = let f = xs !! (n-1)
               s = take (n-1) xs ++ drop n xs
           in (f,s)
