import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class StringSortMapper extends Mapper<Object, Text, Text, Text> {
    public void map(Object key, Text value,
        Context contex) throws IOException, InterruptedException {
      Text out_key = new Text();
      Text out_val = new Text("Dummy Value");
      StringTokenizer wordList = new StringTokenizer(value.toString());
      while (wordList.hasMoreTokens()) {
        out_key.set(wordList.nextToken());
        contex.write(out_key, out_val);
      }
    }
}
