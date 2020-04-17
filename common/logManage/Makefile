include $(HOME)/config.mk
#添加头文件路径
INCLUDE += -I(COMMON)/inc
CFLAGS += -Wall

#添加库文件路劲和链接库文件
#LDFLAGS +=

TARGET=$(RELEASE_LIB)/logPrint.a

OBJPATH	= obj
SRCDIRS = .
OBJDIRS = $(foreach dir,$(SRCDIRS),$(OBJPATH)/$(dir))
SOURCE = $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))
OBJS=$(addprefix $(OBJPATH)/, $(addsuffix .o, $(basename $(SOURCE))))

$(OBJPATH)/%.o : %.c
	$(CC) -c  $(CFLAGS) -o $@ $<

$(TARGET): $(OBJS)
	$(AR) crs $@  $^

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