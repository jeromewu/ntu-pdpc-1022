import java.util.Iterator;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
import java.lang.String;

import org.apache.hadoop.io.Text;

public class IteratorSort{
  public static Iterator<String> Sort(Iterator<Text> it){
    List<String> list = new ArrayList<String>();
    while(it.hasNext()){
      list.add(it.next().toString());
    }
    Collections.sort(list);
    return list.iterator();
  }
}

