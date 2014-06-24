import java.io.IOException;
import java.util.Iterator;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class StringSortReducer extends Reducer<Text, Text, Text, Text> {
    public void reduce(Text key, Iterable<Text> values, Context context)
    throws IOException, InterruptedException {
      Iterator<Text> it = values.iterator();
      Text out_val = new Text();
      out_val.set(it.next());
      context.write(key, out_val);
    }
}
