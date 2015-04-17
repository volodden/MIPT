// общий тип для возвращаемых вашими функциями значений, где первая часть кортежа это само значение функции, вторая - кол-во операций
type Result = float * int
let delta = 1e-10

// *** Первая часть

let fTailor x : float = x / (9.0 + x*x) // функция, которую раскладываем
let n, a, b = 20.0, -1.0, 1.0 // интервал

let tailor x : Result =
    
    let rec calc (sum: float) (n: int) (lastMember: float) =
        
        let newMember = lastMember * (-1.0) * (x * x) / 9.0
        
        if (abs (newMember) < delta)
        then (sum + lastMember, n)
        else calc (sum + lastMember) (n + 1) newMember

    calc 0.0 1 (x / 9.0)

let tailorA x : Result =
    
    let f (value: float) =
        value * (-1.0) * (x * x) / 9.0

    let rec calc (sum: float) (n: int) = 
        
        let cycle (n: int) = 
            
            let rec cycleRec (n: int) (value: float) = 
                match n with
                | 0 -> value
                | _ -> cycleRec (n - 1) (f value)
                
            cycleRec (n - 1) (x / 9.0)

        let newMember = cycle n

        if (abs (newMember) < delta)
        then (sum, n)
        else calc (sum + newMember) (n + 1)

    calc 0.0 1

let printTailor () = 
    [a .. (b-a)/n .. b] 
    |> List.map (fun x -> let (firstRes, firstCou), (secondRes, secondCou) = tailor x, tailorA x in (x, firstRes, firstCou, secondRes, secondCou, fTailor x))
    |> List.iter (fun (a,b,c,d,e,f) -> printf "%f\t%f\t%d\t%f\t%d\t%f\n" a b c d e f )

// *** Вторая часть

type MyResult = Result * bool
let limit = 10000000


let fSolve01 = fun x -> exp(x) + log(x) - 10.0*x            // функция 1, решение которой ищем
let fSolve02 = fun x -> cos(x) - exp(- x*x/2.0) + x - 1.0   // функция 2, решение которой ищем
let fSolve03 = fun x -> 1.0 - x + sin(x) - log(1.0 + x)     // функция 3, решение которой ищем


let iter (f: float -> float) (a: float) (b: float) : MyResult = 

    let rec cycle (x: float) (count: int) =
        
        let signum (x: float) =
            if (x < 0.0)
            then -1.0
            else    if (x > 0.0)
                    then 1.0
                    else 0.0

        let xxi = x - f(x) * 0.00001 * signum (f (x + delta) - f (x))

        if (abs (x - xxi) < delta)
        then ((x, count), true)
        else    if (count < limit)
                then cycle (xxi) (count + 1)
                else ((0.0, 0), false)

    cycle ((a + b) / 2.0) (1)

let newton (f: float -> float) (a: float) (b: float) : MyResult =

    let derivative func (x: float) =
        (f (x + delta) - f (x)) / delta

    let xi (x: float) =
        x - f(x) / (derivative f x)

    let rec cycle (x: float) (count: int) =

        let xxi = xi x

        if (abs (xxi - x) < delta)
        then ((xxi, count), true)
        else    if (count < limit)
                then cycle (xxi) (count + 1)
                else ((0.0, 0), false)

    cycle ((a + b) / 2.0) (1)

    
let dichotomy (f: float -> float) (a: float) (b: float) : MyResult =
    
    let rec cycle (x: float) (a: float) (b:float) (count: int) =
        
        let y = (a + x) / 2.0
        let z = (x + b) / 2.0

        if (abs (a - b) < delta)
        then ((x, count), true)
        else    if (count < limit)
                then    if (f (y) < f (x))
                        then cycle (y) (a) (x) (count + 1)
                        else    if (f (z) < f (x))
                                then cycle (z) (x) (b) (count + 1)
                                else cycle (x) (y) (z) (count + 1)
                else ((0.0, 0), false)
                
    
    cycle ((a + b) / 2.0) (a) (b) (1)

let printSolve () =
    [(fSolve01, 3.0, 4.0); (fSolve02, 1.0, 2.0); (fSolve03, 1.0, 1.5)]
    |> List.iter (fun (fSolve, a, b) -> 
        [newton; dichotomy; iter]
        |> List.map (fun f -> f fSolve a b)
        |> List.iter (fun ((res, cou), exist) ->    if (exist)
                                                    then printfn "%f\t%d" res cou
                                                    else printfn "None\tNone")
        printfn ""
    )
