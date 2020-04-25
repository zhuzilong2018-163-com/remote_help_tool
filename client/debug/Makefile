include ../../config.mk
#添加头文件路径
INCLUDE += -I$(COMMON)/inc
INCLUDE += -I$(CLIENT)/inc
CFLAGS += -Wall

#添加库文件路劲和链接库文件
LDFLAGS += -L$(RELEASE_LIB) -llogPrint
LDFLAGS += -L$(RELEASE_LIB) -laes

TARGET=$(RELEASE_BIN)/debug

OBJPATH	= obj
SRCDIRS = .
OBJDIRS = $(foreach dir,$(SRCDIRS),$(OBJPATH)/$(dir))
SOURCE = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))
OBJS=$(addprefix $(OBJPATH)/, $(addsuffix .o, $(basename $(SOURCE))))

$(OBJPATH)/%.o : %.c
	$(CC) -c $(INCLUDE) $(CFLAGS) -o $@ $<

$(TARGET): $(OBJS)
	$(CC)  -o $@  $^ $(LDFLAGS)
	$(STRIP) $(TARGET)

clean:
	rm -rf $(TARGET)
	rm -rf *.o
	@for d in $(OBJDIRS);     \
	 do                   \
		rm -rf  $$d/*.o ;\
		rm -rf  $$d/*.d ;\
	 done
	mkdir -p $(OBJPATH)
	mkdir -p $(OBJDIRS)