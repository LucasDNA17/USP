import System.IO
import Data.List
import Data.Ord

main = do
    l <- getLine
    let numeros = map read $ words l :: [Int]
    let n1 = head numeros
    let n2 = head $ tail $ numeros
    let n3 = head $ tail $ tail $ numeros
    let n4 = head $ tail $ tail $ tail $ numeros


    h <- openFile "dados.csv" ReadMode
    contents <- hGetContents h 
    let ls = lines contents
    let paises = linesToPaises ls

    putStrLn $ 
        show $
        sum $
        map active $
        filter ((>= n1).confirmed) paises


    putStrLn $
        show $
        sum $
        map deaths $
        take n3 $
        sortBy (comparing confirmed) $
        take n2 $
        sortBy (flip (comparing active)) paises

    
    putStr $
        concat $
        map (++ "\n") $
        map country $
        sortBy (comparing country) $
        take n4 $
        sortBy (flip (comparing confirmed)) paises
    
        

    hClose h


data Pais = Pais {
    country :: [Char],
    confirmed :: Int,
    deaths :: Int,
    recovery :: Int,
    active :: Int
    } deriving(Show)


linesToPaises :: [[Char]] -> [Pais]
linesToPaises [] = [] 
linesToPaises lines = (stringsToPais $ splitOn ',' (head(lines))) : (linesToPaises $ tail(lines))
    where
        stringsToPais :: [[Char]] -> Pais
        stringsToPais strings = Pais {country = nome, confirmed = confirmadas, deaths = mortes, recovery = salvos, active = ativos}
            where
                nome = head(strings)
                confirmadas = read $ head $ tail(strings)
                mortes = read $ head $ tail $ tail(strings)
                salvos = read $ head $ tail $ tail $ tail(strings)
                ativos = read $ head $ tail $ tail $ tail $ tail(strings)

        splitOn :: Char -> [Char] -> [[Char]]
        splitOn _ [] = []
        splitOn caracter string = delimitado : (splitOn caracter (drop ((length delimitado) + 1) string))
            where
                delimitado = takeWhile (/= caracter) string










            



