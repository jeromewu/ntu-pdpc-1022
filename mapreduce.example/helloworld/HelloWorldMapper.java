import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class HelloWorldMapper extends Mapper<Object, Text, Text, Text> {
  @Override
    public void map(Object key, Text value,
        Context context) throws IOException, InterruptedException {
      Text out_value = new Text("Dummy value");
      Text out_key = value;
      context.write(out_key, out_value);
    }
}
