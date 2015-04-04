open System
open System.IO

let file = File.ReadAllText @"C:\Users\volod_000\Desktop\file.txt"

let searchNames (sentence : String) index (names : Map<string, Set<int>>) : Map<string, Set<int>> =

    let words = sentence.Split([|' '; ','; ';'; '"'|])

    let rec loop (namesTemp : Map<string, Set<int>>) i =

        let symbols = [|'.'; '!'; '?'; ' '; char(13); char(10); ')'; '('; ','; ';'; '"'; '\''|]

        match i with
        | a when a = words.Length -> namesTemp
        | _ -> words.[i].Trim(symbols) |> (fun word ->  if word.Length > 1 && Char.IsUpper(word.[0])
                                                        then
                                                        
                                                            let w = 
                                                                if word.[word.Length - 2] = '\'' && word.[word.Length - 1] = 's'
                                                                then word.Remove(word.Length - 2)
                                                                else word
                                                        
                                                            if namesTemp.ContainsKey(w)
                                                            then loop (namesTemp.Add(w, namesTemp.[w].Add(index))) (i + 1) 
                                                            else loop (namesTemp.Add(w, Set.empty.Add(index))) (i + 1)
                                                        
                                                        else loop namesTemp (i + 1))
    loop names 0

type relation = string * string * int

let main (text : String) : relation list =

    let functionForSort (r1 : relation) (r2 : relation) = 
        
        let number (_, _, c) = c
        
        if (number r1 > number r2)
        then -1
        else 1

    let sentences = text.Split([|'.'; '!'; '?'|]);
    
    let rec loop (names : Map<string, Set<int>>) index : Map<string, Set<int>> =
        if (index < sentences.Length)
        then loop (searchNames (sentences.[index].Trim([|'.'; '!'; '?'; ' '|])) index names) (index + 1)
        else names

    let badWords = ["A"; "An"; "The";
                    "I"; "We"; "You"; "He"; "She"; "It";"They";
                    "As"; "But"; "And"; "If"; "Or";
                    "After"; "By"; "In"; "Of";
                    "One"; "Two"; "Three"; "Five"; "FIVE";
                    "Dr"; "Mr"; "Ms";
                    "Can"; "Who"; "What"; "With"; "When";
                    "Many"; "Any"; "Some"; "Everyone"; "Anyway"
                    "Art"; "Cabin"; "Earth"; "Emergency"; "Life"; "Part"; "JUPITER"; "Museum"; "Jupiter"; "Hello"; "No"; "Yes";
                    "Besides"; "That"; "There"; "Then"; "So";
                    "African"; "British"; "Especially"; "Well";
                    "I've"; "I'm"; "I'd"; "Won't"; "I'll"; "We'd"; "You've"]
    
    let filteredMap = Map.filter (fun word _ -> not (List.exists (fun elem -> elem = word) badWords)) (loop Map.empty 0)
    
    let relations = [ for n1 in filteredMap do
                                for n2 in filteredMap do
                                    
                                    let c = Set.count(Set.intersect n1.Value n2.Value)
                                    
                                    if (n1.Key < n2.Key) && (c > 0) then yield (n1.Key, n2.Key, c) ]

    List.sortWith functionForSort relations

for s in (main file) do 
    printfn "%s" (s.ToString())