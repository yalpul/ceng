-- check if a list is palindrome

p6 :: Eq a => [a] -> Bool

p6 xs = 
        xs == reverse xs
