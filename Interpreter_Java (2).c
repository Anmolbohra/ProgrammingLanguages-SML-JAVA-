//package interpreter;

import java.io.*;
import java.util.Stack;
import java.util.Iterator;
import java.io.IOException;
import java.util.HashMap;

public class interpreter {

    public static Stack myStack = new Stack();
    public static HashMap myMap = new HashMap();

    public static void interpreter(String input, String output) {

        try {
            BufferedWriter bw = new BufferedWriter(new FileWriter(output));
            BufferedReader br = new BufferedReader(new FileReader(input));
            String line;
            while ((line = br.readLine()) != null) {
                line = line.replace("\n", "");
                System.out.println("The line: " + line);
                if (line.length() > 3 && !line.equals(":true:") && !line.equals(":false:") && !line.equals(":error:") && !line.equals("swap") && !line.equals("equal") && !line.equals("bind") && !line.equals("lessThan") && !line.equals("quit")) {
                    if (line.substring(0, 4).equals("push")) {
                        try {
                            String val = line.substring(5, line.length());
                            if (val.charAt(0) == '\"' && val.charAt(val.length() - 1) == '\"') {
                                val = val.substring(1, val.length() - 1);
                                val = val + '`';
                                myStack.push(val);
                            } else if (Character.isLetter(val.charAt(0))) {
                                myStack.push(val);    // push words
                            } else {
                                myStack.push(Integer.parseInt(line.substring(5, line.length())));     //push the digits 
                            }
                            
                        } catch (Exception e) {
                            myStack.push(":error:"); //error if no match
                           
                        }
                    } else if (!line.substring(0, 4).equals("push")) {
                        myStack.push(":error:"); //error if no match
                    }
                } else if (line.equals("pop")) {
                    try {
                        myStack.pop();
                    } catch (Exception e) {
                        myStack.push(":error:");
                    }
                } else if (line.equals(":true:") || line.equals(":false:") || line.equals(":error:")) {
                    myStack.push(line);
                }else if (line.equals("add") || line.equals("sub") || line.equals("mul") || line.equals("div") || line.equals("rem")){
                            prep_values(line);
                }else if (line.equals("neg")) {
                    neg_values();
                } else if (line.equals("swap")) {
                    swap_values();
                }else if (line.equals("and") || line.equals("or")){
                andor_func(line);
                } else if (line.equals("not")) {
                    not_func();
                } else if (line.equals("equal")) {
                    equal_func();
                } else if (line.equals("lessThan")) {
                    lessthan_func();
                } else if (line.equals("let")) {
                    myStack.push("let");
                } else if (line.equals("bind")) {
                    bind_func();
                } else if (line.equals("if")) {
                    if_func();
                } else if (line.equals("end")) {
                    Object topvalue = myStack.peek();
                    myStack.pop();
                    while (myStack.peek() != "let") {
                        myStack.pop();
                    }
                    myStack.pop();
                    myStack.push(topvalue);
                } else if (line.equals("quit")) {
                    for (int i = 0; i < myStack.size(); i++) {
                        if (myStack.get(i) instanceof String) {
                            String item = (String) myStack.get(i);
                            if (item.charAt(item.length() - 1) == '`') {
                                item = item.substring(0, item.length() - 1);
                                myStack.remove(i);
                                myStack.insertElementAt(item, i);
                            } else {
                                continue;
                            }
                        }
                    }
                    Iterator iters = myStack.iterator();
                    for (int i = myStack.size() - 1; i >= 0; i--) {
                        bw.write(myStack.get(i).toString());
                        bw.newLine();
                    }
                } else {
                    myStack.push(":error:");
                }
                System.out.print(myStack.toString());
            }

            br.close();
            bw.close();
        } catch (IOException e) {
            System.out.println("Error Occured:\n");
            e.printStackTrace();
        }

    }
        public static Object map_check (Object myVal){
            if (myMap.containsKey(myVal)) 
                    myVal = myMap.get(myVal);
            return myVal;
        }
        
        public static boolean check_int(Object myValue1){
            if (myValue1 instanceof Integer)
                return true;
            else 
                return false;
        }
		
	public static void prep_values(String line) {
        int result = 0;
        if (myStack.size() > 1) {
            Object myVal_1 = myStack.peek();
            Object temp = myStack.pop();
            Object myVal_2 = myStack.peek();
            myStack.push(temp);
            myVal_1 = map_check(myVal_1);
            myVal_2=map_check(myVal_2);
            if (check_int(myVal_1) && check_int(myVal_2)) {
                
                Object myVal1 = myStack.pop();
                Object myVal2 = myStack.pop();
                if (myMap.containsKey(myVal1)) {
                    myVal1 = myMap.get(myVal1);
                }
                if (myMap.containsKey(myVal2)) {
                    myVal2 = myMap.get(myVal2);
                }
                switch (line)
                {
                    case "add" : {
                        result = ((int) myVal2) + ((int) myVal1);
                        System.out.println("added result: " + result);
                        break;
                            }
                    case "sub" :
                    {
                        result = ((int) myVal2) - ((int) myVal1);
                        System.out.println("subtracted result: " + result);
                        break;
                    }
                    case "mul" :
                    {
                        result = ((int) myVal2) * ((int) myVal1);
                        System.out.println("multiplied result: " + result);
                        break;
                    }
                    case "div" :
                    {
                        result = ((int) myVal2) / ((int) myVal1);
                        System.out.println("divided result: " + result);
                        break;
                    }
                    case "rem" :
                    {
                        result = ((int) myVal2) % ((int) myVal1);
                        System.out.println("modulated result: " + result);
                        break;
                    }
                }
                    myStack.push(result);
                    System.out.print(myStack.toString());
        }else
            {
                myStack.push(":error:");
                System.out.print(myStack.toString());
            } 
        }else {
            myStack.push(":error:");
            System.out.print(myStack.toString());
        }
    }		
    public static void swap_values() {
        System.out.println("swapping the numbers!!");
        if (myStack.size() > 1) {
            Object temp = myStack.pop();
            Object temp2 = myStack.pop();
            myStack.push(temp);
            myStack.push(temp2);
            System.out.println("swapped numbers!!");
            System.out.print(myStack.toString());
        } else {
            myStack.push(":error:");
            System.out.print(myStack.toString());
        }

    }

    public static void neg_values() {
        System.out.println("negating the number");
        if (myStack.size() > 0) {
            Object myVal_1 = myStack.peek();
           myVal_1 = map_check(myVal_1);
            if (check_int(myVal_1)) {
                Object myVal1 = myStack.pop();
                myVal1 = map_check(myVal1);
                int result = 0 - ((int) myVal1);
                System.out.println("negated result: " + result);
                myStack.push(result);
                System.out.print(myStack.toString());
            } else {
                myStack.push(":error:");
                System.out.print(myStack.toString());
            }
        } else {
            myStack.push(":error:");
            System.out.print(myStack.toString());
        }
    }
     public static void andor_func(String line) {
        if (myStack.size() > 1) {
            Object myValue1 = myStack.peek();
            Object myValue2 = myStack.get(myStack.size() - 2);
            myValue1 = map_check(myValue1);
            myValue2=map_check(myValue2);
            if (!(myValue1.equals(":true:")) && !(myValue1.equals(":false:")) || !(myValue2.equals(":true:")) && !(myValue2.equals(":false:"))) {
                myStack.push(":error:");
            } else {
                switch (line)
                {
                    case ("and") :
                {
                if (myValue1.equals(myValue2)) {
                    Object temp = myValue1;
                    myStack.pop();
                    myStack.pop();
                    myStack.push(temp);
                } else if (myValue1.equals(":false:") || myValue2.equals(":false:")) {
                    myStack.pop();
                    myStack.pop();
                    myStack.push(":false:");
                }
                break;
                }
                    case ("or") :
                    {
                     if (myValue1.equals(myValue2)) {
                    Object temp = myValue1;
                    myStack.pop();
                    myStack.pop();
                    myStack.push(temp);
                } else if (myValue1.equals(":true:") || myValue2.equals(":true:")) {
                    myStack.pop();
                    myStack.pop();
                    myStack.push(":true:");
                    }
                }
                    break;
                }
            }
        } else {
            myStack.push(":error:");
        }
    }

    public static void not_func() {
        if (!myStack.isEmpty()) {
            Object myValue1 = myStack.peek();
          myValue1 = map_check(myValue1);
            if (!(myValue1.equals(":true:")) && !(myValue1.equals(":false:"))) {
                myStack.push(":error:");
            } else {
                if (myValue1.equals(":true:")) {
                    myStack.pop();
                    myStack.push(":false:");
                } else if (myValue1.equals(":false:")) {
                    myStack.pop();
                    myStack.push(":true:");
                }
            }
        } else {
            myStack.push(":error:");
        }
    }

    public static void equal_func() {
        if (myStack.size() > 1) {
            Object myValue1 = myStack.peek();
            Object myValue2 = myStack.get(myStack.size() - 2);
           myValue1 = map_check(myValue1);
            myValue2=map_check(myValue2);
           if (check_int(myValue1) && check_int(myValue2)) {
                if ((int) myValue1 == (int) myValue2) {
                    myStack.pop();
                    myStack.pop();
                    myStack.push(":true:");
                } else {
                    myStack.pop();
                    myStack.pop();
                    myStack.push(":false:");
                }
            } else {
                myStack.push(":error:");
            }
        } else {
            myStack.push(":error:");
        }
    }

    public static void lessthan_func() {
        if (myStack.size() > 1) {
            Object myValue1 = myStack.peek();
            Object myValue2 = myStack.get(myStack.size() - 2);
            myValue1 = map_check(myValue1);
            myValue2=map_check(myValue2);
            if (check_int(myValue1) && check_int(myValue2)) {
                if ((int) myValue2 < (int) myValue1) {
                    myStack.pop();
                    myStack.pop();
                    myStack.push(":true:");
                } else {
                    myStack.pop();
                    myStack.pop();
                    myStack.push(":false:");
                }
            } else {
                myStack.push(":error:");
            }
        } else {
            myStack.push(":error:");
        }
    }

    public static void bind_func() {
        if (myStack.size() > 1) {
            if (myStack.get(myStack.size() - 2) instanceof String) {
                String x = (String) myStack.get(myStack.size() - 2);
                if (x.charAt(x.length() - 1) == '`' || x.equals(":error:") || x.equals("let") || x.equals(":true:") || x.equals(":false:") || x.equals(":unit:") || myStack.peek().equals(":error:")) {
                    myStack.push(":error:");
                } else {
                    myMap.put(x, myStack.peek());
                    Object origValue = myMap.get(x);
                    System.out.println("x: " + x);
                    if (myMap.containsKey(x)) {
                        if (myMap.containsKey(origValue)) {
                            myMap.put(x, myMap.get(origValue));
                        }
                    }
                    myStack.pop();
                    myStack.pop();
                    myStack.push(":unit:");
                }
            } else {
                myStack.push(":error:");
            }
        } else {
            myStack.push(":error:");
        }
    }

    public static void if_func() {
        if (myStack.size() > 2) {
            Object temp = myStack.peek(); //look at the object at the top of the stack
            Object temp2 = myStack.get(myStack.size() - 2);
            Object myValue1 = myStack.peek();
            Object myValue2 = myStack.get(myStack.size() - 2);
            Object myValue3 = myStack.get(myStack.size() - 3);
           myValue1 = map_check(myValue1);
            myValue2=map_check(myValue2);
            myValue3=map_check(myValue3);
            if (myValue3.equals(":true:") || myValue3.equals(":false:")) {
                switch((String)myValue3)
                {
                    case ":true:" :  {
                    myStack.pop();
                    myStack.pop();
                    myStack.pop();
                    myStack.push(temp);
                    break;
                } case ":false:" : {
                    myStack.pop();
                    myStack.pop();
                    myStack.pop();
                    myStack.push(temp2);
                    break;
                }
            }
            }
            else {
                myStack.push(":error:");
            }
        } else {
            myStack.push(":error:");
        }
    }
}
