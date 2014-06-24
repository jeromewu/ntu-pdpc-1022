SRC=Sort.java SortMapper.java SortReducer.java SortPartitioner.java IteratorSort.java
CLASS=$(SRC:.java=.class)
TARGET=Sort
INDIR=/data/big
OUTDIR=sort_output
OUT=result

all: $(SRC)
	gcc -lm -g test.data.gen.c -o test.data.gen.out
	javac -classpath `yarn classpath` $(SRC)
	jar -cvf $(TARGET).jar $(CLASS)
run: $(TARGET).jar
	hadoop jar $(TARGET).jar $(TARGET) $(INDIR) $(OUTDIR)
get:
	hadoop fs -getmerge $(OUTDIR) $(OUT)
clean:
	rm $(CLASS) $(OUT)
	hadoop fs -rm -r $(OUTDIR)
