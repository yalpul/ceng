-- find the second from last of a list

p2 :: [a] -> a
p2 xs = reverse xs !! 1
