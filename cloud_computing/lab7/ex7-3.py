import sys
from pyspark.sql import SparkSession
import pyspark.sql.functions as sparkFun


#Set a name for the application
appName = "DataFrame Example"

#Set the input folder location
input_folder = "data/in" 

#Set the input folder location
output_folder = "data/out" 

#create a new Spark application and get the Spark session object
spark = SparkSession.builder.appName(appName).getOrCreate()

#read in the CSV dataset as a DataFrame
#inferSchema option forces Spark to automatically specify data column types
#header option forces Spark to automatically fetch column names from the first line in the dataset files
weather_df = spark.read \
              .option("inferSchema", True) \
              .option("header", True) \
              .csv(input_folder)


#Show 10 rows without truncating lines.
#review content might be a multi-line string.
#weather_df.show(10, False)

#Show dataset schema/structure with filed names and types
#weather_df.printSchema()

#-----------------------------------

result_df = weather_df.filter("`Air Temperature` > 20").groupBy("Station Name").agg(sparkFun.avg("Humidity"))

result_df.show(10, False) 

result_df.coalesce(1).write.mode("overwrite").format("csv").save(output_folder+"/ex7-3")

#Stop Spark session
spark.stop()