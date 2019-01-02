fun check (t1, nil) = false |
check (t1, t2::ys) = t1=t2
orelse check (t1, ys);

fun pangram1 (str, current, count) =
        let
                val ref1 = ref current
                val ref2 = ref count
        in
                if !ref2 < 26 andalso !ref1 > #"z" then  "false\n" 
                 else
                        if !ref2 = 26 then "true\n"
                        else
                                if check (!ref1, str) = true then pangram1(str, chr(ord(!ref1) + 1), !ref2 + 1)
                                else "false\n"
        end;

fun hw1(inputFile : string, outputFile : string) =
let
        val inStream = TextIO.openIn inputFile
        val outStream = TextIO.openOut outputFile
        val readLine = TextIO.inputLine inStream
        fun helper(readLine : string option) =
                case readLine of
                                NONE=>(TextIO.closeIn inStream; TextIO.closeOut outStream)
                                |SOME(a)=>(TextIO.output(outStream, pangram1(explode(a), #"a", 0));
                                helper(TextIO.inputLine inStream))
in
        helper(readLine)
end;

