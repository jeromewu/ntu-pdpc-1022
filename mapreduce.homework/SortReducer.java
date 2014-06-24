import java.io.IOException;
import java.util.Iterator;
import java.lang.String;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class SortReducer extends Reducer<IntWritable, Text, IntWritable, Text> {
    public void reduce(IntWritable key, Iterable<Text> values, Context context)
    throws IOException, InterruptedException {
      Text word = new Text();
      Iterator<String> it_str = IteratorSort.Sort(values.iterator());
      while(it_str.hasNext()){
        if(word.getLength() != 0){
          word.set(word.toString()+","+it_str.next());
        }else{
          word.set(it_str.next());
        }
      }
      context.write(key,word);
    }
}
