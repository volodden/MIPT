#if INTERACITVE
#r "../packages/FSharp.Data.2.2.2/lib/net40/FSharp.Data.dll"
#endif
open FSharp.Data
open System
open System.IO
open System.Net
open System.Text
open System.Collections.Specialized

let upgrade link = "http://en.wikipedia.org" + link

let deleteTail (mylist:List<string * string>) = 
    let rec deleteTailrec (mylist:List<string * string>) (emptylist:List<string*string>) = if ((snd (List.head mylist)).Contains("ZPL"))
                                                                                           then (List.head mylist)::emptylist
                                                                                           else deleteTailrec (List.tail mylist) ((List.head mylist)::emptylist)
    deleteTailrec mylist []

let getLanguage (link: String) = 
    let helpFunction = 
        let language = HtmlDocument.Load(link)

        language.Descendants(["tr"])
        |> Seq.map (fun x -> x.Elements())
        |> Seq.filter (fun x -> x.Length = 2)
        |> Seq.toList
        |> List.map (fun x -> (x.[0].Descendants ["a"]
                              |> Seq.toList), x.[1])
        |> List.filter (fun (x, y) -> x.Length = 1)
        |> List.filter (fun (x, y) -> x <> List.Empty)
        |> List.map (fun (x, y) -> (x |> List.map (fun y -> y.Elements())
                                      |> List.filter (fun y -> (List.head y).ToString() = "Paradigm")), y)
        |> List.filter (fun (x, y) -> x.Length = 1)
        |> List.map (fun (x, y) -> y.Elements()
                                   |> Seq.toList
                                   |> List.filter (fun y -> y.ToString().Contains ("Imperative") || y.ToString().Contains ("Functional")
                                                         || y.ToString().Contains ("imperative") || y.ToString().Contains ("functional")))
        |> List.filter (fun x -> (x.Length = 1))

    if (List.length helpFunction = 1)
    then ((List.head helpFunction).ToString().Contains ("Imperative") || (List.head helpFunction).ToString().Contains ("imperative"))
    else false

let Lab_02() = 

    let rawHtml = HtmlDocument.Load("http://en.wikipedia.org/wiki/List_of_programming_languages")
    
    let getLinks =
        rawHtml.Descendants(["li"])
        |> Seq.map (fun x -> x.Elements())
        |> Seq.filter (fun x -> x.Length = 1)
        |> Seq.map (fun x -> x.[0])
        |> Seq.toList
        |> List.filter (fun (x : HtmlNode) -> (x.AttributeValue "href").Contains ("wiki"))
        |> List.map (fun (x : HtmlNode) -> (upgrade (x.AttributeValue "href"), x.InnerText()))
        |> List.filter (fun (x, y) -> (x.Contains ("Programming_language_lists") = false) &&
                                      (x.Contains ("List_of_programming_languages_by_category") = false) &&
                                      (x.Contains ("Timeline_of_programming_languages") = false) &&
                                      (x.Contains ("Generational_list_of_programming_languages") = false))

    deleteTail getLinks

        |> List.filter (fun (x, y) -> getLanguage x)
        |> List.map (fun (x, y) -> y)
        |> List.toArray

// почтовый адрес
let email = ""
 
let main () =
  let values = new NameValueCollection()
  values.Add("email", email)
  values.Add("result", Lab_02().ToString())
  values.Add("content", File.ReadAllText(__SOURCE_DIRECTORY__ + @"/" + __SOURCE_FILE__))
 
  let client = new WebClient()
  let response = client.UploadValues(new Uri("http://mipt.eu01.aws.af.cm/lab2"), values)
  let responseString = Text.Encoding.Default.GetString(response)
 
  printf "%A\n" responseString
