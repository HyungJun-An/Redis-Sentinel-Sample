CC=gcc
SRC=./src
OUT=./bin
INC_PATH=./include
INC = -I$(INC_PATH)/
LIBS = -L/usr/local/lib -lhiredis 
#TEST_SOURCE= $(SRC)/redis-master.c
#TEST_TARGET = redis-master

#TEST2_SOURCE= $(SRC)/redis-slave-1.c
#TEST2_TARGET = redis-slave-1

#TEST3_SOURCE= $(SRC)/redis-slave-2.c
#TEST3_TARGET = redis-slave-2

SENTINEL1_SOURCE= $(SRC)/sentinel-1.c
SENTINEL1_TARGET=sentinel-1

SENTINEL2_SOURCE= $(SRC)/sentinel-2.c
SENTINEL2_TARGET=sentinel-2

SENTINEL3_SOURCE= $(SRC)/sentinel-3.c
SENTINEL3_TARGET=sentinel-3



all: $(SENTINEL1_TARGET)\
	$(SENTINEL2_TARGET)\
	$(SENTINEL3_TARGET)

$(SENTINEL1_TARGET): $(SENTINEL1_SOURCE)
	@echo "Compile $^"
	$(CC) -o $(OUT)/$@ $^ $(INC) $(LIBS)

$(SENTINEL2_TARGET): $(SENTINEL2_SOURCE)
	@echo "Compile $^"
	$(CC) -o $(OUT)/$@ $^ $(INC) $(LIBS)

$(SENTINEL3_TARGET): $(SENTINEL3_SOURCE)
	@echo "Compile $^"
	$(CC) -o $(OUT)/$@ $^ $(INC) $(LIBS)


clean:
	rm -f $(SENTINEL1_TARGET)\
	$(SENTINEL2_TARGET)\
	$(SENTINEL3_TARGET)
