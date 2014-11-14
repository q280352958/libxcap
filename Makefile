CC := gcc
TARGETS = simple-test

PROJECT_BIN_DIR=./bin
PROJECT_SRC_DIR=./src
PROJECT_INC_DIR=./inc
PROJECT_LIB_DIR=./lib
PROJECT_OBJ_DIR=./objs
MKDIR := mkdir -p

CFLAGS := -g -I$(PROJECT_INC_DIR)
LDFLAG := -L$(PROJECT_LIB_DIR)
DEFLAG := -D TEST_GET

src :=$(wildcard $(PROJECT_SRC_DIR)/*.c) \
	$(wildcard $(PROJECT_SRC_DIR)/libmd5/*.c) \
	$(wildcard $(PROJECT_SRC_DIR)/libghttp/*.c) \
	$(wildcard $(PROJECT_SRC_DIR)/libxcap/*.c) \
	$(wildcard $(PROJECT_SRC_DIR)/libezxml/*.c)
	
dir := $(notdir $(src))
PROJECT_OBJ := $(patsubst %.c,%.o,$(dir) )
	
PROJECT_ALL_OBJS := $(addprefix $(PROJECT_OBJ_DIR)/, $(PROJECT_OBJ))

$(PROJECT_OBJ_DIR)/%.o : $(PROJECT_SRC_DIR)/libmd5/%.c
	$(MKDIR) $(PROJECT_OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@	

$(PROJECT_OBJ_DIR)/%.o : $(PROJECT_SRC_DIR)/libghttp/%.c
	$(MKDIR) $(PROJECT_OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@	

$(PROJECT_OBJ_DIR)/%.o : $(PROJECT_SRC_DIR)/libxcap/%.c
	$(MKDIR) $(PROJECT_OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@	

$(PROJECT_OBJ_DIR)/%.o : $(PROJECT_SRC_DIR)/libezxml/%.c
	$(MKDIR) $(PROJECT_OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@	

$(PROJECT_OBJ_DIR)/%.o : $(PROJECT_SRC_DIR)/%.c
	$(MKDIR) $(PROJECT_OBJ_DIR)
	$(CC) $(DEFLAG) -c $(CFLAGS) $< -o $@	

all:$(PROJECT_ALL_OBJS)
	$(MKDIR) $(PROJECT_BIN_DIR)
	$(CC) $(CFLAGS) $(PROJECT_ALL_OBJS) -o $(PROJECT_BIN_DIR)/$(TARGETS) $(LDFLAG)


clean:
	rm -fr $(PROJECT_OBJ_DIR)
	rm -fr $(PROJECT_BIN_DIR)	
