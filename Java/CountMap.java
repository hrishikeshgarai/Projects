import java.io.IOException;
import java.lang.*;
import java.util.StringTokenizer;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapred.*;

public class CountMap extends Mapper<LongWritable, Text, Text, IntWritable>
{

      private final static IntWritable one = new IntWritable(1);
      private Text word = new Text();

      public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException
      {

          String line = value.toString();
          StringTokenizer tokenizer = new StringTokenizer(line);
          String str1 = new String("hackathon");
          String str2 = new String("dec");
          String str3 = new String("java");
          String str4 = new String("chicago");
           while (tokenizer.hasMoreTokens())
            {
               word.set(tokenizer.nextToken());
                if (str1.equalsIgnoreCase(word.toString()) || str2.equalsIgnoreCase(word.toString()) || str3.equalsIgnoreCase(word.toString()) || str4.equalsIgnoreCase(word.toString()))
		{
                 context.write(word, one);
            }
	}
	}
}                                                                                            
