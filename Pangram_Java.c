import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class hw1 {
 static String Str;
    public static void hw1(String inFile , String outFile ) throws IOException {
        
              BufferedReader br= null;
              FileReader fr= null;
              BufferedWriter bw = null;
              FileWriter fw = null;
              
             try {

			fr = new FileReader(inFile);
			br = new BufferedReader(fr);           
                        fw = new FileWriter(outFile);
			bw = new BufferedWriter(fw);

			String sCurrentLine;

			br = new BufferedReader(new FileReader(inFile));

			while ((sCurrentLine = br.readLine()) != null) {
			    System.out.println(sCurrentLine);
                            int i=0;
                                for(char c : sCurrentLine.toCharArray()) {
                                   int x = Character.toUpperCase(c);
                                        if (x >= 'A' && x <= 'Z') {
                                            i |= 1 << (x - 'A');
                                            }
                                    }
                                    if (i == (i | ((1 << (1 + 'Z' - 'A')) - 1)))
                                         Str = "true\n";
                                    else Str ="False\n";
                                    
			bw.write(Str);
                        }
             }
                        	 finally {

                    if (bw != null)
                        bw.close();
                    if (fw != null)
                        fw.close();
                    if (br != null)
			br.close();
             	    if (fr != null)
			fr.close();
                    
             }
    }
}
