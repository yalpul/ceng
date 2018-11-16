-- split a list to two with sizes n

p17 :: [a] -> Int -> ([a],[a])
p17 (x:xs) n
        | n > 0 = let (f,l) = p17 xs (n-1)
                  in (x:f,l)
p17 xs _ = ([],xs)
