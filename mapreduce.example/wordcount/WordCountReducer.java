import java.io.IOException;
import java.util.Iterator;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class WordCountReducer extends Reducer<Text, IntWritable, Text, IntWritable> {
    public void reduce(Text key, Iterable<IntWritable> values, Context context)
    throws IOException, InterruptedException {
      IntWritable total_wordcount = new IntWritable();
      int wordcount = 0;
      Iterator<IntWritable> it = values.iterator();
      while(it.hasNext()){
        wordcount += it.next().get();
      }
      total_wordcount.set(wordcount);
      context.write(key, total_wordcount);
    }
}
