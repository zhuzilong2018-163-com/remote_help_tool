include ../config.mk
#添加头文件路径
INCLUDE += -I$(COMMON)/inc
INCLUDE += -I$(SERVER)/inc
INCLUDE += -I$(SERVER)/serveMain
INCLUDE += -I$(SERVER)/connect
INCLUDE += -I$(SERVER)/taskProcess
CFLAGS += -Wall

#添加库文件路劲和链接库文件
LDFLAGS += -L$(RELEASE_LIB) -llogPrint -lpthread

TARGET=$(RELEASE_BIN)/serve
LOG=$(RELEASE_BIN)/log.txt
default:$(TARGET)

OBJPATH=obj
SRCDIRS=./serveMain ./connect ./taskProcess
OBJDIRS=$(foreach dir,$(SRCDIRS),$(OBJPATH)/$(dir))
SOURCE=$(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))
OBJS=$(addprefix $(OBJPATH)/, $(addsuffix .o, $(basename $(SOURCE))))

$(OBJPATH)/%.o : %.c
	$(CC) -c $(INCLUDE) $(CFLAGS) -o $@ $<

$(TARGET): $(OBJS)
	$(CC)  -o $@  $^ $(LDFLAGS)
	$(STRIP) $(TARGET)

clean:
	rm -rf $(TARGET)
	rm -rf $(LOG)
	rm -rf *.o
	@for d in $(OBJDIRS);     \
	 do                   \
		rm -rf  $$d/*.o ;\
		rm -rf  $$d/*.d ;\
	 done
	mkdir -p $(OBJPATH)


