import java.io.IOException;
import java.util.Iterator;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapred.*;

public class CountReduce extends Reducer<Text, IntWritable, Text, IntWritable>
{
       public void reduce(Text key, Iterator<IntWritable> values, OutputCollector<Text, IntWritable> output, Context context) throws IOException, InterruptedException
      {
            int count = 0;
            while (values.hasNext())
          {
               count = count + values.next().get();
          }
          context.write(key, new IntWritable(count));
      }
}
