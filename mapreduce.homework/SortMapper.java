import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class SortMapper extends Mapper<Object, Text, IntWritable, Text> {

  @Override
    public void map(Object key, Text value,
        Context contex) throws IOException, InterruptedException {
      // Break line into words for processing
      Text word = new Text();
      StringTokenizer wordList = new StringTokenizer(value.toString());
      while (wordList.hasMoreTokens()) {
        IntWritable num = new IntWritable(Integer.parseInt(wordList.nextToken()));
        word.set(wordList.nextToken());
        contex.write(num, word);
      }
    }
}
