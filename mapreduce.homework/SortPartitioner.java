import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Partitioner;

public class SortPartitioner extends Partitioner<IntWritable, Text> {

  @Override
  public int getPartition(IntWritable key, Text value, int numReduceTasks){
      if(key.get() < 429496729)
        return 0;
      else if(key.get() >= 429496729 && key.get() < 858993458)
        return 1;
      else if(key.get() >= 858993458 && key.get() < 1288490187)
        return 2;
      else if(key.get() >= 1288490187 && key.get() < 1717986916)
        return 3;
      else
        return 4;
  }
}
