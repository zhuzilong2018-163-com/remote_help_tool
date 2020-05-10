include ./config.mk

default:
	make -C $(COMMON)/logManage
	make -C $(COMMON)/aes
	make -C $(SERVER)
	make -C $(CLIENT)/clientMain
	make -C $(CLIENT)/debug

clean:
	make -C $(COMMON)/logManage    clean
	make -C $(COMMON)/aes          clean
	make -C $(SERVER)              clean
	make -C $(CLIENT)/clientMain   clean
	make -C $(CLIENT)/debug        clean
