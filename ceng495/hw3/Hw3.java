import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.FloatWritable;
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Partitioner;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.MultipleOutputs;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;

public class Hw3 {

  public static class GameTokenizerMapper
       extends Mapper<Object, Text, Text, IntWritable>{

    private final static IntWritable one = new IntWritable(1);
    private Text word = new Text();

    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
      StringTokenizer itr = new StringTokenizer(value.toString());
      while (itr.hasMoreTokens()) {
        String team1 = itr.nextToken();
        String team2 = itr.nextToken();
        String rslt = itr.nextToken();
        word.set(team1);
        context.write(word, one);
        word.set(team2);
        context.write(word, one);
      }
    }
  }

  public static class GameIntSumReducer
       extends Reducer<Text,IntWritable,Text,IntWritable> {
    private IntWritable result = new IntWritable();

    public void reduce(Text key, Iterable<IntWritable> values,
                       Context context
                       ) throws IOException, InterruptedException {
      int sum = 0;
      for (IntWritable val : values) {
        sum += val.get();
      }
      result.set(sum);
      context.write(key, result);
    }
  }

  public static class PointTokenizerMapper
       extends Mapper<Object, Text, Text, IntWritable>{

    private final static IntWritable one = new IntWritable(1);
    private final static IntWritable two = new IntWritable(2);
    private final static IntWritable three = new IntWritable(3);
    private Text word = new Text();

    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
      StringTokenizer itr = new StringTokenizer(value.toString());
      while (itr.hasMoreTokens()) {
        String team1 = itr.nextToken();
        String team2 = itr.nextToken();
        String rslt = itr.nextToken();
        switch (rslt) {
          case "0":
            word.set(team1);
            context.write(word, one);
            word.set(team2);
            context.write(word, one);
            break;
          case "1":
            word.set(team1);
            context.write(word, three);
            break;
          case "2":
            word.set(team2);
            context.write(word, three);
            break;
        }
      }
    }
  }

  public static class PointIntSumReducer
       extends Reducer<Text,IntWritable,Text,IntWritable> {
    private IntWritable result = new IntWritable();

    public void reduce(Text key, Iterable<IntWritable> values,
                       Context context
                       ) throws IOException, InterruptedException {
      int sum = 0;
      for (IntWritable val : values) {
        sum += val.get();
      }
      result.set(sum);
      context.write(key, result);
    }
  }

  public static class AvgTokenizerMapper
       extends Mapper<Object, Text, Text, IntWritable>{

    private final static IntWritable zero = new IntWritable(0);
    private final static IntWritable one = new IntWritable(1);
    private final static IntWritable two = new IntWritable(2);
    private final static IntWritable three = new IntWritable(3);
    private Text word = new Text();

    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
      StringTokenizer itr = new StringTokenizer(value.toString());
      while (itr.hasMoreTokens()) {
        String team1 = itr.nextToken();
        String team2 = itr.nextToken();
        String rslt = itr.nextToken();
        switch (rslt) {
          case "0":
            word.set(team1);
            context.write(word, one);
            word.set(team2);
            context.write(word, one);
            break;
          case "1":
            word.set(team1);
            context.write(word, three);
            word.set(team2);
            context.write(word, zero);
            break;
          case "2":
            word.set(team2);
            context.write(word, three);
            word.set(team1);
            context.write(word, zero);
            break;
        }
      }
    }
  }

  public static class AvgReducer
          extends Reducer<Text,IntWritable,Text,DoubleWritable> {
      private DoubleWritable result = new DoubleWritable();
      public void reduce(Text key, Iterable<IntWritable> values,
                         Context context
      ) throws IOException, InterruptedException {
      int totalCount = 0;
      int sum = 0;
          for (IntWritable val : values) {
              sum += val.get();
              totalCount++;
          }
          result.set((double)sum/totalCount);
          context.write(key, result);
      }
  }

  public static class StatTokenizerMapper
       extends Mapper<Object, Text, Text, IntWritable>{

    private final static IntWritable one = new IntWritable(1);
    private final static String draw = "DRAW";
    private final static String hwin = "HOME_WIN";
    private final static String awin = "AWAY_WIN";

    private Text word = new Text();

    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
      StringTokenizer itr = new StringTokenizer(value.toString());
      while (itr.hasMoreTokens()) {
        String team1 = itr.nextToken();
        String team2 = itr.nextToken();
        String rslt = itr.nextToken();
        switch (rslt) {
          case "0":
            word.set(draw);
            context.write(word, one);
            break;
          case "1":
            word.set(hwin);
            context.write(word, one);
            break;
          case "2":
            word.set(awin);
            context.write(word, one);
            break;
        }
      }
    }
  }
  public static class StatPartitioner extends
      Partitioner < Text, IntWritable> {
     public int getPartition(Text key,  IntWritable value, int numReduceTasks) {
       switch(key.toString()) {
        case "DRAW": return 0;
        case "HOME_WIN": return 1;
        case "AWAY_WIN": return 2;
        default: return 0;
       }
     }
  }


  public static class StatIntSumReducer
       extends Reducer<Text,IntWritable,Text,IntWritable> {
    private IntWritable result = new IntWritable();

    public void reduce(Text key, Iterable<IntWritable> values,
                       Context context
                       ) throws IOException, InterruptedException {
      int sum = 0;
      for (IntWritable val : values) {
        sum += val.get();
      }
      result.set(sum);
      context.write(key, result);
    }
  }

  public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();
    Job job = Job.getInstance(conf, "HW3");
    job.setJarByClass(Hw3.class);
    String type = args[0];
    switch (type) {
      case "game":
        job.setMapperClass(GameTokenizerMapper.class);
        job.setCombinerClass(GameIntSumReducer.class);
        job.setReducerClass(GameIntSumReducer.class);
        break;

      case "point":
        job.setMapperClass(PointTokenizerMapper.class);
        job.setCombinerClass(PointIntSumReducer.class);
        job.setReducerClass(PointIntSumReducer.class);
        break;

      case "avg":
        job.setNumReduceTasks(1);
        job.setMapperClass(AvgTokenizerMapper.class);
        job.setReducerClass(AvgReducer.class);
        break;

      case "stat":
        job.setNumReduceTasks(3);
        job.setMapperClass(StatTokenizerMapper.class);
        job.setPartitionerClass(StatPartitioner.class);
        job.setReducerClass(StatIntSumReducer.class);
        break;

    }
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
    FileInputFormat.addInputPath(job, new Path(args[1]));
    FileOutputFormat.setOutputPath(job, new Path(args[2]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}

