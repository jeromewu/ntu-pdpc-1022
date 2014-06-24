SRC=StringSort.java StringSortMapper.java StringSortReducer.java
CLASSES=$(SRC:.java=.class)
TARGET=StringSort
INDIR=/example/stringsort
OUTDIR=stringsort_out
OUT=result

all: $(SRC)
	javac -classpath `yarn classpath` $(SRC)
	jar -cvf $(TARGET).jar $(CLASSES)
run: $(TARGET).jar
	hadoop jar $(TARGET).jar $(TARGET) $(INDIR) $(OUTDIR)
get:
	hadoop fs -getmerge $(OUTDIR) $(OUT)
clean:
	hadoop fs -rm -r $(OUTDIR) && rm -r $(CLASSES) $(OUT)
