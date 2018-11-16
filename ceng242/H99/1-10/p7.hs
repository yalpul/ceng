-- flatten a list
-- sicne haskell lists are homogeneous
-- we define a new list type

data NestedList a = Elem a | List [NestedList a]

p7 :: NestedList a -> [a]

p7 (Elem x) = [x]
p7 (List xs) = foldr (++) [] $ map p7 xs
