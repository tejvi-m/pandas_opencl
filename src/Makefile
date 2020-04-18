OBJS	= gpu.o DataFrame.o Graph.o helpers.o SeriesInt.o SeriesFloat.o SeriesStr.o client3.o
SOURCE	= DataFrame/gpu/gpu.cpp DataFrame/DataFrame.cpp DataFrame/Graph.cpp DataFrame/helpers.cpp DataFrame/SeriesInt.cpp DataFrame/SeriesFloat.cpp DataFrame/SeriesStr.cpp client3.cpp
HEADER	= DataFrame/gpu/gpu.h DataFrame/DataFrame.h DataFrame/Graph.h DataFrame/helpers.h DataFrame/Series.h
OUT	= dataframes
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++17 -lOpenCL
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

DataFrame/gpu/gpu.o: DataFrame/gpu/gpu.cpp
	$(CC) $(FLAGS) DataFrame/gpu/gpu.cpp

DataFrame/DataFrame.o: DataFrame/DataFrame.cpp
	$(CC) $(FLAGS) DataFrame/DataFrame.cpp

DataFrame/Graph.o: DataFrame/Graph.cpp
	$(CC) $(FLAGS) DataFrame/Graph.cpp

DataFrame/helpers.o: DataFrame/helpers.cpp
	$(CC) $(FLAGS) DataFrame/helpers.cpp

DataFrame/SeriesInt.o: DataFrame/SeriesInt.cpp
	$(CC) $(FLAGS) DataFrame/SeriesInt.cpp

DataFrame/SeriesFloat.o: DataFrame/SeriesFloat.cpp
	$(CC) $(FLAGS) DataFrame/SeriesFloat.cpp

DataFrame/SeriesStr.o: DataFrame/SeriesStr.cpp
	$(CC) $(FLAGS) DataFrame/SeriesStr.cpp

client3.o: client3.cpp
	$(CC) $(FLAGS) client3.cpp


clean:
	rm -f $(OBJS) $(OUT)
