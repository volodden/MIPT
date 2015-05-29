open System
open System.IO
open System.Net
open System.Text
open System.Collections.Specialized

open System.Numerics

// Part 1.
// ---start---
type JSONToken = 
    | OpeningBrace
    | ClosingBrace
    | OpeningBracket
    | ClosingBracket
    | Comma
    | Colon
    | IntegerValue of BigInteger
    | StringValue  of String
    | BooleanValue of Boolean
    | Null

let serviceSymbol s =
    match (s) with
    | '{' -> Some (OpeningBrace)
    | '}' -> Some (ClosingBrace)
    | '[' -> Some (OpeningBracket)
    | ']' -> Some (ClosingBracket)
    | ',' -> Some (Comma)
    | ':' -> Some (Colon)
    | _   -> None

let isServiceSymbol s = 
    match (serviceSymbol s) with
    | Some s -> true
    | None   -> false

let isNumber c =
    match (c) with
    | c when (( c >= '0') && (c <= '9')) -> true
    | _                                  -> false

let isSpace s = 
    match (s) with
    | ' ' | '\n' | '\t' -> true
    | _                 -> false

let parseIntegerValue S =

    let rec parseRec symbols = function
        | c::t when (isNumber c) -> parseRec (c::symbols) t
        | _ as t                 -> List.rev symbols, t

    parseRec [] S

let parseStringValue S =
    
    let rec parseRec symbols = function
        | '"'::t                             -> List.rev symbols, t
        | '\\'::c::t when c = 'n' || c = '"' -> parseRec (c::symbols) t
        | c::t                               -> parseRec (c::symbols) t
        | _                                  -> failwith "String value is incorrect."

    parseRec [] S

let splitString s = [for c in s -> c]

let tokenizeString s =
    
    let rec tokenizeRec tokens = function
        | []                          -> List.rev tokens
        | w::t when isSpace w         -> tokenizeRec tokens t
        | w::t when isServiceSymbol w -> tokenizeRec (((serviceSymbol w).Value)::tokens) t 
        | '"'::t                      ->
                                         let symbols, t' = parseStringValue t
                                         tokenizeRec ((StringValue (System.String.Concat symbols))::tokens) t'
        | 'n'::'u'::'l'::'l'::t       -> tokenizeRec (Null::tokens) t
        | 't'::'r'::'u'::'e'::t       -> tokenizeRec ((BooleanValue true)::tokens) t
        | 'f'::'a'::'l'::'s'::'e'::t  -> tokenizeRec ((BooleanValue false)::tokens) t
        | d::t when isNumber d        ->
                                         let symbols, t' = parseIntegerValue (d::t)
                                         let number = System.String.Concat symbols
                                         tokenizeRec ((IntegerValue (try BigInteger.Parse(number) with e -> 0I))::tokens) t'
        | _                           -> failwith "Error (tokenize string)."

    tokenizeRec [] (splitString s)
// ---end---

// Part 2.
// ---start---
type JSONObject =
    | Object  of List<string * JSONObject>
    | Array   of List<JSONObject>
    | Number  of BigInteger
    | String  of string
    | Boolean of bool
    | Null

let parseJSONTokens tokens =
    
    let rec parse tokens =

        let rec parseObjectRec L = function
            | JSONToken.ClosingBrace::t         -> (JSONObject.Object (List.rev L)), t
            | Comma::t                          -> parseObjectRec L t
            | JSONToken.StringValue s::Colon::t ->
                                                    let obj, t' = parse t
                                                    parseObjectRec ((s, obj)::L) t'
            | _                                 -> failwith "Object is incorrect"

        let rec parseArrayRec L = function
            | JSONToken.ClosingBracket::t -> (JSONObject.Array (List.rev L)), t
            | Comma::t                    -> parseArrayRec L t
            | _ as t                      ->
                                             let obj, t' = parse t
                                             parseArrayRec (obj::L) t'

        match (tokens) with
        | JSONToken.OpeningBrace::t     -> parseObjectRec [] t
        | JSONToken.OpeningBracket::t   -> parseArrayRec  [] t
        | JSONToken.Null::t             -> JSONObject.Null, t
        | JSONToken.StringValue s::t    -> JSONObject.String s, t
        | JSONToken.IntegerValue v::t   -> JSONObject.Number v, t
        | JSONToken.BooleanValue b::t   -> JSONObject.Boolean b, t
        | _                             -> failwith "Token is unknown."

    match (parse tokens) with
    | result, [] -> result
    | _          -> failwith "JSON structure is wrong."

let stringToJSON s =
    try  Some (parseJSONTokens (tokenizeString (s)))
    with e -> None

let parse = stringToJSON
/// ---end---

// Part 3. Variant 1.
// ---start---
let countArrayElements jsonObj =
  
    let rec countRec (obj:JSONObject) =
        match (obj) with
        | JSONObject.Array  items -> List.fold (fun s item -> 1 + s + (countRec item))       0 items
        | JSONObject.Object pairs -> List.fold (fun s pair ->     s + (countRec (snd pair))) 0 pairs
        | _                       -> 0

    match (jsonObj) with
    | Some obj -> countRec obj
    | None     -> -1

let lab3 = countArrayElements
// ---end---

// Part 4.
// ---start---
let randomNumber1 (r:System.Random) = char (r.Next(int '0', (int '9') + 1))

let randomNumber (r:System.Random) =

    let minLengthForInt = 1
    let maxLengthForInt = 5
    let length = r.Next(minLengthForInt, maxLengthForInt + 1)
    
    JSONObject.Number (System.String.Concat ([for i in 1..length -> randomNumber1 r])
                       |> (fun n -> try BigInteger.Parse(n) with e -> 0I))

let randomChar (r:System.Random) = char (r.Next(int 'a', (int 'z') + 1))

let randomString (r:System.Random) =

    let minLengthForString = 1
    let maxLengthForString = 5
    let length = r.Next(minLengthForString, maxLengthForString + 1)
    
    System.String.Concat ([for i in 1..length -> 
                                                 match (randomChar r) with
                                                 | '"'    -> "\\\""
                                                 | _ as c -> c.ToString() ])
                                        
let randomBool (r:System.Random) = JSONObject.Boolean (r.Next(0, 2) = 0)

let randomPrimitive (r:System.Random) =
    match r.Next(0, 3 + 1) with
    | 0 -> JSONObject.String (randomString r)
    | 1 -> randomNumber r
    | 2 -> randomBool r
    | _ -> JSONObject.Null

let randomJSON maxDepth =
    
    let minCountObject = 0
    let maxCountObject = 5

    let rec randomObject depth (r:System.Random) =

        let minLengthOfArray = 0
        let maxLengthOfArray = 5

        let rec randomArray depth (r:System.Random) =
            
            let length = r.Next(minLengthOfArray, maxLengthOfArray + 1)

            JSONObject.Array [ for i in 1..length ->
                                                     match r.Next(0, 5 + 1) with
                                                     | 0 when (depth > 0) -> randomObject (depth - 1) r
                                                     | 1 when (depth > 0) -> randomArray  (depth - 1) r
                                                     | _                  -> randomPrimitive          r
                             ]

        JSONObject.Object [
                            for i in 1..r.Next(minCountObject, maxCountObject + 1) ->
                                                                                        (
                                                                                            randomString r,
                                                                                            match r.Next(0, 10 + 1) with
                                                                                            | 0 when (depth > 0) -> randomObject (depth - 1) r
                                                                                            | 1 when (depth > 0) -> randomArray  (depth - 1) r
                                                                                            | _                  -> randomPrimitive         r
                                                                                        )
                          ] 
     
    randomObject maxDepth (System.Random())

let howMuch = 5
let generate = randomJSON howMuch
// ---end---

// Part 5.
/// ---start---
let JSONToString jsonObject =
    
    let tabulation t = System.String.Concat ([for i in 1..t -> '\t'])

    let rec serializeRec (depth:int) (obj:JSONObject) =
        
        let rec serializeObject depth pairs =
            "{\n"
            + ( List.map (fun (k, v) -> (tabulation depth) + "\"" + k + "\": " + (serializeRec (depth+1) v )) pairs
                |> fun x -> System.String.Join(",\n", x) )
            + (tabulation (depth))
            + "\n}"
 
        match obj with
        | JSONObject.Boolean b    -> b.ToString()
        | JSONObject.Null         -> "null"
        | JSONObject.Number n     -> n.ToString()
        | JSONObject.String s     -> "\"" + s + "\""
        | JSONObject.Array items  -> "[" + System.String.Join(", ", List.map (serializeRec depth) items) + "]"
        | JSONObject.Object pairs -> serializeObject (depth+1) pairs

    serializeRec 0 jsonObject

let stringify = JSONToString
/// ---end----

// Part6. (Or tests.)
// ---start---
let testFunction tests =
    let rec test P F results = function
        | [] -> P, F, List.rev results
        | (testName, str, answer)::t ->
            let count = countArrayElements (stringToJSON str)
            if (count <> answer)
            then test    P     (F + 1)  ((testName, "FAILED (expected " + answer.ToString() + ", got " + count.ToString() + ")")::results)  t
            else test (P + 1)     F     ((testName, "PASSED")::results)                                                                     t
    test 0 0 [] tests  

let test() =

    let tests = [
        
        (   "Empty array", """
            {
                "a": []
            }""", 0                                                   );
        (   "Array with object", """                                  
            {                                                         
                "a": [                                                
                       {                                               
                         "b": []                                           
                       }                                              
                     ]                                                    
            }""", 1                                                   );
        (   "Array with one element", """                             
            {                                                         
                "a": [23]                                              
            }""", 1                                                   );
        (   "One element", """                                        
            {                                                         
                "a": 23                                               
            }""", 0                                                   );
        (   "Array with few elements", """                             
            {                                                         
                "a": [23, "b", 42, "aaaa"]                                    
            }""", 4                                                   );
        (   "Array with few objects", """                             
            {                                                         
                "a": [                                                
                       {                                              
                         "b": [42],                                   
                         "c": ["321", "123", "33333"]                 
                       },                                             
                       {                                              
                         "aa": 1                                      
                       }                                              
                     ]                                                
            }""", 6                                                   );
        (   "Array with object with array with one element", """       
            {                                               
                "a": [ 
                       {                                     
                         "b": [42]                               
                       }
                     ]                                          
            }""", 2                                                   );
        (   "Big test", """                                           
            {                                                         
                "a": {                                                
                    "b": [],                                          
                    "c": [["11", 11], ["22", 22, 33, "33"]],          
                    "d": [23, 42, "23", "42"],                        
                    "e": 1024                                         
                },                                                    
                "f": [                                                
                       {                                              
                         "g": [[1], [2]],                             
                         "h": ["7", "44"],                            
                         "i": 2048                                    
                       },                                             
                       {                                              
                         "j": [[[["+4"]]]]                            
                       },                                             
                       {                                              
                         "h": "25!"                                   
                       }                                              
                     ]                                                
            }""", 25                                                  );
    ]

    let passed, failed, results = testFunction tests

    printfn "Passed: %d\nFailed: %d" passed failed
    List.iter (fun (n, r) -> printfn "%s: %s" n r) results
// --end---