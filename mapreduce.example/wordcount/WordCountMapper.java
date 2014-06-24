import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class WordCountMapper extends Mapper<Object, Text, Text, IntWritable> {

  @Override
    public void map(Object key, Text value,
        Context contex) throws IOException, InterruptedException {
      Text word = new Text();
      IntWritable one = new IntWritable(1);
      StringTokenizer wordList = new StringTokenizer(value.toString());
      while (wordList.hasMoreTokens()) {
        word.set(wordList.nextToken());
        contex.write(word,one);//string 1
      }
    }
}
