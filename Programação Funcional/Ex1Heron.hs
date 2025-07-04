main = do 
    la <- getLine
    lb <- getLine
    lc <- getLine

    let a = read(la)
    let b = read(lb)
    let c = read(lc)

    let res = printArea a b c
    putStrLn res
        where
            printArea a b c
                | (isTriangle a b c) = show $ heron a b c
                | otherwise = "-"

isTriangle a b c
    | (a + b) >= c && (b + c) >= a && (c + a) >= b = True
    | otherwise = False

heron a b c = sqrt(s*(s - a)*(s - b)*(s - c))
    where 
        s = (a + b + c)/2